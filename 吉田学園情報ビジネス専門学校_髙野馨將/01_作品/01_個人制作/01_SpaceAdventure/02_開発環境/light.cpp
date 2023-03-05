//========================================================
//
//ライト
//Author:髙野馨將
//
//========================================================
#include "light.h"
#include "application.h"

//======================================================
//コンストラクタ
//======================================================
CLight::CLight()
{
}

//======================================================
//デストラクタ
//======================================================
CLight::~CLight()
{//何も書かない
}

//====================================
//ライトの初期化処理
//====================================
void CLight::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];				//ライトの方向ベクトル
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトをクリア
		ZeroMemory(&m_aLight[0], sizeof(m_aLight));
		//ライトの種類を設定
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		//ライトの拡散光を設定(色)
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(0.5f, -1.0f, 0.5f);
		//正視化する(大きさ1のベクトルにする)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		m_aLight[nCntLight].Direction = vecDir[nCntLight];
		//ライトを設定
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		//ライトを有効化する
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//====================================
//ライトの終了処理
//====================================
void CLight::Uninit(void)
{
}

//====================================
//ライトの更新処理
//====================================
void CLight::Update(void)
{
}