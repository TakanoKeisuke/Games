//======================================================
//
// gimmick.cpp
// Author : ûüì]
//
//======================================================
#include "gimmick.h"
#include "player.h"
#include "game.h"
#include "application.h"

//======================================================
//RXgN^
//======================================================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//fXgN^
//======================================================
CGimmick::~CGimmick()
{
}

//======================================================
//ú»
//======================================================
HRESULT CGimmick::Init(void)
{
	//ú»
	OriginPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nFallTime = 120;
	m_nRespawnTime = 0;
	m_fHeight = 0.0f;
	m_fRange = 0.0f;
	m_fSpeed = 1.0f;
	m_bLanding = false;
	m_bCountStart = false;
	m_bRespawn = false;
	CObjectX::Init();

	//fÌÝè
	if (m_type == TYPE_FALL)
	{
		LoadModel("data\\model\\FallFloor.x");
	}
	else if (m_type == TYPE_FALL_LONG)
	{
		LoadModel("data\\model\\LongFallFloor.x");
	}
	else
	{
		LoadModel("data\\model\\MoveFloor.x");
	}

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CGimmick::Uninit(void)
{
	//ðú
	Flag();
}

//======================================================
//XV
//======================================================
void CGimmick::Update(void)
{
	//íÞ²ÆÌ
	TypeEffect();

	//XV
	CObjectX::Update();

	//½è»èÌL³
	if (m_nInvincibleCnt > 0)
	{//_ÅÍ³µ
		m_nInvincibleCnt--;
	}
	else if (m_nInvincibleCnt == 0)
	{
		//µoµ
		m_bLanding = PushPlayer();
	}

	//Ä¶¬
	if (m_bRespawn)
	{
		Respawn(OriginPos,m_feffect,m_type);
		m_nInvincibleCnt = 60;
	}

	//Ä¶¬ÔªêèÔÉBµ½ç
	if (m_nRespawnTime >= 60)
	{
		m_nRespawnTime = 0;
		m_bRespawn = true;
	}

	//°ªêèÌ³æè¿½ç
	if (GetPos().y <= -200.0f)
	{
		//X|[³¹é
		m_nRespawnTime++;
	}

}

//======================================================
//`æ
//======================================================
void CGimmick::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{
		//`æ
		CObjectX::Draw();
	}
}

//======================================================
//¶¬
//======================================================
CGimmick *CGimmick::Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed)
{
	//®ImÛ
	CGimmick *pGimmick = new CGimmick;

	if (pGimmick != nullptr)
	{
		//ÊuÌÝè
		pGimmick->m_type = type;
		pGimmick->Init();
		pGimmick->OriginPos = pos;
		pGimmick->m_feffect = effect;
		pGimmick->m_fSpeed = speed;
		pGimmick->SetPos(pos);
		if (type == TYPE_FALL || type == TYPE_FALL_LONG)
		{
			pGimmick->m_nFallTime = (int)effect;
		}
		else
		{
			pGimmick->m_fRange = effect;
		}
	}

	return pGimmick;
}

//======================================================
//íÞÌøÊ
//======================================================
void CGimmick::TypeEffect(void)
{
	//îñÌæ¾
	D3DXVECTOR3 move = CObjectX::GetMove();
	//sinJ[u
	m_fHeight += D3DX_PI * (0.004f * m_fSpeed);

	if (m_type != TYPE_NONE)
	{
		switch (m_type)
		{
		case CGimmick::TYPE_MOVE_X:
			move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
			break;

		case CGimmick::TYPE_MOVE_Y:
			move.y = sinf((D3DX_PI * 0.25f) + m_fHeight)  * m_fRange;
			break;

		case CGimmick::TYPE_MOVE_Z:
			move.z = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
			break;

		case CGimmick::TYPE_FALL:
			//º
			Fall();

			//¿éÔÉBµ½ç
			if (m_nFallTime < 0)
			{
				//Æ·
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		case CGimmick::TYPE_FALL_LONG:
			//º
			Fall();

			//¿éÔÉBµ½ç
			if (m_nFallTime < 0)
			{
				//Æ·
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		default:
			break;
		}
	}

	//Ú®ÊÌÝè
	SetMove(move);
}

//======================================================
//vC[Ìµoµ
//======================================================
void CGimmick::Fall(void)
{
	//JÌîñÌæ¾
	CCamera *pCamera = CApplication::GetCamera();

	//Ü¾êxàæÁÄ¢È©Á½ç
	if (m_bLanding && !m_bCountStart)
	{//¿éÜÅÌÔ
		m_bCountStart = true;
	}

	//êxÅàæÁ½ç
	if (m_bCountStart)
	{//¿éÜÅÌÔÌ¸­
		m_nFallTime--;
	}

	//æÁÄ¢éÔ
	if (m_bLanding)
	{
		//Jðhç·
		pCamera->ShakeCamera(1, 1.0f);
	}
}
//======================================================
//vC[Ìµoµ
//======================================================
bool CGimmick::PushPlayer(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 size = GetSize() / 2.0f;
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize() / 2.0f;
		//à¤ÉÜÁÄé©»èð·é
		bool bCollision = false;

		//ubNÌÍÍàÉüÁ½ç
		if (pos.x - size.x <= PlayerPos.x + PlayerSize.x && pos.x + size.x >= PlayerPos.x - PlayerSize.x
			&& pos.z - size.z <= PlayerPos.z + PlayerSize.z && pos.z + size.z >= PlayerPos.z - PlayerSize.z
			&& pos.y + size.y >= PlayerPos.y && pos.y - size.y <= PlayerPos.y + (PlayerSize.y * 2.0f))
		{
			//¶¤©ç½Á½ê
			if ((pPlayer->GetPosOld().x + PlayerSize.x) + move.x <= pos.x - size.x + 1.0f)
			{//vC[Ìµoµ
				PlayerPos.x = pos.x - size.x - PlayerSize.x - 0.1f;
				bCollision = true;
			}
			//E¤©ç½Á½ê
			else if ((pPlayer->GetPosOld().x - PlayerSize.x) + move.x >= pos.x + size.x - 1.0f)
			{//vC[Ìµoµ
				PlayerPos.x = pos.x + size.x + PlayerSize.x + 0.1f;
				bCollision = true;
			}

			//¤©ç½Á½ê
			if ((pPlayer->GetPosOld().z - PlayerSize.z) - move.z >= pos.z + size.z - 1.0f)
			{//vC[Ìµoµ
				PlayerPos.z = pos.z + size.z + PlayerSize.z + 0.1f;
				bCollision = true;
			}
			//èO¤©ç½Á½ê
			else if ((pPlayer->GetPosOld().z + PlayerSize.z) + move.z <= pos.z - size.z + 1.0f)
			{//vC[Ìµoµ
				PlayerPos.z = pos.z - size.z - PlayerSize.z - 0.1f;
				bCollision = true;
			}

			//ã¤©ç½Á½ê
			if (pos.y + size.y <= pPlayer->GetPos().y - move.y)
			{//vC[Ìµoµ
				PlayerPos.y = pos.y + size.y;
				//ubNÌÚ®ÊðÁZ
				PlayerPos += move;
				//vC[ÌÊuðÝè
				pPlayer->SetPos(PlayerPos);
				bCollision = true;
				return true;
			}

			//º¤©ç½Á½ê
			if (move.y >= 0.0f)
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) - move.y)
				{//vC[Ìµoµ
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}
			else
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) + move.y)
				{//vC[Ìµoµ
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}

			if (!bCollision)
			{//½è»èÌÉßèñ¾çãÉµo·
				PlayerPos.y = pos.y + size.y;
				//vC[ÌÊuðÝè
				pPlayer->SetPos(PlayerPos);
				return true;
			}
			//vC[ÌÊuðÝè
			pPlayer->SetPos(PlayerPos);

		}
	}
	return false;
}

//======================================================
//Ä¶¬
//======================================================
void CGimmick::Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type)
{
	//ÊuÌÝè
	Init();
	SetPos(pos);
	OriginPos = pos;
	m_type = type;
	if (type == TYPE_FALL || type == TYPE_FALL_LONG)
	{
		m_nFallTime = (int)effect;
	}
	else
	{
		m_fRange = effect;
	}
}