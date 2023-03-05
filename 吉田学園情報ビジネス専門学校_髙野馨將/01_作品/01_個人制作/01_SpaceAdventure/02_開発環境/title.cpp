//=============================================================================
//
// リザルト処理
// Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "input_keyboard.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "title.h"
#include "fade.h"
#include "inputPad.h"
#include "planet.h"
#include "player.h"
#include "sound.h"

//======================================================
//コンストラクタ
//======================================================
CTitle::CTitle() : CMode()
{
}

//======================================================
//デストラクタ
//======================================================
CTitle::~CTitle()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CTitle::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//初期化
	m_nSelect = 0;
	m_nCounter = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\titlelogo.png",
		&m_pTexture[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\start.png",
		&m_pTexture[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial.png",
		&m_pTexture[2]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.jpg",
		&m_pTexture[3]);

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 250.0f, 0.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f),PRIORITY_4);
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f), PRIORITY_4);
	m_pObject2D[1]->BindTexture(m_pTexture[1]);

	m_pObject2D[2] = CObject2D::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f), PRIORITY_4);
	m_pObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	m_pObject2D[2]->BindTexture(m_pTexture[2]);

	m_pObject2D[3] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f), PRIORITY_3);
	m_pObject2D[3]->BindTexture(m_pTexture[3]);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
	
	//破棄処理
	CObject::Flag();
}

//======================================================
//更新処理
//======================================================
void CTitle::Update(void)
{
	if ((CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT))
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 0) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
	{//Dキーが押された
		if (m_nSelect < 1 && CFade::GetFade() == CFade::FADE_NONE)
		{
			m_nSelect++;
			m_pObject2D[m_nSelect]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
	}
	else if ((CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputKeyboard::GetKeyboardTrigger(DIK_LEFT))
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 0) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
	{//Aキーが押された
		if (m_nSelect > 0 && CFade::GetFade() == CFade::FADE_NONE)
		{
			m_pObject2D[m_nSelect + 1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_nSelect--;
		}
	}

	switch (m_nSelect)
	{
	case 0:
		//選択しているポリゴンを半透明にする
		m_pObject2D[1]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		//決定キー(ENTERキー)が押されたかどうか
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
		{
			//モード設定
			CFade::SetFade(CApplication::MODE_GAME);
		}
		break;

	case 1:
		//選択しているポリゴンを半透明にする
		m_pObject2D[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//決定キー(ENTERキー)が押されたかどうか
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
		{
			//モード設定
			CFade::SetFade(CApplication::MODE_TUTORIAL);
		}
		break;
	}
}

//======================================================
//描画処理
//======================================================
void CTitle::Draw(void)
{
}

//======================================================
//生成処理
//======================================================
CTitle *CTitle::Create()
{
	//動的確保
	CTitle *pTitle = new CTitle;

	if (pTitle != nullptr)
	{
		//初期化
		pTitle->Init();
	}

	return pTitle;
}
