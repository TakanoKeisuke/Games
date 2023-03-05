//========================================================
//
//�J����
//Author:����]��
//
//========================================================
#include "camera.h"
#include <math.h>
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "planet.h"
#include "stage.h"
#include "player.h"
#include "inputPad.h"
#include <stdlib.h>
#include <time.h>

//======================================================
//�R���X�g���N�^
//======================================================
CCamera::CCamera()
{
	//�N���A

}

//======================================================
//�f�X�g���N�^
//======================================================
CCamera::~CCamera()
{//���������Ȃ�
}

//====================================
//�J�����̏���������
//====================================
void CCamera::Init(void)
{
	//���_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -340.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�p�x�Ƌ���
	m_rot = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
	m_fDistance = sqrtf(((m_posR.x - m_posV.x) * (m_posR.x - m_posV.x)) +
		((m_posR.z - m_posV.z) * (m_posR.z - m_posV.z)));

	//������
	m_move = D3DXVECTOR3(2.0f, 0.0f, 0.0f);
	posV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 200.0f);

	m_bLock = false;
}

//====================================
//�J�����̏I������
//====================================
void CCamera::Uninit(void)
{
}

//====================================
//�J�����̍X�V����
//====================================
void CCamera::Update(void)
{
	//���_�̐���
	if (CInputKeyboard::GetKeyboardPress(DIK_Z) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).x > 0.2f)
	{//Z�L�[�������ꂽ
		m_rot.y += D3DX_PI / 100.0f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_C) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).x < -0.2f)
	{//C�L�[�������ꂽ
		m_rot.y -= 0.03f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_N) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).y > 0.2f)
	{//N�L�[�������ꂽ
		m_rot.x += 0.05f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (CInputKeyboard::GetKeyboardPress(DIK_M) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_RIGHT_STICK, 0).y < -0.2f)
	{//M�L�[�������ꂽ
		m_rot.x -= 0.05f;
		m_posVDest.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posVDest.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}

	//�㉺�̔��]�̐���
	if (m_rot.x > 0.6f)
	{
		m_rot.x = 0.6f;
	}
	else if (m_rot.x < -0.3f)
	{
		m_rot.x = -0.3f;
	}

	//�p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//�v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		m_rotDest.y = pPlayer->GetRot().y + D3DX_PI;

	}
	//���K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//���ʂ�����
	if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT_THUMB, 0))
	{
		m_rot.y += (m_rotDest.y - m_rot.y);
		m_rot.x = 0.0f;
	}

	//���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//�߂��̘f�������b�N�I�����鏈��
	TargetPlanet();

	//����
	m_posR += (m_posRDest - m_posR) * 0.1f;
	m_posV += (m_posVDest - m_posV) * 0.1f;
}

//====================================
//�߂��̘f�������b�N�I�����鏈��
//====================================
void CCamera::TargetPlanet(void)
{
	//���擾
	std::vector<CPlanet*> pPlanet = CStage::GetPlanet();	//���ꂼ��̘f���̏��
	std::vector<CPlanet*> pNearPlanet;						//�ł��߂��f���̏��
	pNearPlanet.resize(CStage::m_nMaxPlanet);				//�f���̍ő吔���z����m�ۂ���
	CPlayer *pPlayer = CGame::GetPlayer();					//�v���C���[�̏��

	if (pPlayer != nullptr)
	{
		//�z��̓��I�m��
		std::vector<float> fDistance;
		std::vector<D3DXVECTOR3> PlanetPos;
		//���̎擾
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerRot = pPlayer->GetRot();
		//�z��̑傫���̐ݒ�
		fDistance.resize(CStage::m_nMaxPlanet);
		PlanetPos.resize(CStage::m_nMaxPlanet);

		//�f���ƃv���C���[�̋���
		for (int nCnt = 0; nCnt < CStage::m_nMaxPlanet; nCnt++)
		{
			if (pPlanet[nCnt] != nullptr)
			{
				fDistance[nCnt] = pPlanet[nCnt]->TargetDistance(pPlayer);
			}
		}

		//�����̔�r
		for (int nCount = 0; nCount < CStage::m_nMaxPlanet - 1; nCount++)
		{
			for (int nCount2 = nCount + 1; nCount2 < CStage::m_nMaxPlanet; nCount2++)
			{
				if (fDistance[nCount] < fDistance[nCount2])
				{
					pNearPlanet[0] = CStage::GetPlanet()[nCount];
				}
				else
				{
					pNearPlanet[0] = CStage::GetPlanet()[nCount2];
				}
			}
		}
		bool bInside = false;
		//�ł��߂��f���͈͓̔��ɂ��邩
		if (pNearPlanet[0] != nullptr)
		{
			bInside = pNearPlanet[0]->GetInside();
		}

		if (bInside)
		{
			D3DXVECTOR3 sub;
			sub = (PlayerPos - pNearPlanet[0]->GetPos());

			//���̒��S�����b�N�I��
			sub.y = 0.0f;
			D3DXVec3Normalize(&sub, &sub);
			sub *= 300.0f;
			sub.y = 50.0f;
			m_posVDest = PlayerPos + sub;
			m_posRDest = pNearPlanet[0]->GetPos();
			m_rot.y = atan2f(sub.x, sub.z);
		}
		else
		{//���ʂ̎��̃J����
			//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

			//���[���h�}�g���b�N�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, PlayerPos.x, PlayerPos.y, PlayerPos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

			//���[���h�ϊ��s��
			D3DXVec3TransformCoord(&m_posVDest, &posV, &mtxWorld);
			D3DXVec3TransformCoord(&m_posRDest, &posR, &mtxWorld);
		}
	}
}

//====================================
//�J�����̐ݒ菈��
//====================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 adjustPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_nQuakeFrameCount > 0)
	{
		m_nQuakeFrameCount--;
		////�����ŗh��̑傫����ς���
		adjustPos.x = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.y = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
		adjustPos.z = (float)(rand() % (int)(m_fQuakeMagnitude * 200) / 100) - m_fQuakeMagnitude;
	}
	//�r���[�}�g���b�N�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�̐���
	D3DXVECTOR3 PosV = (adjustPos + m_posV);
	D3DXVECTOR3 PosR = (adjustPos + m_posR);

	D3DXMatrixLookAtLH(&m_mtxView,
		&PosV,
		&PosR,
		&m_vecU);
	
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	//�v���W�F�N�V�����}�g���b�N�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),		//����p
		(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,		//�A�X�y�N�g��
		10.0f,		//�j�A
		100000.0f);	//�t�@�[
	//�v���W�F�N�V�����}�g���b�N�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//====================================
//�J������h�炷�l�̐ݒ�
//====================================
void CCamera::ShakeCamera(int nFrame, float fMagnitude)
{
	m_nQuakeFrameCount = nFrame;
	m_fQuakeMagnitude = fMagnitude;
}

//====================================
//�h��̒�~
//====================================
void CCamera::StopShake(void)
{
	m_fQuakeMagnitude = 0.0f;
	m_nQuakeFrameCount = 0;
}

//====================================
//���_�����_�̐ݒ�
//====================================
void CCamera::SetPos(const D3DXVECTOR3 PosV, const D3DXVECTOR3 PosR)
{
	m_posV = PosV;
	m_posR = PosR;
}