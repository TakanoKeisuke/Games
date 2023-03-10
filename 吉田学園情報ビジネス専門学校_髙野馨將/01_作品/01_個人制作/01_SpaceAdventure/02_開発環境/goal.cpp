//======================================================
//
// goal.cpp
// Author : ûüì]
//
//======================================================
#include "goal.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//======================================================
//RXgN^
//======================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CGoal::~CGoal()
{
}

//======================================================
//ú»
//======================================================
HRESULT CGoal::Init(void)
{
	//ú»
	m_pHitbox = nullptr;

	//fÌÝè
	LoadModel("data\\model\\star000.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CGoal::Uninit(void)
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
//XV
//======================================================
void CGoal::Update(void)
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
			 //SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//qbg{bNXðÁ·
			Uninit();					//RCðÁ·

			return;
		}
	}

	//XV
	CObjectX::Update();
}

//======================================================
//`æ
//======================================================
void CGoal::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//CX^Xð¶¬·é
	CGoal *pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		//Ýè
		pGoal->Init();
		pGoal->SetSize(size);
		pGoal->SetPos(pos);

		//¡ñ]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f,1.0f,0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pGoal->SetRotation(rotation);

		//½è»è
		pGoal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE,0, pGoal,CHitbox::EFFECT_GOAL);
	}

	return pGoal;
}