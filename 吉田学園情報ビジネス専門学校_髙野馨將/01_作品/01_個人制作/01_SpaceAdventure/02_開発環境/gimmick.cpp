//======================================================
//
// gimmick.cpp
// Author : ����]��
//
//======================================================
#include "gimmick.h"
#include "player.h"
#include "game.h"
#include "application.h"

//======================================================
//�R���X�g���N�^
//======================================================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CGimmick::~CGimmick()
{
}

//======================================================
//����������
//======================================================
HRESULT CGimmick::Init(void)
{
	//������
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

	//���f���̐ݒ�
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
//�I������
//======================================================
void CGimmick::Uninit(void)
{
	//�������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CGimmick::Update(void)
{
	//��ނ��Ƃ̏���
	TypeEffect();

	//�X�V����
	CObjectX::Update();

	//�����蔻��̗L��
	if (m_nInvincibleCnt > 0)
	{//�_�Œ��͖���
		m_nInvincibleCnt--;
	}
	else if (m_nInvincibleCnt == 0)
	{
		//�����o������
		m_bLanding = PushPlayer();
	}

	//�Đ�������
	if (m_bRespawn)
	{
		Respawn(OriginPos,m_feffect,m_type);
		m_nInvincibleCnt = 60;
	}

	//�Đ������Ԃ���莞�ԂɒB������
	if (m_nRespawnTime >= 60)
	{
		m_nRespawnTime = 0;
		m_bRespawn = true;
	}

	//�������̍�����藎������
	if (GetPos().y <= -200.0f)
	{
		//���X�|�[��������
		m_nRespawnTime++;
	}

}

//======================================================
//�`�揈��
//======================================================
void CGimmick::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{
		//�`��
		CObjectX::Draw();
	}
}

//======================================================
//��������
//======================================================
CGimmick *CGimmick::Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed)
{
	//���I�m��
	CGimmick *pGimmick = new CGimmick;

	if (pGimmick != nullptr)
	{
		//�ʒu�̐ݒ�
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
//��ނ̌��ʏ���
//======================================================
void CGimmick::TypeEffect(void)
{
	//���̎擾
	D3DXVECTOR3 move = CObjectX::GetMove();
	//sin�J�[�u
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
			//��������
			Fall();

			//�����鎞�ԂɒB������
			if (m_nFallTime < 0)
			{
				//���Ƃ�
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		case CGimmick::TYPE_FALL_LONG:
			//��������
			Fall();

			//�����鎞�ԂɒB������
			if (m_nFallTime < 0)
			{
				//���Ƃ�
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		default:
			break;
		}
	}

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//======================================================
//�v���C���[�̉����o������
//======================================================
void CGimmick::Fall(void)
{
	//�J�����̏��̎擾
	CCamera *pCamera = CApplication::GetCamera();

	//�܂���x������Ă��Ȃ�������
	if (m_bLanding && !m_bCountStart)
	{//������܂ł̎���
		m_bCountStart = true;
	}

	//��x�ł��������
	if (m_bCountStart)
	{//������܂ł̎��Ԃ̌���
		m_nFallTime--;
	}

	//����Ă����
	if (m_bLanding)
	{
		//�J������h�炷
		pCamera->ShakeCamera(1, 1.0f);
	}
}
//======================================================
//�v���C���[�̉����o������
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
		//�����ɖ��܂��Ă邩���������
		bool bCollision = false;

		//�u���b�N�͈͓̔��ɓ�������
		if (pos.x - size.x <= PlayerPos.x + PlayerSize.x && pos.x + size.x >= PlayerPos.x - PlayerSize.x
			&& pos.z - size.z <= PlayerPos.z + PlayerSize.z && pos.z + size.z >= PlayerPos.z - PlayerSize.z
			&& pos.y + size.y >= PlayerPos.y && pos.y - size.y <= PlayerPos.y + (PlayerSize.y * 2.0f))
		{
			//�������瓖�������ꍇ
			if ((pPlayer->GetPosOld().x + PlayerSize.x) + move.x <= pos.x - size.x + 1.0f)
			{//�v���C���[�̉����o��
				PlayerPos.x = pos.x - size.x - PlayerSize.x - 0.1f;
				bCollision = true;
			}
			//�E�����瓖�������ꍇ
			else if ((pPlayer->GetPosOld().x - PlayerSize.x) + move.x >= pos.x + size.x - 1.0f)
			{//�v���C���[�̉����o��
				PlayerPos.x = pos.x + size.x + PlayerSize.x + 0.1f;
				bCollision = true;
			}

			//�������瓖�������ꍇ
			if ((pPlayer->GetPosOld().z - PlayerSize.z) - move.z >= pos.z + size.z - 1.0f)
			{//�v���C���[�̉����o��
				PlayerPos.z = pos.z + size.z + PlayerSize.z + 0.1f;
				bCollision = true;
			}
			//��O�����瓖�������ꍇ
			else if ((pPlayer->GetPosOld().z + PlayerSize.z) + move.z <= pos.z - size.z + 1.0f)
			{//�v���C���[�̉����o��
				PlayerPos.z = pos.z - size.z - PlayerSize.z - 0.1f;
				bCollision = true;
			}

			//�㑤���瓖�������ꍇ
			if (pos.y + size.y <= pPlayer->GetPos().y - move.y)
			{//�v���C���[�̉����o��
				PlayerPos.y = pos.y + size.y;
				//�u���b�N�̈ړ��ʂ����Z
				PlayerPos += move;
				//�v���C���[�̈ʒu��ݒ�
				pPlayer->SetPos(PlayerPos);
				bCollision = true;
				return true;
			}

			//�������瓖�������ꍇ
			if (move.y >= 0.0f)
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) - move.y)
				{//�v���C���[�̉����o��
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}
			else
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) + move.y)
				{//�v���C���[�̉����o��
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}

			if (!bCollision)
			{//�����蔻��̒��ɂ߂荞�񂾂��ɉ����o��
				PlayerPos.y = pos.y + size.y;
				//�v���C���[�̈ʒu��ݒ�
				pPlayer->SetPos(PlayerPos);
				return true;
			}
			//�v���C���[�̈ʒu��ݒ�
			pPlayer->SetPos(PlayerPos);

		}
	}
	return false;
}

//======================================================
//�Đ�������
//======================================================
void CGimmick::Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type)
{
	//�ʒu�̐ݒ�
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