//======================================================
//
//���f��
//Author:����]��
//
//======================================================
#include "model.h"
#include "application.h"
#include "input.h"
#include "game.h"
#include <assert.h>
#include "player.h"

//======================================================
//�R���X�g���N�^
//======================================================
CModel::CModel()
{
	m_nMatId = -1;
}

//======================================================
//�f�X�g���N�^
//======================================================
CModel::~CModel()
{
}

//======================================================
//����������
//======================================================
HRESULT CModel::Init(void)
{
	//������
	m_bModel = false;
	m_pTexture = nullptr;
	D3DXMatrixIdentity(&m_mtxShadow);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CModel::Uninit(void)
{
	//���b�V���̔j��
	if (m_MeshModel != nullptr)
	{
		m_MeshModel->Release();
		m_MeshModel = nullptr;
	}

	//�}�e���A���̔j��
	if (m_BuffMatModel != nullptr)
	{
		m_BuffMatModel->Release();
		m_BuffMatModel = nullptr;
	}

	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < (int)m_NumMatModel; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//======================================================
//�X�V����
//======================================================
void CModel::Update(void)
{
}

//======================================================
//�`�揈��
//======================================================
void CModel::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	CPlayer *pPlayer = CGame::GetPlayer();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//���[���h�}�g���b�N�X���|�����킹�Đݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	
	if (pPlayer != nullptr)
	{
		if (!pPlayer->GetInside())
		{
			//���ʓ��e
			Shadow();
		}
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f���p�[�c�̕`��
		m_MeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//��������
//======================================================
CModel *CModel::Create(const D3DXVECTOR3 &pos)
{
	//���I�m��
	CModel *pModel = new CModel;

	if (pModel != nullptr)
	{
		//������
		pModel->Init();
		pModel->m_pos = pos;
	}

	return pModel;
}

//======================================================
//����������
//======================================================
void CModel::SetModel(const char *pFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMatModel,
		NULL,
		&m_NumMatModel,
		&m_MeshModel);

	// �e�N�X�`��
	m_pTexture = new LPDIRECT3DTEXTURE9[m_NumMatModel];

	//��񂪓����ĂȂ�������
	assert(m_pTexture != nullptr);

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	// �e���b�V���̃}�e���A�������擾����
	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//���̏�����
		m_pTexture[nCntMat] = nullptr;

		//�|���S���ɓ\��t����e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			pMat[nCntMat].pTextureFilename,
			&m_pTexture[nCntMat]);
	}
}

//======================================================
//���ʓ��e
//======================================================
void CModel::Shadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���C�g�̎擾
	CLight *pLight = CApplication::GetLight();
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//�v���C���[
	CPlayer *pPlayer = CGame::GetPlayer();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//����
	D3DXPLANE planeField;

	//���
	D3DXVECTOR3 normal;
	DWORD ambient;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxShadow);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���ƕ��ʂ̈�_���畽�ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &m_ShadowPos, &normal);

	//���C�g�ƕ��ʂ���e�s��
	D3DXMatrixShadow(&m_mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X���|�����킹�Đݒ�
	D3DXMatrixMultiply(&m_mtxShadow, &m_mtxWorld, &m_mtxShadow);

	//�V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxShadow);
	
	//�e�̈ʒu
	D3DXVec3TransformCoord(&m_Shadow, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &m_mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		// �}�e���A������ۑ����A�F�ƃ��C�g�̐F�����ɐݒ�
		D3DMATERIAL9 pMatD3D = pMat[nCntMat].MatD3D;
		pMatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�}�e���A���̐ݒ�
		pDevice->SetRenderState(D3DRS_AMBIENT, 0xff000000);	//�J���[
		pDevice->SetMaterial(&pMatD3D);

		if (pPlayer->GetShadow())
		{
			//�e�̕`��
			m_MeshModel->DrawSubset(nCntMat);
		}
	}

	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}