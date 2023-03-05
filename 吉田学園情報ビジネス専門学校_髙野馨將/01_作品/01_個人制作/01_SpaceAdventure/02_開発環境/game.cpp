//=============================================================================
//
// Q[
// Author:ûüì]
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

//ÃIoÏé¾
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
//RXgN^
//======================================================
CGame::CGame() : CMode()
{
}

//======================================================
//fXgN^
//======================================================
CGame::~CGame()
{
}

//======================================================
//ú»
//======================================================
HRESULT CGame::Init()
{
	//vC[
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(35.0f, 35.0f, 35.0f), 3);

	//Xe[Wzu
	m_pStage = CStage::Create();

	//wi
	m_pMesh_sphere[0] = CMesh_sphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(9000.0f, 0.0f, 9000.0f), D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f), CMesh_sphere::SPHERE_DOWN);
	m_pMesh_sphere[0]->LoadTexture("data\\TEXTURE\\sky.jpg");
	m_pMesh_sphere[1] = CMesh_sphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(9000.0f, 0.0f, 9000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMesh_sphere::SPHERE_UP);
	m_pMesh_sphere[1]->LoadTexture("data\\TEXTURE\\sky.jpg");

	//HPQ[W
	m_pLife = CLife_gauge::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	//^C}[
	m_pTimer = CTimer::Create(D3DXVECTOR3(1280.0f, 35.0f, 0.0f), D3DXVECTOR3(40.0f, 70.0f, 0.0f));

	//XRA
	m_pScore = CScore::Create(D3DXVECTOR3(1280.0f, 90.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f));

	//BµACeÌg
	for (int nCnt = 0; nCnt < MAX_SECRET; nCnt++)
	{
		m_pFrame[nCnt] = CItemFrame::Create(D3DXVECTOR3(50.0f + (80.0f * nCnt), 150.0f, 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f));
	}

	//JÌú»
	CApplication::GetCamera()->Init();

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CGame::Uninit()
{
	//Q[I¹Ì^CâCtÉ¶ÄXRAÌÁZð·é
	int nScore = 0;
	if (m_pTimer != nullptr && m_pScore != nullptr)
	{
		nScore = (m_pTimer->GetTimer()) * 10;
		nScore += m_pPlayer->GetLife() * 100;
		m_pScore->AddScore(nScore);
	}

	//vC[Ìjü
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	//Ìjü
	if (m_pSphere != nullptr)
	{
		m_pSphere->Uninit();
		m_pSphere = nullptr;
	}

	//bVXtBAÌjü
	for (int nCnt = 0; nCnt < MAX_HALF_SPHERE; nCnt++)
	{
		if (m_pMesh_sphere != nullptr)
		{
			m_pMesh_sphere[nCnt]->Uninit();
			m_pMesh_sphere[nCnt] = nullptr;
		}
	}

	//HPQ[WÌjü
	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		m_pLife = nullptr;
	}

	//XRAÌjü
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	//^C}[Ìjü
	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	//^C}[Ìjü
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	//t[Ìjü
	for (int nCnt = 0; nCnt < MAX_SECRET; nCnt++)
	{
		if (m_pFrame[nCnt] != nullptr)
		{
			m_pFrame[nCnt]->Uninit();
			m_pFrame[nCnt] = nullptr;
		}
	}

	//p[eBNÌjü
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (m_pParticle[nCnt] != nullptr)
		{
			m_pParticle[nCnt]->Uninit();
			m_pParticle[nCnt] = nullptr;
		}
	}

	if (m_pStage != nullptr)
	{// Xe[WÌI¹
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}
	
	//ðú
	CObject::Flag();
}

//======================================================
//XV
//======================================================
void CGame::Update()
{

#ifdef _DEBUG
	//èL[(ENTERL[)ª³ê½©Ç¤©
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//[hÝè
		CFade::SetFade(CApplication::MODE_RESULT);
	}
#endif // _DEBUG

	//XV
	m_pStage->Update();
}

//======================================================
//`æ
//======================================================
void CGame::Draw()
{
}

//======================================================
//Q[ÌÝè
//======================================================
CGame *CGame::Create()
{
	//®ImÛ
	CGame *pGame = new CGame;

	if (pGame != nullptr)
	{
		//ú»
		pGame->Init();
	}

	return pGame;
}