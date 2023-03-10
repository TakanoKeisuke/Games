//======================================================
//
// heal.cpp
// Author : ûüì]
//
//======================================================
#include "checkpoint.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "particle.h"
#include "score.h"

//======================================================
//RXgN^
//======================================================
CCheckpoint::CCheckpoint(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CCheckpoint::~CCheckpoint()
{
}

//======================================================
//ú»
//======================================================
HRESULT CCheckpoint::Init(void)
{
	//ú»
	m_pHitbox = nullptr;

	//fÌÝè
	LoadModel("data\\model\\checkpoint.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CCheckpoint::Uninit(void)
{
	//qbg{bNXÌjü
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//ðú
	Flag();
}

//======================================================
//XV
//======================================================
void CCheckpoint::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 ParticlePos = pos + D3DXVECTOR3(0.0f,30.0f,0.0f);

	//p[eBNÌ¶¬
	CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, ParticlePos, 10, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));

	if (m_pHitbox != nullptr)
	{//qbg{bNXªnullÅÍÈ©Á½ç
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//½è»èªnullÅÍÈ©Á½ç
		if (m_pHitbox->GetCollisionState())
		{//vC[Æ½Á½ê
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHECK);

			m_pHitbox->Release();		//qbg{bNXðÁ·
			Uninit();					//©gðÁ·

			return;
		}
	}

	//XV
	CObjectX::Update();
}

//======================================================
//`æ
//======================================================
void CCheckpoint::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CCheckpoint *CCheckpoint::Create(const D3DXVECTOR3 pos)
{
	//®ImÛ
	CCheckpoint *pCheck = new CCheckpoint;

	if (pCheck != nullptr)
	{
		//ÊuÌÝè
		pCheck->Init();
		pCheck->SetPos(pos);

		//qbg{bNXð¶¬·é
		pCheck->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 7.0f, 2.0f), CHitbox::TYPE_OBSTACLE, 0, pCheck, CHitbox::EFFECT_CHECKPOINT);
	}

	return pCheck;
}