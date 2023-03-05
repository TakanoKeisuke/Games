//======================================================
//
// goal.cpp
// Author : ����]��
//
//======================================================
#include "goal.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//======================================================
//�R���X�g���N�^
//======================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CGoal::~CGoal()
{
}

//======================================================
//������
//======================================================
HRESULT CGoal::Init(void)
{
	//������
	m_pHitbox = nullptr;

	//���f���̐ݒ�
	LoadModel("data\\model\\star000.x");

	return S_OK;
}

//======================================================
//�I��
//======================================================
void CGoal::Uninit(void)
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
//�X�V
//======================================================
void CGoal::Update(void)
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
			 //SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Uninit();					//�R�C��������

			return;
		}
	}

	//�X�V����
	CObjectX::Update();
}

//======================================================
//�`��
//======================================================
void CGoal::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//����
//======================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�𐶐�����
	CGoal *pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		//�ݒ菈��
		pGoal->Init();
		pGoal->SetSize(size);
		pGoal->SetPos(pos);

		//����]
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f,1.0f,0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pGoal->SetRotation(rotation);

		//�����蔻��
		pGoal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE,0, pGoal,CHitbox::EFFECT_GOAL);
	}

	return pGoal;
}