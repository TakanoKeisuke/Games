//=============================================================================
//
// �i���o�[����
// Author:����]��
//
//=============================================================================
#include "application.h"
#include "number.h"
#include "renderer.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{//���������Ȃ�
}

//=============================================================================
//�i���o�[�̏�����
//=============================================================================
HRESULT CNumber::Init()
{
	//�I�u�W�F�N�g�̏�����
	CObject2D::Init();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture);

	//�e�N�X�`���̐ݒ�
	CObject2D::BindTexture(m_pTexture);

	//�e�N�X�`���̏�����
	SetTex(10, 0);

	return S_OK;
}

//=============================================================================
//�i���o�[�̐���
//=============================================================================
void CNumber::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//�j������
	Flag();
}

//=============================================================================
//�i���o�[�̐���
//=============================================================================
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 &size)
{
	CNumber *pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		//������
		pNumber->Init();
		pNumber->SetPos(pos);
		pNumber->SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
	}

	return pNumber;
}