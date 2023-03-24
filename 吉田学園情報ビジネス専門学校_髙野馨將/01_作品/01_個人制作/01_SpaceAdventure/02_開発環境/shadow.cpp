//======================================================
//
//�e
//Author:����]��
//
//======================================================
#include "shadow.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CShadow::~CShadow()
{

}

//======================================================
//����������
//======================================================
HRESULT CShadow::Init(void)
{
	//������
	CObject3D::Init();

	//�e�N�X�`���̐ݒ�
	LoadTexture("data\\TEXTURE\\shadow000.jpg");

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//======================================================
//�X�V����
//======================================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//======================================================
//�`�揈��
//======================================================
void CShadow::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CObject3D::Draw();

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//======================================================
//��������
//======================================================
CShadow *CShadow::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//���I�m��
	CShadow *pShadow;
	pShadow = new CShadow(nPriority);

	if (pShadow != nullptr)
	{
		//������
		pShadow->Init();
		pShadow->SetSize(size);
		pShadow->SetPos(pos);
	}
	return pShadow;
}