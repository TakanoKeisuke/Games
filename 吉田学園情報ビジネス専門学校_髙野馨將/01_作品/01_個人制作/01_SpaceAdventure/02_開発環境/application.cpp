//=============================================================================
//
//アプリケーション(マネージャー)
//Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "object3d.h"
#include "objectX.h"
#include "player.h"
#include "billboard.h"
#include "debug.h"
#include "object2D.h"
#include "model.h"
#include "meshfield.h"
#include "sphere.h"
#include "result.h"
#include "title.h"
#include "game.h"
#include "mode.h"
#include "fade.h"
#include "motion.h"
#include "light.h"
#include "sound.h"
#include "inputPad.h"
#include "tutorial.h"
#include "ranking.h"

//静的メンバ変数宣言
CRenderer *CApplication::m_pRenderer = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CDebugProc *CApplication::m_pDebug = nullptr;
CObject *CApplication::m_pMode = nullptr;
CSound *CApplication::m_pSound = nullptr;
CInput *CApplication::m_pInput[2] = {};
CInputPad* CApplication::m_pPad = nullptr;
CApplication::MODE CApplication::m_mode = CApplication::MODE_TITLE;
//======================================================
//コンストラクタ
//======================================================
CApplication::CApplication()
{
}

//======================================================
//デストラクタ
//======================================================
CApplication::~CApplication()
{//何も書かない
}

//======================================================
//初期化処理
//======================================================
HRESULT CApplication::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	//キーボードインスタンスの生成処理 
	m_pInput[0] = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//動的確保
	m_pRenderer = new CRenderer;

	if (m_pRenderer != nullptr)
	{
		//レンダラーの初期化
		m_pRenderer->Init(hWnd, bWindow);
	}

	//動的確保
	m_pLight = new CLight;

	if (m_pLight != nullptr)
	{
		//ライトの初期化
		m_pLight->Init();
	}

	//動的確保
	m_pCamera = new CCamera;

	if (m_pCamera != nullptr)
	{
		//カメラの初期化
		m_pCamera->Init();
	}

	//動的確保
	m_pDebug = new CDebugProc;

	if (m_pDebug != nullptr)
	{
		//デバック表示の初期化
		m_pDebug->Init();
	}

	//動的確保
	m_pPad = new CInputPad;

	if (m_pPad != nullptr)
	{//パッドの初期化処理
		m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	}

	//モーションのファイル読み込み
	CMotion::LoadFile();

	//サウンドの生成
	m_pSound = CSound::Create(hWnd);

	//モードの設定
	CFade::Create(m_mode);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CApplication::Uninit()
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			//インプットの終了処理
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pPad != nullptr)
	{//パッドの破棄処理
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		//カメラの終了処理
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pLight != nullptr)
	{
		//ライトの終了処理
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//サウンドの破棄処理
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();				//終了処理
		delete m_pSound;				//破棄する
		m_pSound = nullptr;				//nullにする
	}

	if (m_pDebug != nullptr)
	{
		//デバック表示の終了処理
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//objectの全開放
	CObject::ReleaseAll();
}

//======================================================
//更新処理
//======================================================
void CApplication::Update()
{
	//入力処理の更新処理
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}
	//パッドの更新処理
	if (m_pPad != nullptr)
	{
		m_pPad->Update();
	}
	//レンダラーの更新処理
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	//カメラの更新処理
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	//ライトの更新処理
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
}

//======================================================
//描画処理
//======================================================
void CApplication::Draw()
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//======================================================
//モード設定
//======================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	//モードの解放
	CObject::ReleaseMode();

	m_mode = mode;

	if (m_pSound != nullptr && m_mode != MODE_TUTORIAL)
	{// 使用中のサウンド停止
		m_pSound->Stop();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;

	case MODE_GAME:
		m_pMode = CGame::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		break;

	//case MODE_RESULT:
	//	m_pMode = CResult::Create();	
	//	break;

	case MODE_RESULT:
		m_pMode = CRanking::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
		break;

	default:
		break;
	}
}