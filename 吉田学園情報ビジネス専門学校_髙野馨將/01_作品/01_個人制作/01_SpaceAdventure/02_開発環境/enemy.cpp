//======================================================
//
// Spike.cpp
// Author : ����]��
//
//======================================================
#include "enemy.h"
#include "CylinderHitbox.h"
#include "player.h"
#include "game.h"

//======================================================
//�R���X�g���N�^
//======================================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CEnemy::~CEnemy()
{
}

//======================================================
//����������
//======================================================
HRESULT CEnemy::Init(void)
{
	//������
	m_pHitbox = nullptr;
	m_type = CGimmick::TYPE_MAX;

	//���f���̐ݒ�
	LoadModel("data\\model\\spike.x");

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CEnemy::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//�������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CEnemy::Update(void)
{
	//���̎擾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 move = CObjectX::GetMove();

	//sin�J�[�u
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
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	//�X�V����
	CObjectX::Update();

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//======================================================
//�`�揈��
//======================================================
void CEnemy::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//��������
//======================================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int range)
{
	//���I�m��
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		//�ʒu�̐ݒ�
		pEnemy->Init();
		pEnemy->SetPos(pos);
		pEnemy->m_fRange = (float)range / 2.0f;

		//�����_���ŉ�]��ݒ肷��
		D3DXVECTOR3 rotation = D3DXVECTOR3((float)Random(-100, 100), (float)Random(-100, 100), (float)Random(-100, 100));
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.x *= 0.1f;
		rotation.y *= 0.1f;
		rotation.z *= 0.1f;
		pEnemy->SetRotation(rotation);

		//�q�b�g�{�b�N�X�𐶐�����
		pEnemy->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 13.0f, 3.0f), CHitbox::TYPE_OBSTACLE, 0, pEnemy, CHitbox::EFFECT_DAMAGE);
	}

	return pEnemy;
}

//======================================================
//�ǔ�����
//======================================================
void CEnemy::Chase(void)
{
	//���̎擾
	//CPlayer *pPlayer = CGame::GetPlayer();


}