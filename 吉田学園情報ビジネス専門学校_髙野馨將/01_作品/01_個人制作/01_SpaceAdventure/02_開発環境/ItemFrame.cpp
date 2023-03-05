//======================================================
//
//itemframe.cpp
//Author:����]��
//
//======================================================
#include "ItemFrame.h"
#include "application.h"
#include "game.h"

//======================================================
//�R���X�g���N�^
//======================================================
CItemFrame::CItemFrame(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CItemFrame::~CItemFrame()
{//���������Ȃ�
}

//======================================================
//����������
//======================================================
HRESULT CItemFrame::Init(void)
{
	//����������
	CObject2D::Init();
	m_bGet = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Frame.png",
		&m_pTexture);

	//�e�N�X�`���̐ݒ�
	CObject2D::BindTexture(m_pTexture);

	//�e�N�X�`�����W�̐ݒ�
	SetTex(2.0f, 0.0f);

	return S_OK;
}

//======================================================
//�X�V����
//======================================================
void CItemFrame::Uninit()
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
void CItemFrame::Update()
{
	//�A�C�e������肵�Ă�����
	if (m_bGet)
	{
		//�e�N�X�`�����W�̐ݒ�
		SetTex(2.0f, 1.0f);
	}

	//�X�V����
	CObject2D::Update();
}

//======================================================
//�X�V����
//======================================================
void CItemFrame::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//======================================================
//��������
//======================================================
CItemFrame *CItemFrame::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//���I�m��
	CItemFrame *pFrame = new CItemFrame;

	if (pFrame != nullptr)
	{
		//������
		pFrame->Init();
		pFrame->SetPos(pos);
		pFrame->SetSize(size);
	}

	return pFrame;
}