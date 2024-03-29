//======================================================
//
// Spike.cpp
// Author : ûüì]
//
//======================================================
#include "spike.h"
#include "CylinderHitbox.h"

//======================================================
//RXgN^
//======================================================
CSpike::CSpike(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CSpike::~CSpike()
{
}

//======================================================
//ú»
//======================================================
HRESULT CSpike::Init(void)
{
	//ú»
	m_pHitbox = nullptr;
	m_type = CGimmick::TYPE_MAX;

	//fÌÝè
	LoadModel("data\\model\\spike.x");

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CSpike::Uninit(void)
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
void CSpike::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 move = CObjectX::GetMove();

	if (m_type == CGimmick::GIMMICK_TYPE::TYPE_NONE)
	{
		//sinJ[u
		m_fHeight += (D3DX_PI * 0.004f);
	}
	else
	{
		//sinJ[u
		m_fHeight += (D3DX_PI * 0.004f) *m_fRange;
	}

	switch (m_type)
	{
	case CGimmick::GIMMICK_TYPE::TYPE_MOVE_X:
		move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
		break;

	case CGimmick::GIMMICK_TYPE::TYPE_MOVE_Y:
		move.y = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
		break;

	case CGimmick::GIMMICK_TYPE::TYPE_MOVE_Z:
		move.z = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
		break;

	case CGimmick::GIMMICK_TYPE::TYPE_NONE:
		move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * (m_fRange * 0.1f);
		move.z = cosf((D3DX_PI * 0.25f) + m_fHeight) * (m_fRange * 0.1f);
		break;

	default:
		break;
	}
	if (m_pHitbox != nullptr)
	{//qbg{bNXªnullÅÍÈ©Á½ç
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}
	
	//XV
	CObjectX::Update();

	//Ú®ÊÌÝè
	SetMove(move);
}

//======================================================
//`æ
//======================================================
void CSpike::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CSpike *CSpike::Create(const D3DXVECTOR3 pos, CGimmick::GIMMICK_TYPE type, int range)
{
	//®ImÛ
	CSpike *pSpike = new CSpike;				

	if (pSpike != nullptr)
	{
		//ÊuÌÝè
		pSpike->Init();
		pSpike->SetPos(pos);
		pSpike->m_type = type;
		pSpike->m_fRange = (float)range / 2.0f;

		//_Åñ]ðÝè·é
		D3DXVECTOR3 rotation = D3DXVECTOR3((float)Random(-100, 100), (float)Random(-100, 100), (float)Random(-100, 100));
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.x *= 0.1f;
		rotation.y *= 0.1f;
		rotation.z *= 0.1f;
		pSpike->SetRotation(rotation);

		//qbg{bNXð¶¬·é
		pSpike->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 13.0f, 3.0f), CHitbox::TYPE_OBSTACLE, 0, pSpike, CHitbox::EFFECT_DAMAGE);
	}

	return pSpike;
}