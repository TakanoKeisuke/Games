//======================================================
//
// Spike.cpp
// Author : ûüì]
//
//======================================================
#include "enemy.h"
#include "CylinderHitbox.h"
#include "player.h"
#include "game.h"

//======================================================
//RXgN^
//======================================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CEnemy::~CEnemy()
{
}

//======================================================
//ú»
//======================================================
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
{
	//îñÌæ¾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 move = CObjectX::GetMove();

	//sinJ[u
	m_fHeight += D3DX_PI * 0.004f;

	switch (m_type)
	{
	case CGimmick::GIMMICK_TYPE::TYPE_MOVE_X:
		move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
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
void CEnemy::Draw(void)
{
	//`æ
	CObjectX::Draw();
}

//======================================================
//¶¬
//======================================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int range)
{
	//®ImÛ
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		//ÊuÌÝè
		pEnemy->Init();
		pEnemy->SetPos(pos);
		pEnemy->m_fRange = (float)range / 2.0f;

		//_Åñ]ðÝè·é
		D3DXVECTOR3 rotation = D3DXVECTOR3((float)Random(-100, 100), (float)Random(-100, 100), (float)Random(-100, 100));
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.x *= 0.1f;
		rotation.y *= 0.1f;
		rotation.z *= 0.1f;
		pEnemy->SetRotation(rotation);

		//qbg{bNXð¶¬·é
		pEnemy->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 13.0f, 3.0f), CHitbox::TYPE_OBSTACLE, 0, pEnemy, CHitbox::EFFECT_DAMAGE);
	}

	return pEnemy;
}

//======================================================
//Çö
//======================================================
void CEnemy::Chase(void)
{
	//îñÌæ¾
	//CPlayer *pPlayer = CGame::GetPlayer();


}