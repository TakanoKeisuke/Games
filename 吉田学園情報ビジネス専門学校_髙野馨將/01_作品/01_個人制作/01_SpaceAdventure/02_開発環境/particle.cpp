//============================================
//
//	particle.cpp
//	Author: saito shian TAKANO KEISUKE
//
//============================================
#include <assert.h>
#include "particle.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "object3d.h"
#include "debug.h"

//============================================
// �p�[�e�B�N���̃R���X�g���N�^
//============================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
}

//============================================
// �p�[�e�B�N���̃f�X�g���N�^
//============================================
CParticle::~CParticle()
{
}
//============================================
// �p�[�e�B�N���̏���������
//============================================
HRESULT CParticle::Init(void)
{
	//���̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�����o�ϐ��̏�����
	m_pTexture = nullptr;							//�e�N�X�`���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��̏�����
	m_size = D3DXVECTOR3(3.0f, 3.0f, 0.0f);			//�T�C�Y�̏�����
	m_nLife = 50;									//�̗͂̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F�̏�����

	//�e�N�X�`���̐�
	SetTexture("data\\TEXTURE\\shadow000.jpg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(���[���h���W�ł͂Ȃ����[�J�����W��ݒ�)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// �p�[�e�B�N���̏I������
//============================================
void CParticle::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�j������
	Flag();
}

//============================================
// �p�[�e�B�N���̍X�V����
//============================================
void CParticle::Update(void)
{
	//�ʒu�̍X�V
	m_pos += m_move;

	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(-m_Radius, m_Radius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Radius, m_Radius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Radius, -m_Radius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Radius, -m_Radius, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�ړ��ʌ���
	m_pos.x += (0.0f - m_move.x) * 0.1f;
	m_pos.y += (0.0f - m_move.y) * 0.1f;
	m_pos.z += (0.0f - m_move.z) * 0.1f;

	//�ʒu�̐ݒ�
	SetPos(m_pos);
	//�ړ��̐ݒ�
	SetMove(m_move);
	//�T�C�Y�̐ݒ�
	SetSize(m_size);
}

//============================================
// �p�[�e�B�N���̕`�揈��
//============================================
void CParticle::Draw(void)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);//�s�񏉊����֐�(�������̍s���P�ʍs��ɏ�����)

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�	(2�t����������΃r���{�[�h����Ɍ����Ȃ�)
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//�s���]�֐�(�������Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//�s��|���Z�֐�(��2���� * ��O������������Ɋi�[)

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//�s��ړ��֐�(��������x,y,z�����̈ړ��s����쐬)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);	//���[���h���W�s��̐ݒ�

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�p�[�e�B�N���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//============================================
// �p�[�e�B�N���̃e�N�X�`������
//============================================
CParticle * CParticle::SetTexture(char * pFile)
{
	//GetDevive�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTexture);

	return S_OK;
}

//============================================
// �p�[�e�B�N���̈ʒu�̐ݒ�
//============================================
void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// �p�[�e�B�N���̃T�C�Y�̐ݒ�
//============================================
void CParticle::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// �p�[�e�B�N���̐ݒ菈��
//============================================
void CParticle::SetParticle(D3DXVECTOR3 pos, int life, D3DXCOLOR col)
{


	if (m_type == PARTICLETYPE_FIRE)
	{
		m_pos = pos;																		//�ʒu
		m_move.x = sinf((float)(rand() % 10)) * ((float)(rand() % 15) / 15);				//x�̈ړ���
		m_move.y = cosf((float)(rand() % 10)) * ((float)(rand() % 10) / 10);				//y�̈ړ���
		m_move.z = sinf((float)(rand() % 10)) * ((float)(rand() % 15) / 15);				//z�̈ړ���
		m_Radius = (float)(rand() % 5 + 2);													//���a�̎Z�o
		m_nLife = life;																		//�����̎Z�o
		m_col = col;																		//�F
	}
	if (m_type == PARTICLETYPE_FOUNTAIN)
	{
		m_pos = pos;																		//�ʒu
		m_move.x = sinf((float)(rand() % 100)) * ((float)(rand() % 10) / 50);				//x�̈ړ���
		//m_move.y = 0.50f;																	//y�̈ړ���
		m_move.z = sinf((float)(rand() % 100)) * ((float)(rand() % 10) / 50);				//z�̈ړ���
		m_Radius = (float)(rand() % 5 + 2);													//���a�̎Z�o
		m_nLife = life;																		//�����̎Z�o
		m_col = col;																		//�F
	}
	if (m_type == PARTICLETYPE_SPLINTER)
	{
		m_pos = pos;																		//�ʒu
		m_move.x = sinf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//x�̈ړ���
		m_move.y = cosf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//y�̈ړ���
		m_move.z = sinf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//z�̈ړ���
		m_Radius = (float)(rand() % 5 + 1);													//���a�̎Z�o
		m_nLife = life;																		//�����̎Z�o
		m_col = col;																		//�F
	}

}

//============================================
// �p�[�e�B�N���̎�ނ̐ݒ�
//============================================
void CParticle::SetParticleType(PARTICLETYPE type)
{
	m_type = type;
}

//============================================
// �p�[�e�B�N���̐���
//============================================
CParticle * CParticle::Create(PARTICLETYPE type, D3DXVECTOR3 pos, int life, D3DXCOLOR col)
{
	CParticle *pParticle = nullptr;

	//�p�[�e�B�N���̐���
	pParticle = new CParticle(PRIORITY_5);				//�p�[�e�B�N���̃C���X�^���X����
	//null�`�F�b�N
	if (pParticle != nullptr)
	{
		pParticle->SetParticleType(type);
		//����������
		pParticle->Init();
		pParticle->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pParticle->SetParticle(pos, life, col);
	}
	else
	{
		assert(false);
	}
	return pParticle;
}