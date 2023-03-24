//======================================================
//
//�r���{�[�h
//Author:����]��
//
//======================================================
#include "billboard.h"
#include "application.h"
#include "input.h"
#include <assert.h>
#include "object3d.h"

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	//������
	m_bTexture = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//======================================================
//�f�X�g���N�^
//======================================================
CBillboard::~CBillboard()
{
	//assert(m_pVtxBuff == nullptr);
}

//======================================================
//����������
//======================================================
HRESULT CBillboard::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�e�N�X�`���̐ݒ�
	LoadTexture("data\\TEXTURE\\bullet000.png");

	//pVtx�̐���
	SetVtx();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_bTexture)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture != nullptr)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
	}

	Break();
}

//======================================================
//�X�V����
//======================================================
void CBillboard::Update(void)
{
	SetVtx();
}

//======================================================
//�`�揈��
//======================================================
void CBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;	//�v�Z�p�}�g���b�N�X
									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;	//�c��]
	m_mtxWorld._22 = mtxView._22;	//�c��]
	m_mtxWorld._23 = mtxView._32;	//�c��]
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u(�|���S��(�O�p�`))��
	//���C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================================================
//��������
//======================================================
CBillboard *CBillboard::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//���I�m��
	CBillboard *pObject3D;
	pObject3D = new CBillboard(nPriority);

	if (pObject3D != nullptr)
	{
		//������
		pObject3D->Init();
		pObject3D->SetPos(pos);
		pObject3D->SetSize(size);
	}

	return pObject3D;
}

//======================================================
//pVtx�̐���
//======================================================
void CBillboard::SetVtx(void)
{
	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);

	// nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

////======================================================
////�F�̕ύX
////======================================================
//void CBillboard::SetCol(D3DXCOLOR col)
//{
//	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^
//							//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//���_�J���[�̐ݒ�
//	pVtx[0].col = col;
//	pVtx[1].col = col;
//	pVtx[2].col = col;
//	pVtx[3].col = col;
//
//	//���_�o�b�t�@���A�����b�N����
//	m_pVtxBuff->Unlock();
//}

//======================================================
//�e�N�X�`���̓ǂݍ���
//======================================================
void CBillboard::LoadTexture(const char *aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}