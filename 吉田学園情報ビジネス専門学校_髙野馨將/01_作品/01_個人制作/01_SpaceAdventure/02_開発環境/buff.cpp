//======================================================
//
// Buff.cpp
// Author : ûüì]
//
//======================================================
#include "buff.h"
#include "stage.h"
#include "application.h"
#include "sound.h"
#include<vector>

//======================================================
//RXgN^
//======================================================
CBuff::CBuff(int nPriority) : CObjectX(nPriority)
{
}


//======================================================
//fXgN^
//======================================================
CBuff::~CBuff()
{
}

//======================================================
//ú»
//======================================================
HRESULT CBuff::Init(void)
{
	//ú»
	m_pHitbox = nullptr;
	m_bInvisible = false;

	switch (m_effect)
	{
	case CHitbox::EFFECT_JUMP:
		//fÌÝè
		LoadModel("data\\model\\Coin02.x");
		break;

	case CHitbox::EFFECT_SPEED:
		//fÌÝè
		LoadModel("data\\model\\Coin03.x");
		break;

	default:
		break;
	}

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CBuff::Uninit(void)
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
void CBuff::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	std::vector<CBuff*> pBuff = CStage::GetBuff();

	if (m_pHitbox != nullptr)
	{//qbg{bNXªnullÅÍÈ©Á½ç
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//½è»èªnullÅÍÈ©Á½ç
		if (m_pHitbox->GetCollisionState())
		{//vC[Æ½Á½ê
			m_bInvisible = true;
			m_nInvincibleCnt = 360;

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

			m_pHitbox->Release();		//qbg{bNXðÁ·
			m_pHitbox = nullptr;
		}
	}

	//³GÔ
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//JE^[ÌXV
	}

	//êèÔoÂÆX|[·é
	for (int nCnt = 0; nCnt < CStage::m_nMaxBuff; nCnt++)
	{
		if (pBuff[nCnt]->m_nInvincibleCnt <= 0 && pBuff[nCnt]->m_pHitbox == nullptr)
		{
			pBuff[nCnt]->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff[nCnt], m_effect);
		}
	}

	//³GÔ
	if (m_nInvincibleCnt <= 60)
	{
		m_bInvisible = false;
	}

	//XV
	CObjectX::Update();
}

//======================================================
//`æ
//======================================================
void CBuff::Draw(void)
{
	if (!m_bInvisible)
	{
		if (m_nInvincibleCnt % 10 <= 5)
		//`æ
		CObjectX::Draw();
	}
}

//======================================================
//¶¬
//======================================================
CBuff *CBuff::Create(const D3DXVECTOR3 pos, CHitbox::INTERACTION_EFFECT effect)
{
	//®ImÛ
	CBuff *pBuff = new CBuff;

	if (pBuff != nullptr)
	{
		//ÊuÌÝè
		pBuff->m_effect = effect;
		pBuff->Init();
		pBuff->SetPos(pos);

		//¡ñ]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pBuff->SetRotation(rotation);

		//qbg{bNXð¶¬·é
		pBuff->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff, effect);
	}

	return pBuff;
}