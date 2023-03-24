//======================================================
//
//���b�V���t�B�[���h
//Author:����]��
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "debug.h"
#include <assert.h>
#include "meshfield.h"

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CMeshField::~CMeshField()
{
}

//======================================================
//����������
//======================================================
HRESULT CMeshField::Init(void)
{
	//������
	m_bTexture = false;
	m_fFriction = 0.45f;
	if (m_type == TYPE_ICE)
	{//�^�C�v���X�̏ꍇ���C�W����������
		m_fFriction = 0.2f;
	}
	m_nVertex = ((m_block.x + 1.0f) * (m_block.y + 1.0f));
	m_nIndex = (((m_block.x + 1.0f)  * m_block.x * 2.0f) * m_block.y + (m_block.y - 1.0f) * 2.0f);
	m_nPrimitive = (m_block.x * m_block.y * 2.0f + 4.0f * (m_block.y - 1.0f));

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (int)m_nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (int)m_nIndex,	//�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//�e�N�X�`���̐ݒ�
	if (m_type == TYPE_ICE)
	{
		LoadTexture("data\\TEXTURE\\ice.png");
	}
	else
	{
		LoadTexture("data\\TEXTURE\\block001.jpg");
	}

	VERTEX_3D * pVtx = NULL;		//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_block.y + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_block.x + 1; nCntX++)
		{
			//���_���W�̐ݒ�
			if (m_type == TYPE_X_UPPER)
			{//X�����ɉE���オ��
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, m_size.y * nCntX, -m_size.z * nCntZ + m_size.z);
			}
			else if (m_type == TYPE_X_LOWER)
			{//X�����ɉE��������
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, -m_size.y * nCntX, -m_size.z * nCntZ + m_size.z);
			}
			else if(m_type == TYPE_Z_UPPER)
			{//Z�����ɉE���オ��
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, -m_size.y * nCntZ, -m_size.z * nCntZ + m_size.z);
			}
			else
			{//Z�����ɉE��������
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, m_size.y * nCntZ, -m_size.z * nCntZ + m_size.z);
			}
			//nor�̐ݒ�
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxZ = 0; nCntIdxZ < m_block.y; nCntIdxZ++)
	{
		int nLine = nCntIdxZ * (int)((m_block.x + 1) * 2 + 2);	//��*(���_��*2�{�k�ރ|���S��)
		for (int nCntIdxX = 0; nCntIdxX <= m_block.x; nCntIdxX++)
		{
			//�����Ԗ�
			pIdx[nCntIdxX * 2 + nLine] = (WORD)(((m_block.x + 1) * (nCntIdxZ + 1)) + nCntIdxX);
			//��Ԗ�
			pIdx[nCntIdxX * 2 + 1 + nLine] = (WORD)(((m_block.x + 1) * nCntIdxZ) + nCntIdxX);
			if (nCntIdxZ < m_block.y - 1)
			{
				pIdx[(int)((m_block.x + 1) * 2) + nLine] = (WORD)(m_block.x + (m_block.x + 1) * nCntIdxZ);
				pIdx[(int)((m_block.x + 1) * 2) + nLine + 1] = (WORD)(((m_block.x + 1)) * (2 + nCntIdxZ));
			}
		}
	}
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	//�@���̌v�Z
	Normal();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CMeshField::Uninit(void)
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

	//���_�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Flag();
}

//======================================================
//�X�V����
//======================================================
void CMeshField::Update(void)
{
}

//======================================================
//�`�揈��
//======================================================
void CMeshField::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
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
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (int)m_nVertex, 0, (int)m_nPrimitive);	//�v���~�e�B�u(�|���S��(�O�p�`))��
	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//======================================================
//��������
//======================================================
CMeshField *CMeshField::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR2 &block, MESH_TYPE type, int nPriority)
{
	//���I�m��
	CMeshField *pMesh = new CMeshField(nPriority);

	if (pMesh != nullptr)
	{
		//������
		pMesh->SetSize(size);
		pMesh->SetPos(pos);
		pMesh->m_type = type;
		pMesh->m_rot = rot;
		pMesh->m_block = block;
		pMesh->Init();
	}

	return pMesh;
}

//======================================================
//�e�N�X�`���̓ǂݍ���
//======================================================
void CMeshField::LoadTexture(const char *aFileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}

//======================================================
//�@���̌v�Z
//======================================================
void CMeshField::Normal()
{
	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPolygon = 0; nCntPolygon < m_nPrimitive; nCntPolygon++)
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
//�����蔻��
//======================================================
bool CMeshField::Collision(D3DXVECTOR3 *pos, float fRadius,bool bPush)
{
	// �����蔻��
	bool bCollison = false;

	// ���_���̎擾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �^�[�Q�b�g���̐錾
	D3DXVECTOR3 posTarget = *pos;

	// �v�Z�p�ϐ�
	D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecLine[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecPos[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	float fInnerProduct[3] = { 0.0f };

	for (int nCntPolygon = 0; nCntPolygon < m_nPrimitive; nCntPolygon++)
	{
		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// ���_���W�̎擾
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
		{// �k�ރ|���S�����΂�
			continue;
		}

		// �|���S���̕Ӄx�N�g��
		aVecLine[0] = aVtx[1] - aVtx[0];
		aVecLine[1] = aVtx[2] - aVtx[1];
		aVecLine[2] = aVtx[0] - aVtx[2];

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// ���_�ƃ^�[�Q�b�g�̃x�N�g��
			aVecPos[nCntVtx] = posTarget - aVtx[nCntVtx];

			// ���_�ƃ^�[�Q�b�g�̃x�N�g���ƃ|���S���̕Ӄx�N�g���̓��ς��Z�o
			fInnerProduct[nCntVtx] = (aVecLine[nCntVtx].z * aVecPos[nCntVtx].x) - (aVecLine[nCntVtx].x * aVecPos[nCntVtx].z);
		}

		if ((0.0f <= fInnerProduct[0]
			&& 0.0f <= fInnerProduct[1]
			&& 0.0f <= fInnerProduct[2])
			|| (0.0f >= fInnerProduct[0]
				&& 0.0f >= fInnerProduct[1]
				&& 0.0f >= fInnerProduct[2]))
		{
			// �ʖ@���x�N�g��
			D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �ʖ@���x�N�g��
			D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);

			// �ʖ@���x�N�g���̐��K��
			D3DXVec3Normalize(&norVec, &norVec);

			// �����̌����_�̎Z�o
			float fIntersection = aVtx[0].y - ((posTarget.x - aVtx[0].x) * norVec.x + (posTarget.z - aVtx[0].z) * norVec.z) / norVec.y;

			if (fIntersection >= posTarget.y && fIntersection <= posTarget.y + fRadius)
			{// �ʒu�̐ݒ�
				if (bPush)
				{
					pos->y = fIntersection;
				}

				// ����̐ݒ�
				bCollison = true;

#ifdef _DEBUG
				//�f�o�b�N�\��
				/*CDebugProc::Print("���ɂ���|���S�� : %d\n", nCntPolygon);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon, pVtx[pIdx[nCntPolygon]].nor.x, pVtx[pIdx[nCntPolygon]].nor.y, pVtx[pIdx[nCntPolygon]].nor.z);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 1, pVtx[pIdx[nCntPolygon + 1]].nor.x, pVtx[pIdx[nCntPolygon + 1]].nor.y, pVtx[pIdx[nCntPolygon + 1]].nor.z);
				CDebugProc::Print("���_%d�̖@�� | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 2, pVtx[pIdx[nCntPolygon + 2]].nor.x, pVtx[pIdx[nCntPolygon + 2]].nor.y, pVtx[pIdx[nCntPolygon + 2]].nor.z);*/
				//pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				//pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				//pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
#endif // _DEBUG
				break;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�����Ԃ�
	return bCollison;
}