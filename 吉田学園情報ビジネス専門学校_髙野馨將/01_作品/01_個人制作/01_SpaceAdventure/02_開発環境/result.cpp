//=============================================================================
//
// リザルト処理
// Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "fade.h"
//#include "sound.h"
#include "game.h"

//静的メンバ変数宣言
bool CResult::b_clear;
//======================================================
//コンストラクタ
//======================================================
CResult::CResult() : CMode()
{
}

//======================================================
//デストラクタ
//======================================================
CResult::~CResult()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CResult::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sea.png",
		&m_pTexture[0]);

	//PlaySound(SOUND_LABEL_BGM001);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f), PRIORITY_3);
	m_pObject2D->BindTexture(m_pTexture[0]);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CResult::Uninit(void)
{
	//StopSound();
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	CObject::Flag();
}

//======================================================
//更新処理
//======================================================
void CResult::Update(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (CInputKeyboard::GetKeyboardPress(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		CFade::SetFade(CApplication::MODE_RANKING);
	}
}

//======================================================
//生成処理
//======================================================
CResult * CResult::Create()
{
	//動的確保
	CResult *pResult = new CResult;

	if (pResult != nullptr)
	{
		//初期化
		pResult->Init();
	}

	return pResult;
}
