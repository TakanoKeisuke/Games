//======================================================
//
//life_gage.cpp
//Author:����]��
//
//======================================================
#include "life_gauge.h"
#include "application.h"
#include "game.h"
#include "player.h"

//======================================================
//�R���X�g���N�^
//======================================================
CLife_gauge::CLife_gauge(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CLife_gauge::~CLife_gauge()
{//���������Ȃ�
}

//======================================================
//����������
//======================================================
HRESULT CLife_gauge::Init(void)
{
	//����������
	CObject2D::Init();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life.png",
		&m_pTexture);

	//�e�N�X�`���̐ݒ�
	CObject2D::BindTexture(m_pTexture);

	//�e�N�X�`�����W�̐ݒ�
	SetTex(4.0f, 0.0f);

	return S_OK;
}

//======================================================
//�X�V����
//======================================================
void CLife_gauge::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CLife_gauge::Update()
{
	//�J�����̏��̎擾
	CPlayer *pPlayer = CGame::GetPlayer();
	int nLife = pPlayer->GetLife();

	if (nLife == 3)
	{
		//�e�N�X�`�����W�̐ݒ�
		SetTex(4.0f, 0.0f);
	}
	else if (nLife == 2)
	{
		//�e�N�X�`�����W�̐ݒ�
		SetTex(4.0f, 1.0f);
	}
	else if (nLife == 1)
	{
		//�e�N�X�`�����W�̐ݒ�
		SetTex(4.0f, 2.0f);
	}
	else if (nLife == 0)
	{
		//�e�N�X�`�����W�̐ݒ�
		SetTex(4.0f, 3.0f);
	}

	//�X�V����
	CObject2D::Update();
}

//======================================================
//�X�V����
//======================================================
void CLife_gauge::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//======================================================
//��������
//======================================================
CLife_gauge *CLife_gauge::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//���I�m��
	CLife_gauge *pLife = new CLife_gauge;

	if (pLife != nullptr)
	{
		//������
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(size);
	}

	return pLife;
}