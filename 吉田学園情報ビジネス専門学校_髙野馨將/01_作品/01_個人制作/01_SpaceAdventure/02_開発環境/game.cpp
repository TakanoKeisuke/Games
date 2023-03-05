//=============================================================================
//
// ゲーム処理
// Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "renderer.h"
#include "fade.h"
#include "sphere.h"
#include "mesh_sphere.h"
#include "planet.h"
#include "goal.h"
#include "spike.h"
#include "heal.h"
#include "ring.h"
#include "life_gauge.h"
#include "buff.h"
#include "hitbox.h"
#include "gimmick.h"
#include "secret_item.h"
#include "ItemFrame.h"
#include "stage.h"
#include "particle.h"
#include "timer.h"
#include "score.h"
#include "enemy.h"
#include "sound.h"

//静的メンバ変数宣言
CItemFrame *CGame::m_pFrame[MAX_SECRET] = {};
CParticle *CGame::m_pParticle[MAX_PARTICLE] = {};
CPlayer *CGame::m_pPlayer = nullptr;
CSphere *CGame::m_pSphere = nullptr;
CScore *CGame::m_pScore = nullptr;
CMesh_sphere *CGame::m_pMesh_sphere[MAX_HALF_SPHERE] = {};
CLife_gauge *CGame::m_pLife = nullptr;
CTimer *CGame::m_pTimer = nullptr;
CEnemy *CGame::m_pEnemy = nullptr;
CStage *CGame::m_pStage = nullptr;
//======================================================
//コンストラクタ
//======================================================
CGame::CGame() : CMode()
{
}

//======================================================
//デストラクタ
//======================================================
CGame::~CGame()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CGame::Init()
{
	//プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(35.0f, 35.0f, 35.0f), 3);

	//ステージ配置
	m_pStage = CStage::Create();

	//背景
	m_pMesh_sphere[0] = CMesh_sphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(9000.0f, 0.0f, 9000.0f), D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f), CMesh_sphere::SPHERE_DOWN);
	m_pMesh_sphere[0]->LoadTexture("data\\TEXTURE\\sky.jpg");
	m_pMesh_sphere[1] = CMesh_sphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(9000.0f, 0.0f, 9000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMesh_sphere::SPHERE_UP);
	m_pMesh_sphere[1]->LoadTexture("data\\TEXTURE\\sky.jpg");

	//HPゲージ
	m_pLife = CLife_gauge::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	//タイマー
	m_pTimer = CTimer::Create(D3DXVECTOR3(1280.0f, 35.0f, 0.0f), D3DXVECTOR3(40.0f, 70.0f, 0.0f));

	//スコア
	m_pScore = CScore::Create(D3DXVECTOR3(1280.0f, 90.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));

	//隠しアイテムの枠
	for (int nCnt = 0; nCnt < MAX_SECRET; nCnt++)
	{
		m_pFrame[nCnt] = CItemFrame::Create(D3DXVECTOR3(50.0f + (80.0f * nCnt), 150.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f));
	}

	//カメラの初期化
	CApplication::GetCamera()->Init();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CGame::Uninit()
{
	//ゲーム終了時のタイムやライフに応じてスコアの加算をする
	int nScore = 0;
	if (m_pTimer != nullptr && m_pScore != nullptr)
	{
		nScore = (m_pTimer->GetTimer()) * 10;
		nScore += m_pPlayer->GetLife() * 100;
		m_pScore->AddScore(nScore);
	}

	//プレイヤーの破棄処理
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	//球の破棄処理
	if (m_pSphere != nullptr)
	{
		m_pSphere->Uninit();
		m_pSphere = nullptr;
	}

	//メッシュスフィアの破棄処理
	for (int nCnt = 0; nCnt < MAX_HALF_SPHERE; nCnt++)
	{
		if (m_pMesh_sphere != nullptr)
		{
			m_pMesh_sphere[nCnt]->Uninit();
			m_pMesh_sphere[nCnt] = nullptr;
		}
	}

	//HPゲージの破棄処理
	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	//スコアの破棄処理
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//タイマーの破棄処理
	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	//タイマーの破棄処理
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	//フレームの破棄処理
	for (int nCnt = 0; nCnt < MAX_SECRET; nCnt++)
	{
		if (m_pFrame[nCnt] != nullptr)
		{
			m_pFrame[nCnt]->Uninit();
			m_pFrame[nCnt] = nullptr;
		}
	}

	//パーティクルの破棄処理
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (m_pParticle[nCnt] != nullptr)
		{
			m_pParticle[nCnt]->Uninit();
			m_pParticle[nCnt] = nullptr;
		}
	}

	if (m_pStage != nullptr)
	{// ステージの終了処理
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}
	
	//解放処理
	CObject::Flag();
}

//======================================================
//更新処理
//======================================================
void CGame::Update()
{

#ifdef _DEBUG
	//決定キー(ENTERキー)が押されたかどうか
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		CFade::SetFade(CApplication::MODE_RESULT);
	}
#endif // _DEBUG

	//更新処理
	m_pStage->Update();
}

//======================================================
//描画処理
//======================================================
void CGame::Draw()
{
}

//======================================================
//ゲームの設定
//======================================================
CGame *CGame::Create()
{
	//動的確保
	CGame *pGame = new CGame;

	if (pGame != nullptr)
	{
		//初期化
		pGame->Init();
	}

	return pGame;
}