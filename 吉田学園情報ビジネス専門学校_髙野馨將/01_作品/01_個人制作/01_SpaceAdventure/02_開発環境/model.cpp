//======================================================
//
//モデル
//Author:髙野馨將
//
//======================================================
#include "model.h"
#include "application.h"
#include "input.h"
#include "game.h"
#include <assert.h>
#include "player.h"

//======================================================
//コンストラクタ
//======================================================
CModel::CModel()
{
	m_nMatId = -1;
}

//======================================================
//デストラクタ
//======================================================
CModel::~CModel()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CModel::Init(void)
{
	//初期化
	m_bModel = false;
	m_pTexture = nullptr;
	D3DXMatrixIdentity(&m_mtxShadow);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CModel::Uninit(void)
{
	//メッシュの破棄
	if (m_MeshModel != nullptr)
	{
		m_MeshModel->Release();
		m_MeshModel = nullptr;
	}

	//マテリアルの破棄
	if (m_BuffMatModel != nullptr)
	{
		m_BuffMatModel->Release();
		m_BuffMatModel = nullptr;
	}

	//テクスチャの破棄
	for (int nCnt = 0; nCnt < (int)m_NumMatModel; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//======================================================
//更新処理
//======================================================
void CModel::Update(void)
{
}

//======================================================
//描画処理
//======================================================
void CModel::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	CPlayer *pPlayer = CGame::GetPlayer();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//ワールドマトリックスを掛け合わせて設定
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	
	if (pPlayer != nullptr)
	{
		if (!pPlayer->GetInside())
		{
			//平面投影
			Shadow();
		}
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデルパーツの描画
		m_MeshModel->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//生成処理
//======================================================
CModel *CModel::Create(const D3DXVECTOR3 &pos)
{
	//動的確保
	CModel *pModel = new CModel;

	if (pModel != nullptr)
	{
		//初期化
		pModel->Init();
		pModel->m_pos = pos;
	}

	return pModel;
}

//======================================================
//初期化処理
//======================================================
void CModel::SetModel(const char *pFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMatModel,
		NULL,
		&m_NumMatModel,
		&m_MeshModel);

	// テクスチャ
	m_pTexture = new LPDIRECT3DTEXTURE9[m_NumMatModel];

	//情報が入ってなかったら
	assert(m_pTexture != nullptr);

	// バッファの先頭ポインタをD3DXMATERIALにキャストして取得
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	// 各メッシュのマテリアル情報を取得する
	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//情報の初期化
		m_pTexture[nCntMat] = nullptr;

		//ポリゴンに貼り付けるテクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			pMat[nCntMat].pTextureFilename,
			&m_pTexture[nCntMat]);
	}
}

//======================================================
//平面投影
//======================================================
void CModel::Shadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ライトの取得
	CLight *pLight = CApplication::GetLight();
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//プレイヤー
	CPlayer *pPlayer = CGame::GetPlayer();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//平面
	D3DXPLANE planeField;

	//情報
	D3DXVECTOR3 normal;
	DWORD ambient;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxShadow);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//法線と平面の一点から平面を作成
	D3DXPlaneFromPointNormal(&planeField, &m_ShadowPos, &normal);

	//ライトと平面から影行列
	D3DXMatrixShadow(&m_mtxShadow, &vecLight, &planeField);

	//ワールドマトリックスを掛け合わせて設定
	D3DXMatrixMultiply(&m_mtxShadow, &m_mtxWorld, &m_mtxShadow);

	//シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxShadow);
	
	//影の位置
	D3DXVec3TransformCoord(&m_Shadow, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &m_mtxShadow);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		// マテリアル情報を保存し、色とライトの色を黒に設定
		D3DMATERIAL9 pMatD3D = pMat[nCntMat].MatD3D;
		pMatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetRenderState(D3DRS_AMBIENT, 0xff000000);	//カラー
		pDevice->SetMaterial(&pMatD3D);

		if (pPlayer->GetShadow())
		{
			//影の描画
			m_MeshModel->DrawSubset(nCntMat);
		}
	}

	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}