//======================================================
//
// Buff.cpp
// Author : ����]��
//
//======================================================
#include "buff.h"
#include "stage.h"
#include "application.h"
#include "sound.h"
#include<vector>

//======================================================
//�R���X�g���N�^
//======================================================
CBuff::CBuff(int nPriority) : CObjectX(nPriority)
{
}


//======================================================
//�f�X�g���N�^
//======================================================
CBuff::~CBuff()
{
}

//======================================================
//����������
//======================================================
HRESULT CBuff::Init(void)
{
	//������
	m_pHitbox = nullptr;
	m_bInvisible = false;

	switch (m_effect)
	{
	case CHitbox::EFFECT_JUMP:
		//���f���̐ݒ�
		LoadModel("data\\model\\Coin02.x");
		break;

	case CHitbox::EFFECT_SPEED:
		//���f���̐ݒ�
		LoadModel("data\\model\\Coin03.x");
		break;

	default:
		break;
	}

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CBuff::Uninit(void)
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
void CBuff::Update(void)
{
	//���̎擾
	D3DXVECTOR3 pos = CObjectX::GetPos();
	std::vector<CBuff*> pBuff = CStage::GetBuff();

	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//�����蔻�肪null�ł͂Ȃ�������
		if (m_pHitbox->GetCollisionState())
		{//�v���C���[�Ɠ��������ꍇ
			m_bInvisible = true;
			m_nInvincibleCnt = 360;

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			m_pHitbox = nullptr;
		}
	}

	//���G����
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//�J�E���^�[�̍X�V
	}

	//��莞�Ԍo�ƃ��X�|�[�����鏈��
	for (int nCnt = 0; nCnt < CStage::m_nMaxBuff; nCnt++)
	{
		if (pBuff[nCnt]->m_nInvincibleCnt <= 0 && pBuff[nCnt]->m_pHitbox == nullptr)
		{
			pBuff[nCnt]->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff[nCnt], m_effect);
		}
	}

	//���G����
	if (m_nInvincibleCnt <= 60)
	{
		m_bInvisible = false;
	}

	//�X�V����
	CObjectX::Update();
}

//======================================================
//�`�揈��
//======================================================
void CBuff::Draw(void)
{
	if (!m_bInvisible)
	{
		if (m_nInvincibleCnt % 10 <= 5)
		//�`��
		CObjectX::Draw();
	}
}

//======================================================
//��������
//======================================================
CBuff *CBuff::Create(const D3DXVECTOR3 pos, CHitbox::INTERACTION_EFFECT effect)
{
	//���I�m��
	CBuff *pBuff = new CBuff;

	if (pBuff != nullptr)
	{
		//�ʒu�̐ݒ�
		pBuff->m_effect = effect;
		pBuff->Init();
		pBuff->SetPos(pos);

		//����]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pBuff->SetRotation(rotation);

		//�q�b�g�{�b�N�X�𐶐�����
		pBuff->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff, effect);
	}

	return pBuff;
}