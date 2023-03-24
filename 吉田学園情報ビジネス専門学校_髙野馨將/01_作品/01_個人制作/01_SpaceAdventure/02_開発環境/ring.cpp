//======================================================
//
// ring.cpp
// Author : ����]��
//
//======================================================
#include "ring.h"
#include "CylinderHitbox.h"
#include "SphereHitbox.h"

//======================================================
//�R���X�g���N�^
//======================================================
CRing::CRing(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CRing::~CRing()
{
}

//======================================================
//������
//======================================================
HRESULT CRing::Init(void)
{
	//������
	m_pHitbox = nullptr;

	//���f���̐ݒ�
	LoadModel("data\\model\\jump.x");

	return S_OK;
}

//======================================================
//�I��
//======================================================
void CRing::Uninit(void)
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
void CRing::Update(void)
{
	//���̎擾
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	//�X�V����
	CObjectX::Update();
}

//======================================================
//�`��
//======================================================
void CRing::Draw(void)
{
	//�`��
	CObjectX::Draw();
}

//======================================================
//����
//======================================================
CRing *CRing::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�𐶐�����
	CRing *pRing = new CRing;

	if (pRing != nullptr)
	{
		//�ݒ菈��
		pRing->Init();
		pRing->SetSize(size);
		pRing->SetPos(pos);
		pRing->SetRot(rot);

		//�����蔻��
		pRing->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE, 0, pRing, CHitbox::EFFECT_FLY);
	}

	return pRing;
}