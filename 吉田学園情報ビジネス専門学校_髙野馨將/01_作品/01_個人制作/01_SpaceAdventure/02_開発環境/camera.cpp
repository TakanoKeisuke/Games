//========================================================
//
//カメラ
//Author:髙野馨將
//
//========================================================
#include "camera.h"
#include <math.h>
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "planet.h"
#include "stage.h"
#include "player.h"
#include "inputPad.h"
#include <stdlib.h>
#include <time.h>

//======================================================
//コンストラクタ
//======================================================
CCamera::CCamera()
{
	//クリア

}

//======================================================
//デストラクタ
//======================================================
CCamera::~CCamera()
{//何も書かない
}

//====================================
//カメラの初期化処理
//====================================
void CCamera::Init(void)
{
	//視点・注視点・上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -340.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//角度と距離
	m_rot = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
	m_fDistance = sqrtf(((m_posR.x - m_posV.x) * (m_posR.x - m_posV.x)) +
		((m_posR.z - m_posV.z) * (m_posR.z - m_posV.z)));

	//初期化
	m_move = D3DXVECTOR3(2.0f, 0.0f, 0.0f);
	posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 200.0f);

	m_bLock = false;
}

//====================================
//カメラの終了処理
//====================================
void CCamera::Uninit(void)
{
}

//====================================
//カメラの更新処理
//====================================
void CCamera::Update(void)
{
	//視点の旋回
	if (CInputKeyboard::GetKeyboardPress(DIK_Z) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).x > 0.2f)
	{//Zキーが押された
		m_rot.y += D3DX_PI / 100.0f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_C) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).x < -0.2f)
	{//Cキーが押された
		m_rot.y -= 0.03f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_N) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).y > 0.2f)
	{//Nキーが押された
		m_rot.x += 0.05f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_M) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).y < -0.2f)
	{//Mキーが押された
		m_rot.x -= 0.05f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}

	//上下の反転の制御
	if (m_rot.x > 0.6f)
	{
		m_rot.x = 0.6f;
	}
	else if (m_rot.x < -0.3f)
	{
		m_rot.x = -0.3f;
	}

	//角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//プレイヤーの情報を取得
	CPlayer *pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		m_rotDest.y = pPlayer->GetRot().y + D3DX_PI;

	}
	//正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//正面を向く
	if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT_THUMB, 0))
	{
		m_rot.y += (m_rotDest.y - m_rot.y);
		m_rot.x = 0.0f;
	}

	//正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//近くの惑星をロックオンする処理
	TargetPlanet();

	//減衰
	m_posR += (m_posRDest - m_posR) * 0.1f;
	m_posV += (m_posVDest - m_posV) * 0.1f;
}

//====================================
//近くの惑星をロックオンする処理
//====================================
void CCamera::TargetPlanet(void)
{
	//情報取得
	std::vector<CPlanet*> pPlanet = CStage::GetPlanet();	//それぞれの惑星の情報
	std::vector<CPlanet*> pNearPlanet;						//最も近い惑星の情報
	pNearPlanet.resize(CStage::m_nMaxPlanet);				//惑星の最大数分配列を確保する
	CPlayer *pPlayer = CGame::GetPlayer();					//プレイヤーの情報

	if (pPlayer != nullptr)
	{
		//配列の動的確保
		std::vector<float> fDistance;
		std::vector<D3DXVECTOR3> PlanetPos;
		//情報の取得
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerRot = pPlayer->GetRot();
		//配列の大きさの設定
		fDistance.resize(CStage::m_nMaxPlanet);
		PlanetPos.resize(CStage::m_nMaxPlanet);

		//惑星とプレイヤーの距離
		for (int nCnt = 0; nCnt < CStage::m_nMaxPlanet; nCnt++)
		{
			if (pPlanet[nCnt] != nullptr)
			{
				fDistance[nCnt] = pPlanet[nCnt]->TargetDistance(pPlayer);
			}
		}

		//距離の比較
		for (int nCount = 0; nCount < CStage::m_nMaxPlanet - 1; nCount++)
		{
			for (int nCount2 = nCount + 1; nCount2 < CStage::m_nMaxPlanet; nCount2++)
			{
				if (fDistance[nCount] < fDistance[nCount2])
				{
					pNearPlanet[0] = CStage::GetPlanet()[nCount];
				}
				else
				{
					pNearPlanet[0] = CStage::GetPlanet()[nCount2];
				}
			}
		}
		bool bInside = false;
		//最も近い惑星の範囲内にいるか
		if (pNearPlanet[0] != nullptr)
		{
			bInside = pNearPlanet[0]->GetInside();
		}

		if (bInside)
		{
			D3DXVECTOR3 sub;
			sub = (PlayerPos - pNearPlanet[0]->GetPos());

			//球の中心をロックオン
			sub.y = 0.0f;
			D3DXVec3Normalize(&sub, &sub);
			sub *= 300.0f;
			sub.y = 50.0f;
			m_posVDest = PlayerPos + sub;
			m_posRDest = pNearPlanet[0]->GetPos();
			m_rot.y = atan2f(sub.x, sub.z);
		}
		else
		{//平面の時のカメラ
			//計算用マトリックス
			D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

			//ワールドマトリックの初期化
			D3DXMatrixIdentity(&mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, PlayerPos.x, PlayerPos.y, PlayerPos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

			//ワールド変換行列
			D3DXVec3TransformCoord(&m_posVDest, &posV, &mtxWorld);
			D3DXVec3TransformCoord(&m_posRDest, &posR, &mtxWorld);
		}
	}
}

//====================================
//カメラの設定処理
//====================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 adjustPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_nQuakeFrameCount > 0)
	{
		m_nQuakeFrameCount--;
		////乱数で揺れの大きさを変える
		adjustPos.x = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.y = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.z = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
	}
	//ビューマトリックの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックの生成
	D3DXVECTOR3 PosV = (adjustPos + m_posV);
	D3DXVECTOR3 PosR = (adjustPos + m_posR);

	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,
		&PosR,
		&m_vecU);
	
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//プロジェクションマトリックの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),		//視野角
		(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,		//アスペクト比
		10.0f,		//ニア
		100000.0f);	//ファー
	//プロジェクションマトリックの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//====================================
//カメラを揺らす値の設定
//====================================
void CCamera::ShakeCamera(int nFrame, float fMagnitude)
{
	m_nQuakeFrameCount = nFrame;
	m_fQuakeMagnitude = fMagnitude;
}

//====================================
//揺れの停止
//====================================
void CCamera::StopShake(void)
{
	m_fQuakeMagnitude = 0.0f;
	m_nQuakeFrameCount = 0;
}

//====================================
//視点注視点の設定
//====================================
void CCamera::SetPos(const D3DXVECTOR3 PosV, const D3DXVECTOR3 PosR)
{
	m_posV = PosV;
	m_posR = PosR;
}