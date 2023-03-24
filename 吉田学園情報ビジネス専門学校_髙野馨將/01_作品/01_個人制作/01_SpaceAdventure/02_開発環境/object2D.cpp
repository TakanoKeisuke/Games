//======================================================
//
//�I�u�W�F�N�g2D
//Author:����]��
//
//======================================================
#include "object2D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//======================================================
//�f�X�g���N�^
//======================================================
CObject2D::~CObject2D()
{//assert(m_pVtxBuff == nullptr);
}

//======================================================
//����������
//======================================================
HRESULT CObject2D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//pVtx�̐���
	SetVtx();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Flag();
}

//======================================================
//�X�V����
//======================================================
void CObject2D::Update(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//�`�揈��
//======================================================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//���_���̐擪�A�h���X
		2);											//�v���~�e�B�u(�|���S��)��

	//�e�N�X�`����null�ݒ�
	pDevice->SetTexture(0, NULL);
}

//======================================================
//��������
//======================================================
CObject2D *CObject2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//���I�m��
	CObject2D *pObject2D;
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{
		//������
		pObject2D->Init();
		pObject2D->SetSize(size);
		pObject2D->SetPos(pos);
	}
	return pObject2D;
}

//======================================================
//pVtx�̐���
//======================================================
void CObject2D::SetVtx(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::SetLifePos(const D3DXVECTOR3 &pos,const float &size, const float &life)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x , pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size * life, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x , pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size * life, pos.y + 50.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//�v���C���[���W�̐ݒ�
//======================================================
void CObject2D::SetPlayerPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
//�F�̕ύX
//======================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
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
void CObject2D::SetTex(float BesideSplit, float nNumIndex)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

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
//�����蔻��
//======================================================
bool CObject2D::Collision(const D3DXVECTOR3 &Destpos, const D3DXVECTOR3 &Destsize, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	if (Destpos.y - Destsize.y / 2.0f <= pos.y + size.y / 2.0f
		&& Destpos.y + Destsize.y / 2.0f >= pos.y - size.y / 2.0f
		&& Destpos.x + Destsize.x / 2.0f >= pos.x - size.x / 2.0f
		&& Destpos.x - Destsize.x / 2.0f <= pos.x + size.x / 2.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}