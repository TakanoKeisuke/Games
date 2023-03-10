//======================================================
//
// heal.cpp
// Author : ûüì]
//
//======================================================
#include "heal.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "score.h"

//======================================================
//RXgN^
//======================================================
CHeal::CHeal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CHeal::~CHeal()
{
}

//======================================================
//ú»
//======================================================
HRESULT CHeal::Init(void)
{
	//ú»
	m_pHitbox = nullptr;

	//fÌÝè
	LoadModel("data\\model\\Coin00.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CHeal::Uninit(void)
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
void CHeal::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//qbg{bNXªnullÅÍÈ©Á½ç
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//½è»èªnullÅÍÈ©Á½ç
		if (m_pHitbox->GetCollisionState())
		{//vC[Æ½Á½ê
			//XRAÌÁZ
			CScore *pScore = CGame::GetScore();
			pScore->AddScore(100);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN_GET);

			m_pHitbox->Release();		//qbg{bNXðÁ·
			Uninit();					//RCðÁ·

			return;
		}
	}

	//XV
	CObjectX::Update();
}

//======================================================
//`æ
//======================================================
void CHeal::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CHeal *CHeal::Create(const D3DXVECTOR3 pos)
{
	//®ImÛ
	CHeal *pHeal = new CHeal;

	if (pHeal != nullptr)
	{
		//ÊuÌÝè
		pHeal->Init();
		pHeal->SetPos(pos);

		//¡ñ]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pHeal->SetRotation(rotation);

		//qbg{bNXð¶¬·é
		pHeal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 10.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pHeal, CHitbox::EFFECT_HEAL);
	}

	return pHeal;
}