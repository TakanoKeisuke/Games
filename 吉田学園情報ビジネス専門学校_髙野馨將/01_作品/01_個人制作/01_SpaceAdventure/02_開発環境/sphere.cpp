//======================================================
//
//Sphere
//Author:髙野馨將
//
//======================================================
#include "input_keyboard.h"
#include "sphere.h"
#include "application.h"
#include "game.h"
#include "input.h"
#include "debug.h"
#include <assert.h>
#include "meshfield.h"
#include "main.h"
#include "BoxHitbox.h"
#include "CylinderHitbox.h"
#include "stage.h"

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CSphere::CSphere(int nPriority) : CObjectX(nPriority)
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//======================================================
//デストラクタ
//======================================================
CSphere::~CSphere()
{

}

//======================================================
//初期化処理
//======================================================
HRESULT CSphere::Init(void)
{
	//初期化
	D3DXMatrixIdentity(&m_mtxRot);
	m_quat = {};
	m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fValueRot = 0.0f;
	m_pHitbox = nullptr;
	m_bModel = false;

	//モデルの設定
	LoadModel("data\\model\\sphere.x");

	return S_OK;
}

//======================================================
//更新処理
//======================================================
void CSphere::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	Flag();
}

//======================================================
//更新処理
//======================================================
void CSphere::Update(void)
{
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
	 //位置を更新する
		D3DXVECTOR3 newPos = GetPos() + m_pHitbox->GetRelativePos();
		m_pHitbox->SetPos(newPos);
	}
	//キー入力
	Input();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

}

//======================================================
//描画処理
//======================================================
void CSphere::Draw(void)
{
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans,mtxWorld;

	//モデルの情報の取得
	D3DXVECTOR3 SpherePos = GetPos();

	//ワールドマトリックス
	mtxWorld = GetWorldMatrix();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//クォータニオンの作成
	D3DXQuaternionRotationAxis(&m_quat,&m_vecAxis,m_fValueRot);

	//向きの反映
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quat);
	D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &m_mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, SpherePos.x, SpherePos.y, SpherePos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	SetWorldMatrix(mtxWorld);

	//描画
	CObjectX::DrawSphere();
}

//======================================================
//生成処理
//======================================================
CSphere *CSphere::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, int nPriority)
{
	//動的確保
	CSphere *pSphere;
	pSphere = new CSphere(nPriority);

	if (pSphere != nullptr)
	{
		//初期化
		pSphere->Init();
		pSphere->SetPos(pos);
		pSphere->SetRot(rot);
	}
	
	//ヒットボックスを生成する
	pSphere->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 35.0f, 10.0f), CHitbox::TYPE_OBSTACLE, pSphere);
	
	return pSphere;
}

//======================================================
//入力処理
//======================================================
void CSphere::Input(void)
{
	//モデルの情報の取得
	D3DXVECTOR3 SpherePos = GetPos();
	D3DXVECTOR3 SphereRot = GetRot();
	D3DXVECTOR3 SphereMove = GetMove();
	D3DXVECTOR3 SphereSize = GetSize();

	//カメラの情報の取得
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//プレイヤーの移動
	if (CInputKeyboard::GetKeyboardPress(DIK_I)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y  < -0.5f*/)
	{//↑を押したら
		if (CInputKeyboard::GetKeyboardPress(DIK_L)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
		{//→を押したら
			SphereMove.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z += cosf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_J)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
		{//←を押したら
			SphereMove.x -= sinf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
		}
		else
		{//↑
			SphereMove.z += cosf(CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);
			m_rotDest.y = CameraRot.y + D3DX_PI;
		}
	}
	//↓を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_K) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).y  > 0.5f*/)
	{
		if (CInputKeyboard::GetKeyboardPress(DIK_L)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
		{//→を押したら
			SphereMove.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_J) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
		{//←を押したら
			SphereMove.x -= sinf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{//↓
			SphereMove.z -= cosf(CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);
			//m_rotDest.y = CameraRot.y;
		}
	}
	//→を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_L) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
	{
		SphereMove.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * 1.0f;
		SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);
		//m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
	}
	//←を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_J) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
	{
		SphereMove.x -= sinf(D3DX_PI * 0.5f + CameraRot.y) * 1.0f;
		SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);
		//m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
	}

	//目的の角度の正規化
	if (m_rotDest.y - GetRot().y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - SphereRot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//減衰
	SphereRot.y += (m_rotDest.y - SphereRot.y) * 0.1f;

	//現在の角度の正規化
	if (SphereRot.y > D3DX_PI)
	{
		SphereRot.y = SphereRot.y - D3DX_PI * 2;
	}
	else if (SphereRot.y < -D3DX_PI)
	{
		SphereRot.y = SphereRot.y + D3DX_PI * 2;
	}

	//移動量の加算
	SpherePos += SphereMove;

	//移動量を更新
	SphereMove.x += (0.0f - SphereMove.x) * 0.45f;
	SphereMove.z += (0.0f - SphereMove.z) * 0.45f;

	//回転軸
	m_vecAxis = D3DXVECTOR3(SphereMove.z, SphereMove.y, -SphereMove.x);
	//回転量
	m_fValueRot = D3DXVec3Length(&SphereMove) / D3DXVec3Length(&SphereSize);

	//rotの設定
	SetRot(SphereRot);

	////メッシュの当たり判定
	//std::vector<CMeshField*> pMesh = CStage::GetMesh();
	//if (pMesh != nullptr)
	//{
	//	pMesh->Collision(&SpherePos, SphereSize.y / 2.0f);
	//}

	//posの設定
	SetPos(SpherePos);

	//moveの設定
	SetMove(SphereMove);
}