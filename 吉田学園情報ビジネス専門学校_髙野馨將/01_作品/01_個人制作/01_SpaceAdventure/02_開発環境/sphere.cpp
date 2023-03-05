//======================================================
//
//Sphere
//Author:����]��
//
//======================================================
#include "input_keyboard.h"
#include "sphere.h"
#include "application.h"
#include "game.h"
#include "input.h"
#include "debug.h"
#include <assert.h>
#include "meshfield.h"
#include "main.h"
#include "BoxHitbox.h"
#include "CylinderHitbox.h"
#include "stage.h"

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CSphere::CSphere(int nPriority) : CObjectX(nPriority)
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//======================================================
//�f�X�g���N�^
//======================================================
CSphere::~CSphere()
{

}

//======================================================
//����������
//======================================================
HRESULT CSphere::Init(void)
{
	//������
	D3DXMatrixIdentity(&m_mtxRot);
	m_quat = {};
	m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fValueRot = 0.0f;
	m_pHitbox = nullptr;
	m_bModel = false;

	//���f���̐ݒ�
	LoadModel("data\\model\\sphere.x");

	return S_OK;
}

//======================================================
//�X�V����
//======================================================
void CSphere::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	Flag();
}

//======================================================
//�X�V����
//======================================================
void CSphere::Update(void)
{
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
	 //�ʒu���X�V����
		D3DXVECTOR3 newPos = GetPos() + m_pHitbox->GetRelativePos();
		m_pHitbox->SetPos(newPos);
	}
	//�L�[����
	Input();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

}

//======================================================
//�`�揈��
//======================================================
void CSphere::Draw(void)
{
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxWorld;

	//���f���̏��̎擾
	D3DXVECTOR3 SpherePos = GetPos();

	//���[���h�}�g���b�N�X
	mtxWorld = GetWorldMatrix();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�N�H�[�^�j�I���̍쐬
	D3DXQuaternionRotationAxis(&m_quat,&m_vecAxis,m_fValueRot);

	//�����̔��f
	D3DXMatrixRotationQuaternion(&mtxRot, &m_quat);
	D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &m_mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, SpherePos.x, SpherePos.y, SpherePos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(mtxWorld);

	//�`��
	CObjectX::DrawSphere();
}

//======================================================
//��������
//======================================================
CSphere *CSphere::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, int nPriority)
{
	//���I�m��
	CSphere *pSphere;
	pSphere = new CSphere(nPriority);

	if (pSphere != nullptr)
	{
		//������
		pSphere->Init();
		pSphere->SetPos(pos);
		pSphere->SetRot(rot);
	}
	
	//�q�b�g�{�b�N�X�𐶐�����
	pSphere->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 35.0f, 10.0f), CHitbox::TYPE_OBSTACLE, pSphere);
	
	return pSphere;
}

//======================================================
//���͏���
//======================================================
void CSphere::Input(void)
{
	//���f���̏��̎擾
	D3DXVECTOR3 SpherePos = GetPos();
	D3DXVECTOR3 SphereRot = GetRot();
	D3DXVECTOR3 SphereMove = GetMove();
	D3DXVECTOR3 SphereSize = GetSize();

	//�J�����̏��̎擾
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//�v���C���[�̈ړ�
	if (CInputKeyboard::GetKeyboardPress(DIK_I)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).y  < -0.5f*/)
	{//������������
		if (CInputKeyboard::GetKeyboardPress(DIK_L)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
		{//������������
			SphereMove.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z += cosf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_J)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
		{//������������
			SphereMove.x -= sinf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
		}
		else
		{//��
			SphereMove.z += cosf(CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);
			m_rotDest.y = CameraRot.y + D3DX_PI;
		}
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_K) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).y  > 0.5f*/)
	{
		if (CInputKeyboard::GetKeyboardPress(DIK_L)/* || GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
		{//������������
			SphereMove.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_J) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
		{//������������
			SphereMove.x -= sinf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);

			SphereMove.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);

			//m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{//��
			SphereMove.z -= cosf(CameraRot.y) * 1.0f;
			SphereRot.x += SphereMove.z / (SphereSize.x / 2.0f);
			//m_rotDest.y = CameraRot.y;
		}
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_L) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  > 0.5f*/)
	{
		SphereMove.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * 1.0f;
		SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);
		//m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_J) /*|| GetJoypadStick(JOYKEY_LEFT_STICK, 0).x  < -0.5f*/)
	{
		SphereMove.x -= sinf(D3DX_PI * 0.5f + CameraRot.y) * 1.0f;
		SphereRot.z += SphereMove.x / (SphereSize.z / 2.0f);
		//m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
	}

	//�ړI�̊p�x�̐��K��
	if (m_rotDest.y - GetRot().y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - SphereRot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//����
	SphereRot.y += (m_rotDest.y - SphereRot.y) * 0.1f;

	//���݂̊p�x�̐��K��
	if (SphereRot.y > D3DX_PI)
	{
		SphereRot.y = SphereRot.y - D3DX_PI * 2;
	}
	else if (SphereRot.y < -D3DX_PI)
	{
		SphereRot.y = SphereRot.y + D3DX_PI * 2;
	}

	//�ړ��ʂ̉��Z
	SpherePos += SphereMove;

	//�ړ��ʂ��X�V
	SphereMove.x += (0.0f - SphereMove.x) * 0.45f;
	SphereMove.z += (0.0f - SphereMove.z) * 0.45f;

	//��]��
	m_vecAxis = D3DXVECTOR3(SphereMove.z, SphereMove.y, -SphereMove.x);
	//��]��
	m_fValueRot = D3DXVec3Length(&SphereMove) / D3DXVec3Length(&SphereSize);

	//rot�̐ݒ�
	SetRot(SphereRot);

	////���b�V���̓����蔻��
	//std::vector<CMeshField*> pMesh = CStage::GetMesh();
	//if (pMesh != nullptr)
	//{
	//	pMesh->Collision(&SpherePos, SphereSize.y / 2.0f);
	//}

	//pos�̐ݒ�
	SetPos(SpherePos);

	//move�̐ݒ�
	SetMove(SphereMove);
}