//======================================================
//
//�I�u�W�F�N�g3D
//Author:����]��
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CObject3D::~CObject3D()
{//assert(m_pVtxBuff == nullptr);
}

//======================================================
//����������
//======================================================
HRESULT CObject3D::Init(void)
{
	//������
	m_size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bTexture = false;

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
	LoadTexture("data\\TEXTURE\\sea.png");

	//pVtx�̐���
	SetVtx();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CObject3D::Uninit(void)
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

	Flag();
}

//======================================================
//�X�V����
//======================================================
void CObject3D::Update(void)
{
	//pVtx�̐���
	SetVtx();
}

//======================================================
//�`�揈��
//======================================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldPolygon);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u(�|���S��(�O�p�`))��
	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//��������
//======================================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size,int nPriority)
{
	//���I�m��
	CObject3D *pObject3D;
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{
		//������
		pObject3D->Init();
		pObject3D->SetSize(size);
		pObject3D->SetPos(pos);
	}

	return pObject3D;
}

//======================================================
//pVtx�̐���
//======================================================
void CObject3D::SetVtx(void)
{
	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = m_pos;
	pVtx[1].pos = m_pos;
	pVtx[2].pos = m_pos;
	pVtx[3].pos = m_pos;

	// nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//���W�̐ݒ�
//======================================================
void CObject3D::SetSize(const D3DXVECTOR3 &size)
{
	m_size = size;

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x,  0.0f, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x,  0.0f, -m_size.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//�F�̕ύX
//======================================================
void CObject3D::SetCol(D3DXCOLOR col)
{
	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//�e�N�X�`�����W�̊m��
//======================================================
void CObject3D::SetTex(float BesideSplit, float nNumIndex)
{
	//���_���W�ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumIndex + 1.0f) / BesideSplit, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumIndex + 1.0f) / BesideSplit, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//======================================================
//�e�N�X�`���̓ǂݍ���
//======================================================
void CObject3D::LoadTexture(const char *aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}