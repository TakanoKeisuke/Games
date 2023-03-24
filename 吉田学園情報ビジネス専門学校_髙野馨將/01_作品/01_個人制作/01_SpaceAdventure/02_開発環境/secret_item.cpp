//======================================================
//
// secret_item.cpp
// Author : ����]��
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
//�R���X�g���N�^
//======================================================
CSecret_item::CSecret_item(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CSecret_item::~CSecret_item()
{
}

//======================================================
//����������
//======================================================
HRESULT CSecret_item::Init(void)
{
	//������
	m_pHitbox = nullptr;
	m_bCollision = false;
	m_nNumber = 0;

	//���f���̐ݒ�
	LoadModel("data\\model\\Coin01.x");

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CSecret_item::Uninit(void)
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
void CSecret_item::Update(void)
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
			pScore->AddScore(1000);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			CItemFrame *pFrame = CGame::GetFrame(m_nNumber);	//�t���[���ɃZ�b�g����
			pFrame->SetGetItem(true);
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
void CSecret_item::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//��������
//======================================================
CSecret_item *CSecret_item::Create(const D3DXVECTOR3 pos, int number)
{
	//���I�m��
	CSecret_item *pItem = new CSecret_item;

	if (pItem != nullptr)
	{
		//�ʒu�̐ݒ�
		pItem->Init();
		pItem->m_nNumber = number;
		pItem->SetPos(pos);

		//����]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pItem->SetRotation(rotation);

		//�q�b�g�{�b�N�X�𐶐�����
		pItem->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(8.0f, 8.0f, 8.0f), CHitbox::TYPE_OBSTACLE, 0, pItem, CHitbox::EFFECT_HEAL);
	}

	return pItem;
}