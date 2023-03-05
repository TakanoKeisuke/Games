//======================================================
//
//�v���C���[
//Author:����]��
//
//======================================================
#include "player.h"
#include "application.h"
#include "game.h"
#include "input.h"
#include "debug.h"
#include <assert.h>
#include <stdio.h>
#include "meshfield.h"
#include "BoxHitbox.h"
#include "CylinderHitbox.h"
#include "model.h"
#include "mesh_sphere.h"
#include "sphere.h"
#include "shadow.h"
#include "motion.h"
#include "fade.h"
#include "planet.h"
#include "gimmick.h"
#include "SphereHitbox.h"
#include "stage.h"
#include "sound.h"
#include "particle.h"
#include "inputPad.h"
#include "timer.h"

//�ÓI�����o�ϐ��錾
float CPlayer::m_fAcceleration = 1.0f;		//�����W��
float CPlayer::m_fJump = 20.0f;				//�W�����v��
//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CPlayer::~CPlayer()
{

}

//======================================================
//����������
//======================================================
HRESULT CPlayer::Init(void)
{
	//������
	m_nCntModel = 0;
	m_nCntGoal = 0;
	m_fCT = 0.0f;
	m_fBuffQuantity = 0.0f;
	m_fFriction = 0.45f;
	m_fDash = 1.0f;
	m_fSlowFall = 1.0f;
	m_nLife = 3;
	m_nBuffTime = 0;
	m_pHitbox = nullptr;
	m_Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Originpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXQuaternionIdentity(&m_quat);
	D3DXMatrixIdentity(&m_mtxQuat);
	m_bModel = false;
	m_bShadow = true;
	m_bCollisionField = {};
	m_bJumping = false;
	m_bGoal = false;
	m_bInside = false;
	m_bCollisionPlanet = false;

#ifdef _DEBUG
	//�f�o�b�N���[�h
	m_nLife = 300;
#endif // _DEBUG

	//���f���̐���
	LoadPlayer();

	return S_OK;
}

//======================================================
//�X�V����
//======================================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();	//�I������
			delete m_apModel[nCnt];		//�j������
			m_apModel[nCnt] = nullptr;	//null�ɂ���
		}
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//���[�V�����̔j������
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//�U���̃q�b�g�{�b�N�X�̔j������
	if (m_pAttackHitbox != nullptr)
	{
		m_pAttackHitbox->Release();
		m_pAttackHitbox = nullptr;
	}

	//�������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CPlayer::Update(void)
{
	//�d��
	if (m_move.y >= -10.0f && !m_bInside)
	{
		m_move.y -= 1.0f;
	}

	//���[�V�����̍X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	//���[�V�����̐ݒ�
	m_pMotion->SetPresentAnim(0);

	//�L�[����
	Input();

	if (m_pHitbox != nullptr)
	{
		//�I�u�W�F�N�g�̓����蔻��
		CollisionObj();
	}

	//�X�e�[�W�̓����蔻��
	CollisionStage();

	//�v���C���[�̋���
	BuffPlayer();

	//�v���C���[�����̍�����藎������
	if (GetPos().y <= -200.0f)
	{//�_���[�W���󂯂�
		m_pHitbox->SetEffect(CHitbox::EFFECT_DAMAGE);
		//�v���C���[�̈ʒu��߂�
		SetPos(m_Originpos);
	}

	if (m_bGoal)
	{//�S�[��������J�E���g����
		m_nCntGoal++;
	}
	//�S�[���J�E���g��120�𒴂�����
	if (m_nCntGoal >= 60 && CFade::GetFade() == CFade::FADE_NONE)
	{//�J�ڂ���
		m_nCntGoal = 0;
		//���[�h�ݒ�
		CFade::SetFade(CApplication::MODE_RESULT);
	}
}

//======================================================
//�`�揈��
//======================================================
void CPlayer::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{//���G��Ԃ�������A�_�ł�����
	//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		if (m_bInside)
		{//���ɏ���Ă���Ȃ�
			D3DXMatrixMultiply(&mtxRot, &mtxRot, &m_mtxQuat);
		}
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			//���f���̕`��
			m_apModel[nCnt]->Draw();
		}
	}
}

//======================================================
//��������
//======================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority)
{
	//���I�m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		//������
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_Originpos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_size = size;

		//�A�j���[�V�����̐���
		pPlayer->m_pMotion = CMotion::Create(CMotion::ANIM_TYPE_PLAYER);
		//�q�b�g�{�b�N�X�̐���
		pPlayer->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_PLAYER, pPlayer);
	}

	return pPlayer;
}

//======================================================
//�I�u�W�F�N�g�Ɠ���������
//======================================================
void CPlayer::CollisionObj(void)
{
	//�����擾
	CCamera *pCamera = CApplication::GetCamera();		//�J�����̏��
	CTimer *pTimer = CGame::GetTimer();					//�X�R�A�̏��

	//�����蔻��̍X�V
	m_pHitbox->SetPos(m_pos);
	m_pHitbox->Update();

	//�����蔻��̃G�t�F�N�g���擾
	CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

	switch (effect)
	{

	case CHitbox::EFFECT_GOAL:
		//�G�ꂽ��S�[��
		m_bGoal = true;
		break;

	case CHitbox::EFFECT_DAMAGE:
		//�̗͂����炷
		if (m_nLife > 0)
		{
			m_nLife--;
		}

		//�J������h�炷
		pCamera->ShakeCamera(20, 3.0f);

		//�m�b�N�o�b�N�̏���(�V�������x�̐ݒ�)
		D3DXVec3Normalize(&m_move, &m_move);
		m_move.x *= -50.0f;
		m_move.y = 10.0f;
		m_move.z *= -50.f;

		//���G��ԃJ�E���^�[��ݒ肷��
		m_nInvincibleCnt = 60;

		//�̗͂��Ȃ��Ȃ�����
		if (m_nLife <= 0)
		{
			//�X�R�A�̌��Z
			pTimer->SubTimer(5);
		}

		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
			m_pHitbox->SetInvincibility(true);						//���G��Ԃ�ݒ肷��
		}
		break;

	case CHitbox::EFFECT_HEAL:
		//�̗͂�2�ȉ��̎����₷
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
		}
		break;

	case CHitbox::EFFECT_FLY:
		//��΂�
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_Y, 0) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_X, 0) && m_bJumping)
		{
			if (m_fBuffQuantity != 0.0f)
			{//�W�����v�͂���������Ă�����
				m_move.y = (m_fJump + 10.0f) * m_fBuffQuantity;
			}
			else
			{
				m_move.y = m_fJump + 50.0f;
			}
			//�W�����v������Ԃɂ���
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}
		if (m_bInside && m_bJumping)
		{
			//������ɔ�΂�
			m_move = m_norVec * 120.0f;
			//�W�����v������Ԃɂ���
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}


		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
		}
		break;

	case CHitbox::EFFECT_SPEED:
		//�������ʂ̎�ނ�ݒ�
		m_type = TYPE_SPEED;
		//�������ʂ̎��Ԃ�ݒ�
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
		}
		break;

	case CHitbox::EFFECT_JUMP:
		//�������ʂ̎�ނ�ݒ�
		m_type = TYPE_JUMP;
		//�������ʂ̎��Ԃ�ݒ�
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
		}
		break;

	case CHitbox::EFFECT_CHECKPOINT:

		//���X�|�[���n�_�̐ݒ�
		m_Originpos = m_pHitbox->GetPos();
		//�̗͂�2�ȉ��̎����₷
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
		}
		break;

	default:
		break;
	}

	//���G����
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//�J�E���^�[�̍X�V

		if (m_nInvincibleCnt <= 0)
		{//0�ɂȂ�����A
			if (m_pHitbox != nullptr)
			{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
				m_pHitbox->SetInvincibility(false);			//���G��Ԃ��I���悤�ɐݒ肷��
			}
		}
	}
}

//======================================================
//�v���C���[�̋�������
//======================================================
void CPlayer::BuffPlayer(void)
{
	//�v���C���[�̃^�C�v�ɂ���ē����鋭��
	if (m_type != TYPE_NONE && m_nBuffTime > 0)
	{
		BuffEffect(m_type);
		m_type = TYPE_NONE;
	}

	//�������ʂ̎��Ԃ�����
	if (m_nBuffTime > 0)
	{
		m_nBuffTime--;
		//�p�[�e�B�N���̐���
		CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, m_pos, 30, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));
	}

	//�������ʂ̃��Z�b�g
	if (m_nBuffTime == 0)
	{
		m_fAcceleration = 1.0f;
		m_fSlowFall = 1.0f;
	}
}

//======================================================
//�������ʏ���
//======================================================
void CPlayer::BuffEffect(PLAYER_TYPE type)
{
	switch (type)
	{
	case CPlayer::TYPE_SPEED:
		//����
		m_fAcceleration = 2.0f;
		//����
		m_nBuffTime = 300;
		break;

	case CPlayer::TYPE_JUMP:
		//�������x�ቺ
		m_fSlowFall = 4.0f;
		//����
		m_nBuffTime = 360;
		break;

	default:
		break;
	}
}

//======================================================
//�X�e�[�W�Ɠ���������
//======================================================
void CPlayer::CollisionStage(void)
{
	//���b�V���̏��擾
	std::vector<CMeshField*> pMesh = CStage::GetMesh();
	bool b = true;
	D3DXVECTOR3 shadowPos = m_apModel[0]->GetShadowPos();
	//���b�V���t�B�[���h�̐� ���n�̔��������
	m_bCollisionField.resize(CStage::m_nMaxMesh);
	for (int nCnt = 0; nCnt < CStage::m_nMaxMesh; nCnt++)
	{
		if (pMesh[nCnt] != nullptr)
		{
			//���b�V���̓����蔻��
			m_bCollisionField[nCnt] = pMesh[nCnt]->Collision(&m_pos, (m_size.y / 2.0f));
		}
		//���n���Ă���Ƃ��̓W�����v�ł���
		if (m_bCollisionField[nCnt])
		{
			m_bJumping = true;
			m_fFriction = pMesh[nCnt]->GetFriction();

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{//���f���̉e
				m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, m_pos.y + 0.2f, m_pos.z));

				b = pMesh[nCnt]->ShadowCollision(&D3DXVECTOR3(shadowPos.x, m_pos.y, shadowPos.z), 0.0f);

				if (!b)
				{
					m_bShadow = false;
				}
				else
				{
					m_bShadow = true;
				}
			}

			break;
		}
		else
		{
			m_fFriction = 0.45f;
			m_bJumping = false;

			//b = pMesh[nCnt]->ShadowCollision(&D3DXVECTOR3(shadowPos.x, 0.0f, shadowPos.z), 0.0f);

			//if (!b)
			//{
			//	m_bShadow = false;
			//}
			//else
			//{
			//	m_bShadow = true;
			//}
		}
	}




	//�f���̏��擾
	std::vector<CPlanet*> pPlanet = CStage::GetPlanet();	//���ꂼ��̘f���̏��
	std::vector<float> fDif;								//���ꂼ��̘f���Ƃ̋���
	std::vector<CPlanet*> pNearPlanet;						//�ł��߂��f���̏��
	fDif.resize(CStage::m_nMaxPlanet);
	pNearPlanet.resize(CStage::m_nMaxPlanet);
	//�f���ƃv���C���[�̋���
	for (int nCnt = 0; nCnt < CStage::m_nMaxPlanet; nCnt++)
	{
		if (pPlanet[nCnt] != nullptr)
		{
			fDif[nCnt] = pPlanet[nCnt]->TargetDistance(this);
		}
	}

	//�����̔�r
	for (int nCount = 0; nCount < CStage::m_nMaxPlanet - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < CStage::m_nMaxPlanet; nCount2++)
		{
			if (fDif[nCount] < fDif[nCount2])
			{
				pNearPlanet[0] = CStage::GetPlanet()[nCount];
			}
			else
			{
				pNearPlanet[0] = CStage::GetPlanet()[nCount2];
			}
		}
	}

	if (pNearPlanet[0] != nullptr)
	{
		//�f���̓����蔻��
		m_bCollisionPlanet = pNearPlanet[0]->CollisionSphere(&m_pos, &m_size);
		m_bInside = pNearPlanet[0]->SetGravity(&m_pos, &m_size, &m_move);

		if (m_bCollisionPlanet)
		{//�f���ɏ���Ă���Ƃ�
			m_bJumping = true;
		}

		//================================
		//�p�����킹��]
		//================================

		//��]���̎Z�o
		m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���x�N�g��
		m_norVec = m_pos - pNearPlanet[0]->GetPos();			//�@���x�N�g��
		D3DXVECTOR3 vecOver = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//������x�N�g��

		//�@���x�N�g���̐��K��
		D3DXVec3Normalize(&m_norVec, &m_norVec);
		//�O�ς������Ď��x�N�g�����o��
		D3DXVec3Cross(&m_vecAxis, &vecOver, &m_norVec);
		//���ς̎Z�o
		float dot = D3DXVec3Dot(&vecOver, &m_norVec);
		//����]�ɕK�v�Ȋp�x�̎Z�o
		float angle = acosf(dot / (D3DXVec3Length(&vecOver) * D3DXVec3Length(&m_norVec)));

		//�N�H�[�^�j�I���̎Z�o
		m_quat = D3DXQUATERNION(0, 0, 0, 1);
		D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, angle);
		D3DXMatrixRotationQuaternion(&m_mtxQuat, &m_quat);
	}
}

//======================================================
//���͏���
//======================================================
void CPlayer::Input(void)
{
	//�J�����̏��̎擾
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//�v���C���[�̈ړ�
	if (CInputPad::GetJoypadPress(CInputPad::JOYKEY_A, 0))
	{//A�{�^��������������ƃ_�b�V��
		m_fDash = 1.5f;
	}
	else
	{//�����Ɩ߂�
		m_fDash = 1.0f;
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_UP) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
	{//������������
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//������������
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) == true || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//������������	
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x -= sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else
		{//��
		 //�i�s�����̃x�N�g��
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x += sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		//���[�V�����̐ݒ�
		m_pMotion->SetPresentAnim(1);
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_DOWN) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
	{
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//������������
		 //�i�s�����̃x�N�g��
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//������������
		 //�i�s�����̃x�N�g��
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x -= sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else
		{//��
			if (!m_bInside)
			{//���b�V���t�B�[���h�ɏ���Ă��鎞
				m_move.x -= sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//���͈͓̔�
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		//���[�V�����̐ݒ�
		m_pMotion->SetPresentAnim(1);
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
	{
		if (!m_bInside)
		{//���b�V���t�B�[���h�ɏ���Ă��鎞
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//���͈͓̔�
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		//���[�V�����̐ݒ�
		m_pMotion->SetPresentAnim(1);
	}
	//������������
	else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
	{
		if (!m_bInside)
		{//���b�V���t�B�[���h�ɏ���Ă��鎞
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//���͈͓̔�
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		//���[�V�����̐ݒ�
		m_pMotion->SetPresentAnim(1);
	}

	//�ړI�̊p�x�̐��K��
	if (m_rotDest.y - GetRot().y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//����
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	//���݂̊p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//�M�~�b�N�̏�ɏ���Ă�����W�����v�ł���悤�ɂ���
	for (int nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
	{
		if (!m_bJumping)
		{//�W�����v���Ă��Ȃ���΁A����Ă��邩���肷��
			std::vector<CGimmick*> pGimmick = CStage::GetGimmick();
			std::vector<bool> bGimmick;
			bGimmick.resize(CStage::m_nMaxGimmick);
			for (nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
			{
				if (pGimmick[nCnt] != nullptr)
				{
					bGimmick[nCnt] = pGimmick[nCnt]->GetLanding();
					//���n���Ă���Ƃ��̓W�����v�ł���
					if (bGimmick[nCnt])
					{
						for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
						{//���f���̉e
							m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, m_pos.y + 0.2f, m_pos.z));
						}
						m_move.y = 0.0f;
						m_pos.y = pGimmick[nCnt]->GetPos().y + (pGimmick[nCnt]->GetSize().y / 2.0f);
						m_bJumping = true;
					}
				}
			}
		}
	}

	//�W�����v
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && m_bJumping
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && m_bJumping)
	{
		if (m_bInside)
		{
			m_move = m_norVec * 10.0f;
		}
		else
		{
			if (m_fBuffQuantity != 0.0f)
			{//�W�����v�͂���������Ă�����
				m_move.y = m_fJump * m_fBuffQuantity;
			}
			else
			{//�W�����v�͂ɕω����Ȃ����
				m_move.y = m_fJump;
			}
		}
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		//�W�����v���Ă����Ԃɂ���
		m_bJumping = false;
	}

	////�N�[���^�C�����Ȃ���΍U��
	//if (CInputKeyboard::GetKeyboardTrigger(DIK_V) && m_fCT <= 0.0f && m_pAttackHitbox == nullptr)
	//{
	//	//�U��
	//	Attack();
	//}

	//if (m_fCT > 0)
	//{//�U������������
	//	//�N�[���^�C���̌���
	//	m_fCT--;
	//}

	//if (m_fCT <= 0.0f && m_pAttackHitbox != nullptr)
	//{//�J�E���^�[��0�ȉ��ɂȂ�����
	//	m_pAttackHitbox->Release();			//�q�b�g�{�b�N�X��j������
	//	m_pAttackHitbox = nullptr;			//�|�C���^��null�ɂ���
	//	m_fCT = 0;							//�J�E���^�[��0�ɖ߂�
	//}

	//�O��ʒu��ۑ�
	m_posOld = m_pos;

	//�ړ��ʂ����Z
	m_pos += m_move;

	//�ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * m_fFriction;
	m_move.z += (0.0f - m_move.z) * m_fFriction;
	if (m_bInside)
	{
		m_move.y += (0.0f - m_move.y) * m_fFriction;
	}
	else
	{
		if (m_move.y < 0.0f)
		{
			m_move.y += (0.0f - m_move.y) * 0.1f * m_fSlowFall;
		}
		else
		{
			m_move.y += (0.0f - m_move.y) * 0.1f;
		}
	}

#ifdef _DEBUG
	//�f�o�b�N�\��
	CDebugProc::Print("���݂̊p�x%f\n", m_rot.y);
	CDebugProc::Print("���݂̈ʒu : %f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("�J�����̊p�x : %f\n", CameraRot.y);
	CDebugProc::Print("�ړI�̊p�x : %f\n", m_rotDest.y);
	CDebugProc::Print("�ړ��� : %f %f %f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("�N�H�[�^�j�I�� %f %f %f %f\n", m_quat.x, m_quat.y, m_quat.z, m_quat.w);
	CDebugProc::Print("���x�N�g�� %f %f %f \n", m_vecAxis.x, m_vecAxis.y, m_vecAxis.z);
	CDebugProc::Print("�������ʂ̎��� %d \n", m_nBuffTime);
#endif // _DEBUG
}

//======================================================
//�U������
//======================================================
void CPlayer::Attack(void)
{
	//�N�[���^�C���̐ݒ�
	m_fCT = 60.0f;

	//�v���C���[�̓����蔻��ɉ��Z���镪
	D3DXVECTOR3 Attack_size = m_size + D3DXVECTOR3(7.0f, 0.0f, 7.0f);

	//�q�b�g�{�b�N�X�̐���
	m_pAttackHitbox = CCylinderHitbox::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), Attack_size, CHitbox::TYPE_OBSTACLE, 0, this, CHitbox::EFFECT_PUSH);
}

//======================================================
//���f���̓ǂݍ���
//======================================================
void CPlayer::LoadPlayer(void)
{
	int nNumParts;
	char aText[2000];						//��������i�[����z��
	char FileName[MAX_MODEL][2000];			//2�����z��

	FILE *pFile; //�t�@�C���|�C���^��錾

	pFile = fopen("data/model/model.txt", "r");

	aText[0] = '\0';	//������Ȃ�

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
	 //�t�@�C���ɓ��͂����f�[�^�������o������
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fscanf(pFile, "%s", &aText[0]);    //�t�@�C�����當�����ǂݍ���(�ǂݍ��݊J�n)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
				continue;
			}

			//�t�@�C���l�[���𕡐����͂���
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);					// = ��ǂݍ���
				fscanf(pFile, "%s", &FileName[m_nCntModel][0]);	//0�Ԗڂ���ǂݍ��܂��

				//���f���p�[�c�̐���
				m_apModel[m_nCntModel] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//���f�����̃J�E���g
				m_nCntModel++;
			}

			if (strcmp(&aText[0], "CHARACTERSET") == 0)
			{
				while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
						continue;
					}

					if (strcmp(&aText[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = ��ǂݍ���
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "PARTSSET") == 0)
					{
						D3DXVECTOR3 pos, rot;
						int IndexParent = 0;	//�e�̔ԍ�
						int Ind = 0;

						while (strcmp(&aText[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //��s���Ɠǂݍ���
								continue;
							}

							if (strcmp(&aText[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &Ind);
							}
							else if (strcmp(&aText[0], "PARENT") == 0)
							{

								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &IndexParent);
							}
							else if (strcmp(&aText[0], "POS") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								pos = D3DXVECTOR3(x, y, z);
							}
							else if (strcmp(&aText[0], "ROT") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								rot = D3DXVECTOR3(x, y, z);
							}
						}

						//���f���p�[�c�̓ǂݍ���
						m_apModel[Ind]->SetModel(&FileName[Ind][0]);
						m_apModel[Ind]->SetId(Ind);

						//���f���p�[�c�ɏ�񂪓����Ă�����
						if (m_apModel[Ind])
						{
							//���f���p�[�c�̈ʒu�ƌ����̐ݒ�
							m_apModel[Ind]->SetRot(rot);
							m_apModel[Ind]->SetPos(pos);
						}

						//�e�̔ԍ���0��艺��������
						if (IndexParent < 0)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_apModel[Ind]->SetParent(nullptr);
						}
						//�e�̔ԍ������f���p�[�c��菬����������
						else if (IndexParent < MAX_MODEL)
						{
							//���f���p�[�c�̃}�g���b�N�X�̐ݒ�
							m_apModel[Ind]->SetParent(m_apModel[IndexParent]);
						}
					}
				}
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}