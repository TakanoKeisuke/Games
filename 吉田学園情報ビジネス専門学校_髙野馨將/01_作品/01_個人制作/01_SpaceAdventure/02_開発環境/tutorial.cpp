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
#include "tutorial.h"
#include "fade.h"
#include "sound.h"
#include "inputPad.h"

//======================================================
//コンストラクタ
//======================================================
CTutorial::CTutorial() : CMode()
{
}

//======================================================
//デストラクタ
//======================================================
CTutorial::~CTutorial()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CTutorial::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\controller.png",
		&m_pTexture[0]);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f)
		,D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f), PRIORITY_3);
	m_pObject2D->BindTexture(m_pTexture[0]);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CTutorial::Uninit(void)
{
	CObject::Flag();
}

//======================================================
//更新処理
//======================================================
void CTutorial::Update(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		CFade::SetFade(CApplication::MODE_TITLE);
	}
}

//======================================================
//生成処理
//======================================================
CTutorial *CTutorial::Create()
{
	//動的確保
	CTutorial *pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		//初期化
		pTutorial->Init();
	}

	return pTutorial;
}
