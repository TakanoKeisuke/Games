//======================================================
//
// secret_item.cpp
// Author : ûüì]
//
//======================================================
#include "secret_item.h"
#include "CylinderHitbox.h"
#include "ItemFrame.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "score.h"

//======================================================
//RXgN^
//======================================================
CSecret_item::CSecret_item(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CSecret_item::~CSecret_item()
{
}

//======================================================
//ú»
//======================================================
HRESULT CSecret_item::Init(void)
{
	//ú»
	m_pHitbox = nullptr;
	m_bCollision = false;
	m_nNumber = 0;

	//fÌÝè
	LoadModel("data\\model\\Coin01.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CSecret_item::Uninit(void)
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
void CSecret_item::Update(void)
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
			pScore->AddScore(1000);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//qbg{bNXðÁ·
			CItemFrame *pFrame = CGame::GetFrame(m_nNumber);	//t[ÉZbg·é
			pFrame->SetGetItem(true);
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
void CSecret_item::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CSecret_item *CSecret_item::Create(const D3DXVECTOR3 pos, int number)
{
	//®ImÛ
	CSecret_item *pItem = new CSecret_item;

	if (pItem != nullptr)
	{
		//ÊuÌÝè
		pItem->Init();
		pItem->m_nNumber = number;
		pItem->SetPos(pos);

		//¡ñ]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pItem->SetRotation(rotation);

		//qbg{bNXð¶¬·é
		pItem->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(8.0f, 8.0f, 8.0f), CHitbox::TYPE_OBSTACLE, 0, pItem, CHitbox::EFFECT_HEAL);
	}

	return pItem;
}