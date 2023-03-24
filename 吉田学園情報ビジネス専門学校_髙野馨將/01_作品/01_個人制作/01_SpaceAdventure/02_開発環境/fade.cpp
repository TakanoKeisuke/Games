//=============================================================================
//
// フェード処理
// Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "renderer.h"

//静的メンバ変数
CApplication::MODE CFade::m_ModeNext = {};	//次の画面(モード)
CFade::FADE CFade::m_pFade = {};			//フェードの状態	
D3DXCOLOR CFade::m_Color = {};				//カラー
//======================================================
//コンストラクタ
//======================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_MODE);
}

//======================================================
//デストラクタ
//======================================================
CFade::~CFade()
{
}

//======================================================
//初期化処理
//======================================================
void CFade::Init(CApplication::MODE modeNext)
{
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),PRIORITY_5);

	//初期化
	m_pFade = FADE_IN;		//フェードイン状態に
	m_ModeNext = modeNext;
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	m_pObject2D->SetPos(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pObject2D->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D->SetCol(m_Color);
	m_pObject2D->SetType(CObject::OBJTYPE_MODE);

	//モードの設定
	CApplication::SetMode(m_ModeNext);
}

//======================================================
//終了処理
//======================================================
void CFade::Uninit(void)
{
	//解放処理
	CObject::Flag();
}

//======================================================
//初期化処理
//======================================================
void CFade::Update(void)
{
	if (m_pFade != FADE_NONE)
	{
		if (m_pFade == FADE_IN)
		{//フェードイン状態
			m_Color.a -= 0.07f;		//ポリゴンを透明にしていく
			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				m_pFade = FADE_NONE;		//何もしていない状態に
			}
		}
		else if (m_pFade == FADE_OUT)
		{ //フェードアウト状態
			m_Color.a += 0.07f;		//ポリゴンを不透明にしていく
			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				m_pFade = FADE_IN;		//フェードイン状態に

				//モード設定(次の画面に移行)
				CApplication::SetMode(m_ModeNext);
			}
		}
		m_pObject2D->SetCol(m_Color);
	}
}

//======================================================
//初期化処理
//======================================================
void CFade::SetFade(CApplication::MODE modeNext)
{
	m_pFade = FADE_OUT;								//フェードアウト状態に
	m_ModeNext = modeNext;							//次の画面(モード)を設定
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒いポリゴン(透明)にしておく
}

//======================================================
//初期化処理
//======================================================
CFade * CFade::Create(CApplication::MODE modeNext)
{
	//動的確保
	CFade *pFade = new CFade;

	if (pFade != nullptr)
	{
		//初期化
		pFade->Init(modeNext);
	}

	return pFade;
}
