//======================================================
//
//�I�u�W�F�N�gX
//Author:����]��
//
//======================================================
#include "objectX.h"
#include "application.h"
#include "meshfield.h"
#include "input.h"
#include "stage.h"
#include <assert.h>

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CObjectX::~CObjectX()
{
	//assert(m_MeshModel == nullptr);
}

//======================================================
//����������
//======================================================
HRESULT CObjectX::Init(void)
{
	//������
	m_bModel = false;
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_MeshModel != nullptr)
	{
		m_MeshModel->Release();
		m_MeshModel = nullptr;
	}

	if (m_bModel)
	{
		//�}�e���A���̔j��
		if (m_BuffMatModel != nullptr)
		{
			m_BuffMatModel->Release();
			m_BuffMatModel = nullptr;
		}
	}

	Flag();
}

//======================================================
//�X�V����
//======================================================
void CObjectX::Update(void)
{
	if (m_rotation != nullptr)
	{//��]���x��0�ł͂Ȃ�������
		m_rot += m_rotation;			//��]�p�x���X�V����
	}
	if (m_move != nullptr)
	{//�ړ��ʂ�0�ł͂Ȃ�������
		m_pos += m_move;				//�ړ��ʂ��X�V����
	}
}

//======================================================
//�`�揈��
//======================================================
void CObjectX::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;			
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL * pMat;			

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���b�V���̏��擾
	std::vector<CMeshField*> pMesh = CStage::GetMesh();

	for (int nCnt = 0; nCnt < CStage::m_nMaxMesh; nCnt++)
	{
		if (m_pos.y >= pMesh[nCnt]->GetPos().y)
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

		//���f���p�[�c�̕`��
		m_MeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//�`�揈��
//======================================================
void CObjectX::DrawSphere()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL * pMat;

	//���ʓ��e
	Shadow();

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

		//���f���p�[�c�̕`��
		m_MeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//���ʓ��e
//======================================================
void CObjectX::Shadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//���C�g�̎擾
	CLight *pLight = CApplication::GetLight();
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;
	//�e�̃}�g���b�N�X
	D3DXMATRIX mtxShadow;
	//����
	D3DXPLANE planeField;
	//���
	D3DXVECTOR3 pos, normal;
	DWORD ambient;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���ƕ��ʂ̈�_���畽�ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//���C�g�ƕ��ʂ���e�s��
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);
	//���[���h�}�g���b�N�X���|�����킹�Đݒ�
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//�V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);
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
		//�e�̕`��
		m_MeshModel->DrawSubset(nCntMat);
	}
	//�ێ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//��������
//======================================================
CObjectX *CObjectX::Create(const D3DXVECTOR3 &pos, int nPriority)
{
	//���I�m��
	CObjectX *pObjectX;
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{
		//������
		pObjectX->Init();
		pObjectX->SetPos(pos);
	}

	return pObjectX;
}

//======================================================
//�e�N�X�`���̓ǂݍ���
//======================================================
void CObjectX::LoadModel(const char *aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(aFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMatModel,
		NULL,
		&m_NumMatModel,
		&m_MeshModel);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̐�
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = m_MeshModel->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_MeshModel->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		//�ŏ��l
		if (vtx.x < m_Min.x)
		{
			m_Min.x = vtx.x;
		}
		if (vtx.y < m_Min.y)
		{
			m_Min.y = vtx.y;
		}
		if (vtx.z < m_Min.z)
		{
			m_Min.z = vtx.z;
		}
		//�ő�l
		if (vtx.x > m_Max.x)
		{
			m_Max.x = vtx.x;
		}
		if (vtx.y > m_Max.y)
		{
			m_Max.y = vtx.y;
		}
		if (vtx.z > m_Max.z)
		{
			m_Max.z = vtx.z;
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	m_size = m_Max - m_Min;
	m_bModel = true;
}