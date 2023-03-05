//======================================================
//
// heal.cpp
// Author : ����]��
//
//======================================================
#include "heal.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "score.h"

//======================================================
//�R���X�g���N�^
//======================================================
CHeal::CHeal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CHeal::~CHeal()
{
}

//======================================================
//����������
//======================================================
HRESULT CHeal::Init(void)
{
	//������
	m_pHitbox = nullptr;

	//���f���̐ݒ�
	LoadModel("data\\model\\Coin00.x");

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CHeal::Uninit(void)
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
void CHeal::Update(void)
{
	//���̎擾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//�����蔻�肪null�ł͂Ȃ�������
		if (m_pHitbox->GetCollisionState())
		{//�v���C���[�Ɠ��������ꍇ
			//�X�R�A�̉��Z
			CScore *pScore = CGame::GetScore();
			pScore->AddScore(100);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN_GET);

			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Uninit();					//�R�C��������

			return;
		}
	}

	//�X�V����
	CObjectX::Update();
}

//======================================================
//�`�揈��
//======================================================
void CHeal::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//��������
//======================================================
CHeal *CHeal::Create(const D3DXVECTOR3 pos)
{
	//���I�m��
	CHeal *pHeal = new CHeal;

	if (pHeal != nullptr)
	{
		//�ʒu�̐ݒ�
		pHeal->Init();
		pHeal->SetPos(pos);

		//����]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pHeal->SetRotation(rotation);

		//�q�b�g�{�b�N�X�𐶐�����
		pHeal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 10.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pHeal, CHitbox::EFFECT_HEAL);
	}

	return pHeal;
}