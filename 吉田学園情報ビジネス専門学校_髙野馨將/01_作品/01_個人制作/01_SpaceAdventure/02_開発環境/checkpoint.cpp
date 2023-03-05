//======================================================
//
// heal.cpp
// Author : ����]��
//
//======================================================
#include "checkpoint.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "particle.h"
#include "score.h"

//======================================================
//�R���X�g���N�^
//======================================================
CCheckpoint::CCheckpoint(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CCheckpoint::~CCheckpoint()
{
}

//======================================================
//����������
//======================================================
HRESULT CCheckpoint::Init(void)
{
	//������
	m_pHitbox = nullptr;

	//���f���̐ݒ�
	LoadModel("data\\model\\checkpoint.x");

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CCheckpoint::Uninit(void)
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
void CCheckpoint::Update(void)
{
	//���̎擾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 ParticlePos = pos + D3DXVECTOR3(0.0f,30.0f,0.0f);

	//�p�[�e�B�N���̐���
	CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, ParticlePos, 10, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));

	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//�����蔻�肪null�ł͂Ȃ�������
		if (m_pHitbox->GetCollisionState())
		{//�v���C���[�Ɠ��������ꍇ
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHECK);

			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Uninit();					//���g������

			return;
		}
	}

	//�X�V����
	CObjectX::Update();
}

//======================================================
//�`�揈��
//======================================================
void CCheckpoint::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//��������
//======================================================
CCheckpoint *CCheckpoint::Create(const D3DXVECTOR3 pos)
{
	//���I�m��
	CCheckpoint *pCheck = new CCheckpoint;

	if (pCheck != nullptr)
	{
		//�ʒu�̐ݒ�
		pCheck->Init();
		pCheck->SetPos(pos);

		//�q�b�g�{�b�N�X�𐶐�����
		pCheck->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 7.0f, 2.0f), CHitbox::TYPE_OBSTACLE, 0, pCheck, CHitbox::EFFECT_CHECKPOINT);
	}

	return pCheck;
}