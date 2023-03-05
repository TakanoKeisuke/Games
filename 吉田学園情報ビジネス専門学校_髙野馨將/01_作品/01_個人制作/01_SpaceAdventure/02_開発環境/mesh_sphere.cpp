//======================================================
//
//mesh_sphere.cpp
//Author : ����]��
//
//======================================================
#include "application.h"
#include "mesh_sphere.h"
#include "object3d.h"
#include "debug.h"

//======================================================
//�R���X�g���N�^
//======================================================
CMesh_sphere::CMesh_sphere(const int nPriority) : CMeshField(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
}

//======================================================
//�f�X�g���N�^
//======================================================
CMesh_sphere::~CMesh_sphere()
{
}

//======================================================
//����������
//======================================================
HRESULT CMesh_sphere::Init(void)
{
	//������
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HALFSPHEAR_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * HALFSPHEAR_INDEXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���W�ւ̃|�C���^
	VERTEX_3D * pVtx = nullptr;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < HALFSPHEAR_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < HALFSPHEAR_X_BLOCK + 1; nCntX++)
		{
			float fRot = (D3DX_PI * 2) / HALFSPHEAR_X_BLOCK * nCntX;
			float fHalfRot = (D3DX_PI) / HALFSPHEAR_Z_BLOCK * nCntZ;

			// ���a�ƁA�����̌v�Z
			float Radius = cosf(fHalfRot) * m_size.x;
			float Height = sinf(fHalfRot) * m_size.z;

			//���_���W�̐ݒ�
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.x = sinf(-fRot) * Radius;
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.z = cosf(-fRot) * Radius;
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.y = Height/* + 15.0f*/;

			//�e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			switch (m_tex)
			{
			case CMesh_sphere::SPHERE_UP:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * -nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * -nCntZ);
				break;

			case CMesh_sphere::SPHERE_DOWN:
				//�e�N�X�`�����W�̐ݒ�
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * nCntZ);
				break;

			case CMesh_sphere::SPHERE_MAX:
				//���W�̐ݒ�
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.z = sinf(fHalfRot) * cosf(fRot) * -m_size.x;
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.x = sinf(fHalfRot) * sinf(fRot) * -m_size.x;
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.y = cosf(fHalfRot) * -m_size.x;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * nCntZ);		
				break;

			default:
				break;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (int nCntZ = 0; nCntZ < HALFSPHEAR_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX < HALFSPHEAR_X_BLOCK + 1; nCntX++)
		{
			pIdx[0] = (WORD)((HALFSPHEAR_X_BLOCK + 1) + nCntX + nCntZ * (HALFSPHEAR_X_BLOCK + 1));
			pIdx[1] = (WORD)((HALFSPHEAR_X_BLOCK + 1) + nCntX + nCntZ * (HALFSPHEAR_X_BLOCK + 1) - (HALFSPHEAR_X_BLOCK + 1));

			pIdx += 2;
		}

		//�k�ރ|���S��
		if (nCntZ < HALFSPHEAR_Z_BLOCK - 1)
		{
			pIdx[0] = (WORD)((HALFSPHEAR_X_BLOCK + 1)* nCntZ + HALFSPHEAR_X_BLOCK);
			pIdx[1] = (WORD)((HALFSPHEAR_X_BLOCK + 1) * (nCntZ + 2));

			pIdx += 2;
		}
	}
	//�C���f�b�N�X�o�b�t�@�̊J��
	m_pIdxBuff->Unlock();

	//�@���̌v�Z
	Normal();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CMesh_sphere::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	//���S�t���O��true��
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CMesh_sphere::Update(void)
{
}

//======================================================
//�`�揈��
//======================================================
void CMesh_sphere::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���b�V���t�B�[���h�̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, HALFSPHEAR_VERTEX_NUM, 0, HALFSPHEAR_PRIMITIVE_NUM);

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	//���C�g��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//======================================================
//�@���̌v�Z
//======================================================
void CMesh_sphere::Normal(void)
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPolygon = 0; nCntPolygon < HALFSPHEAR_PRIMITIVE_NUM; nCntPolygon++)
	{
		// �ϐ��錾
		D3DXVECTOR3 Vtx[3] = {};
		D3DXVECTOR3 VtxLine[2] = {};

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			Vtx[nCnt] = pVtx[pIdx[nCntPolygon + nCnt]].pos;
		}

		if (Vtx[0] == Vtx[1]
			|| Vtx[0] == Vtx[2]
			|| Vtx[1] == Vtx[2])
		{// �k�ރ|���S���̏ꍇ
			continue;
		}

		// �|���S���̕Ӄx�N�g��
		VtxLine[0] = Vtx[1] - Vtx[0];
		VtxLine[1] = Vtx[2] - Vtx[0];

		// �ʖ@���x�N�g��
		D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (nCntPolygon % 2 == 0)
		{// �ʖ@���x�N�g��(�O�����̊O��)
			D3DXVec3Cross(&norVec, &VtxLine[0], &VtxLine[1]);
		}
		else
		{// �ʖ@���x�N�g��(�O�����̊O��)
			D3DXVec3Cross(&norVec, &VtxLine[1], &VtxLine[0]);
		}

		//���K��
		D3DXVec3Normalize(&norVec, &norVec);

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			//�@���x�N�g���̉��Z
			pVtx[pIdx[nCntPolygon + nCnt]].nor += norVec;

			//���K��
			D3DXVec3Normalize(&pVtx[pIdx[nCntPolygon + nCnt]].nor, &pVtx[pIdx[nCntPolygon + nCnt]].nor);
		}

		// �C���f�b�N�X�o�b�t�@�̃A�����b�N
		m_pIdxBuff->Unlock();

		// ���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//======================================================
//��������
//======================================================
CMesh_sphere * CMesh_sphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, SPHERE_TEX tex)
{
	CMesh_sphere* pSphere = new CMesh_sphere(3);

	if (pSphere != nullptr)
	{
		pSphere->SetPos(pos);
		pSphere->SetSize(size);
		pSphere->SetRot(rot);
		pSphere->SetTex(tex);

		if (FAILED(pSphere->Init()))
		{
			return nullptr;
		}
	}

	return pSphere;
}

//======================================================
//�e�N�X�`���ǂݍ��ݏ���
//======================================================
void CMesh_sphere::LoadTexture(const char * aFileName)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);
}

//======================================================
//�����蔻��
//======================================================
bool CMesh_sphere::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	//�����蔻��
	bool bCollison = false;

	//���_���̎擾
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�Ώۂ�pos�̎擾
	D3DXVECTOR3 posTarget = *pos;
	//�v�Z�p�ϐ�
	D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecLine[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecPos[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	float fInnerProduct[3] = { 0.0f };

	for (int nCntPolygon = 0; nCntPolygon < HALFSPHEAR_PRIMITIVE_NUM; nCntPolygon++)
	{
		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{//���_���W�̎擾
			aVtx[nCntVtx] = pVtx[pIdx[nCntPolygon + nCntVtx]].pos;

			//���[���h���W�ɃL���X�g
			//�ϐ��錾
			D3DXMATRIX        mtxWorldVtx;                //���[���h�}�g���b�N�X
			D3DXMATRIX        mtxRot, mtxTrans;           //�v�Z�p�}�g���b�N�X
				
			//���[���h�}�g���b�N�X�̏�����
			//�s�񏉊����֐�(��������[�s��]��[�P�ʍs��]�ɏ�����)
			D3DXMatrixIdentity(&mtxWorldVtx);

			//�ʒu�𔽉f
			//�s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, aVtx[nCntVtx].x, aVtx[nCntVtx].y, aVtx[nCntVtx].z);
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);        //�s��|���Z�֐�

			 //�����̔��f
			 //�s���]�֐� (��������[���[(y)�s�b�`(x)���[��(z)]�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

			//�s��|���Z�֐� (������ * ��O������������Ɋi�[)
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

			//�ʒu�𔽉f
			//�s��ړ��֐� (��������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);        //�s��|���Z�֐�

			aVtx[nCntVtx] = D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
		}

		if (aVtx[0] == aVtx[1]
			|| aVtx[0] == aVtx[2]
			|| aVtx[1] == aVtx[2])
		{//�k�ރ|���S���̏ꍇ
			continue;
		}

		// �|���S���̕Ӄx�N�g��
		aVecLine[0] = aVtx[1] - aVtx[0];
		aVecLine[1] = aVtx[2] - aVtx[1];
		aVecLine[2] = aVtx[0] - aVtx[2];

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{//���_�ƃ^�[�Q�b�g�̃x�N�g��
			aVecPos[nCntVtx] = posTarget - aVtx[nCntVtx];

			//���_�ƃ^�[�Q�b�g�̃x�N�g���ƃ|���S���̕Ӄx�N�g���̓��ς��Z�o
			fInnerProduct[nCntVtx] = (aVecLine[nCntVtx].z * aVecPos[nCntVtx].x) - (aVecLine[nCntVtx].x * aVecPos[nCntVtx].z);
		}

		if ((0.0f <= fInnerProduct[0]
			&& 0.0f <= fInnerProduct[1]
			&& 0.0f <= fInnerProduct[2])
			|| (0.0f >= fInnerProduct[0]
				&& 0.0f >= fInnerProduct[1]
				&& 0.0f >= fInnerProduct[2]))
		{// ����̐ݒ�
			bCollison = true;

			// �ʖ@���x�N�g��
			D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �ʖ@���x�N�g��(�O�����̊O��)
			D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);

			//���K��
			D3DXVec3Normalize(&norVec, &norVec);

			//����
			D3DXVECTOR3 sub = posTarget - m_pos;
			//D3DXVec3Normalize(&sub, &sub);

			//�x�N�g��
			D3DXVECTOR3 P = aVtx[0];
			D3DXVECTOR3 PA = m_pos - P;
			//D3DXVec3Normalize(&PA, &PA);
			D3DXVECTOR3 PB = posTarget - P;
			//D3DXVec3Normalize(&PB, &PB);

			//����
			float dotPA = D3DXVec3Dot(&PA, &norVec);
			float dotPB = D3DXVec3Dot(&PB, &norVec);
			if (dotPA == 0 || dotPB == 0)
			{
				continue;
			}
			D3DXVECTOR3 pointX = m_pos + sub *(dotPA / (dotPA + dotPB));

			if (nCntPolygon % 2 == 0)
			{
				norVec *= -1.0f;
			}

			//�p�x�̐ݒ�
			rot->x = norVec.x;
			rot->y = norVec.y;
			rot->z = norVec.z;
			//�ʒu�̐ݒ�
			//pos->y = (aVtx[0].y) - ((posTarget.x - aVtx[0].x) * norVec.x + (posTarget.z - aVtx[0].z) * norVec.z) / norVec.y; 
			//D3DXVECTOR3 cross[3] = {};
			//D3DXVECTOR3 X[3] = {};
			//for (int nCnt = 0; nCnt < 3; nCnt++)
			//{
			//	X[nCnt] = pointX - aVtx[nCnt];
			//}

			//D3DXVec3Cross(&cross[0], &aVecLine[0], &X[0]);
			//D3DXVec3Cross(&cross[1], &aVecLine[1], &X[1]);
			//D3DXVec3Cross(&cross[2], &aVecLine[2], &X[2]);

			//if ((int)cross[0].x == (int)cross[1].x
			//	&& (int)cross[0].y == (int)cross[1].y
			//	&& (int)cross[0].z == (int)cross[1].z
			//	&& (int)cross[0].x == (int)cross[2].x
			//	&& (int)cross[0].y == (int)cross[2].y
			//	&& (int)cross[0].z == (int)cross[2].z)
			//{
			//	pos->x = pointX.x;
			//	pos->y = pointX.y;
			//	pos->z = pointX.z;
			//}

#ifdef _DEBUG
			//�f�o�b�N
			CDebugProc::Print("���ɂ���|���S�� : %d\n", nCntPolygon);
			//float randcolr = (rand() % 10) * 1.0f;
			//float randcolg = (rand() % 10) * 1.0f;
			//float randcolb = (rand() % 10) * 1.0f;
			//pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			//pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			//pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
#endif //DEBUG

			break;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�����蔻���Ԃ�
	return bCollison;
}