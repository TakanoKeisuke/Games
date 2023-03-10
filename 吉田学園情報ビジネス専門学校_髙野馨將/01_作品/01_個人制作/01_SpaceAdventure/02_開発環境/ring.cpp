//======================================================
//
// ring.cpp
// Author : ûüì]
//
//======================================================
#include "ring.h"
#include "CylinderHitbox.h"
#include "SphereHitbox.h"

//======================================================
//RXgN^
//======================================================
CRing::CRing(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CRing::~CRing()
{
}

//======================================================
//ú»
//======================================================
HRESULT CRing::Init(void)
{
	//ú»
	m_pHitbox = nullptr;

	//fÌÝè
	LoadModel("data\\model\\jump.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CRing::Uninit(void)
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
void CRing::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//qbg{bNXªnullÅÍÈ©Á½ç
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	//XV
	CObjectX::Update();
}

//======================================================
//`æ
//======================================================
void CRing::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CRing *CRing::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//CX^Xð¶¬·é
	CRing *pSphere = new CRing;

	if (pSphere != nullptr)
	{
		//Ýè
		pSphere->Init();
		pSphere->SetSize(size);
		pSphere->SetPos(pos);
		pSphere->SetRot(rot);

		//¡ñ]
		/*D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pSphere->SetRotation(rotation);*/

		//½è»è
		pSphere->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE, 0, pSphere, CHitbox::EFFECT_FLY);
	}

	return pSphere;
}