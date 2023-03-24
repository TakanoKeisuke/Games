//======================================================
//
//vC[
//Author:ûüì]
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

//ÃIoÏé¾
float CPlayer::m_fAcceleration = 1.0f;		//Á¬W
float CPlayer::m_fJump = 20.0f;				//WvÍ
int CPlayer::m_nGoalCnt = 30;				//S[©çtF[hÌÔ

//======================================================
//I[o[[h³ê½RXgN^
//======================================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{

}

//======================================================
//fXgN^
//======================================================
CPlayer::~CPlayer()
{

}

//======================================================
//ú»
//======================================================
HRESULT CPlayer::Init(void)
{
	//ú»
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
	//fobN[h
	m_nLife = 300;
#endif // _DEBUG

	//fÌ¶¬
	LoadPlayer();

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();	//I¹
			delete m_apModel[nCnt];		//jü·é
			m_apModel[nCnt] = nullptr;	//nullÉ·é
		}
	}

	//qbg{bNXÌjü
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//[VÌjü
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//UÌqbg{bNXÌjü
	if (m_pAttackHitbox != nullptr)
	{
		m_pAttackHitbox->Release();
		m_pAttackHitbox = nullptr;
	}

	//ðú
	Flag();
}

//======================================================
//XV
//======================================================
void CPlayer::Update(void)
{
	//dÍ
	if (m_move.y >= -10.0f && !m_bInside)
	{
		m_move.y -= 1.0f;
	}

	//[VÌXV
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	//[VÌÝè
	m_pMotion->SetPresentAnim(0);

	//L[üÍ
	Input();

	if (m_pHitbox != nullptr)
	{
		//IuWFNgÌ½è»è
		CollisionObj();
	}

	//vC[Ì­»
	BuffPlayer();

	//Xe[WÌ½è»è
	CollisionStage();

	//M~bNÌ½è»è
	CollisionGimmick();

	//vC[ªêèÌ³æè¿½ç
	if (GetPos().y <= -200.0f)
	{//_[Wðó¯é
		m_pHitbox->SetEffect(CHitbox::EFFECT_DAMAGE);
		//­»øÊÌjü
		m_nBuffTime = 0;
		//vC[ÌÊuðß·
		SetPos(m_Originpos);
	}

	if (m_bGoal)
	{//S[µ½çJEg·é
		m_nCntGoal++;
	}
	//S[JEgª120ð´¦½ç
	if (m_nCntGoal >= m_nGoalCnt && CFade::GetFade() == CFade::FADE_NONE)
	{//JÚ·é
		m_nCntGoal = 0;
		//[hÝè
		CFade::SetFade(CApplication::MODE_RESULT);
	}
}

//======================================================
//`æ
//======================================================
void CPlayer::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{//³GóÔ¾Á½çA_Å³¹é
	//foCXÌæ¾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		//vZp}gbNX
		D3DXMATRIX mtxRot, mtxTrans;

		//[h}gbNXÌú»
		D3DXMatrixIdentity(&m_mtxWorld);

		//ü«ð½f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		if (m_bInside)
		{//ÉæÁÄ¢éÈç
			D3DXMatrixMultiply(&mtxRot, &mtxRot, &m_mtxQuat);
		}
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//Êuð½f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//[h}gbNXÌÝè
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			//fÌ`æ
			m_apModel[nCnt]->Draw();
		}
	}
}

//======================================================
//¶¬
//======================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority)
{
	//®ImÛ
	CPlayer *pPlayer;
	pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		//ú»
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_Originpos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_size = size;

		//Aj[VÌ¶¬
		pPlayer->m_pMotion = CMotion::Create(CMotion::ANIM_TYPE_PLAYER);
		//qbg{bNXÌ¶¬
		pPlayer->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_PLAYER, pPlayer);
	}

	return pPlayer;
}

//======================================================
//IuWFNgÆ½Á½
//======================================================
void CPlayer::CollisionObj(void)
{
	//îñðæ¾
	CCamera *pCamera = CApplication::GetCamera();		//JÌîñ
	CTimer *pTimer = CGame::GetTimer();					//XRAÌîñ

	//½è»èÌXV
	m_pHitbox->SetPos(m_pos);
	m_pHitbox->Update();

	//½è»èÌGtFNgðæ¾
	CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

	switch (effect)
	{

	case CHitbox::EFFECT_GOAL:
		//Gê½çS[
		m_bGoal = true;
		break;

	case CHitbox::EFFECT_DAMAGE:
		//ÌÍð¸ç·
		if (m_nLife > 0)
		{
			m_nLife--;
		}

		//Jðhç·
		pCamera->ShakeCamera(20, 3.0f);

		//mbNobNÌ(Vµ¢¬xÌÝè)
		D3DXVec3Normalize(&m_move, &m_move);
		m_move.x *= -50.0f;
		m_move.y = 10.0f;
		m_move.z *= -50.f;

		//³GóÔJE^[ðÝè·é
		m_nInvincibleCnt = 60;

		//ÌÍªÈ­ÈÁ½ç
		if (m_nLife <= 0)
		{
			//XRAÌ¸Z
			pTimer->SubTimer(5);
		}

		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
			m_pHitbox->SetInvincibility(true);						//³GóÔðÝè·é
		}
		break;

	case CHitbox::EFFECT_HEAL:
		//ÌÍª2ÈºÌâ·
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
		}
		break;

	case CHitbox::EFFECT_FLY:
		//òÎ·
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_Y, 0) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_X, 0) && m_bJumping)
		{
			if (m_fBuffQuantity != 0.0f)
			{//WvÍª²®³êÄ¢½ç
				m_move.y = (m_fJump + 10.0f) * m_fBuffQuantity;
			}
			else
			{
				m_move.y = m_fJump + 20.0f;
			}
			//Wvµ½óÔÉ·é
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}
		if (m_bInside && m_bJumping)
		{
			//ãûüÉòÎ·
			m_move = m_norVec * 120.0f;
			//Wvµ½óÔÉ·é
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}


		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
		}
		break;

	case CHitbox::EFFECT_SPEED:
		//­»øÊÌíÞðÝè
		m_type = TYPE_SPEED;
		//­»øÊÌÔðÝè
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
		}
		break;

	case CHitbox::EFFECT_JUMP:
		//­»øÊÌíÞðÝè
		m_type = TYPE_JUMP;
		//­»øÊÌÔðÝè
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
		}
		break;

	case CHitbox::EFFECT_CHECKPOINT:

		//X|[n_ÌÝè
		m_Originpos = m_pHitbox->GetPos();
		//ÌÍª2ÈºÌâ·
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//qbg{bNXÌ|C^ªnullÅÍÈ©Á½ç
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//GtFNgðß·
		}
		break;

	default:
		break;
	}

	//³GÔ
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//JE^[ÌXV

		if (m_nInvincibleCnt <= 0)
		{//0ÉÈÁ½çA
			if (m_pHitbox != nullptr)
			{//qbg{bNXªnullÅÍÈ©Á½ç
				m_pHitbox->SetInvincibility(false);			//³GóÔªIíéæ¤ÉÝè·é
			}
		}
	}
}

//======================================================
//vC[Ì­»
//======================================================
void CPlayer::BuffPlayer(void)
{
	//vC[Ì^CvÉæÁÄ¾çêé­»
	if (m_type != TYPE_NONE && m_nBuffTime > 0)
	{
		BuffEffect(m_type);
		m_type = TYPE_NONE;
	}

	//­»øÊÌÔð¸­
	if (m_nBuffTime > 0)
	{
		m_nBuffTime--;
		//p[eBNÌ¶¬
		CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, m_pos, 30, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));
		
		if (m_bInside)
		{
			m_nBuffTime = 0;
		}
	}

	//­»øÊÌZbg
	if (m_nBuffTime == 0)
	{
		m_fAcceleration = 1.0f;
		m_fSlowFall = 1.0f;
	}
}

//======================================================
//­»øÊ
//======================================================
void CPlayer::BuffEffect(PLAYER_TYPE type)
{
	switch (type)
	{
	case CPlayer::TYPE_SPEED:
		//Á¬
		m_fAcceleration = 2.0f;
		//Ô
		m_nBuffTime = 300;
		break;

	case CPlayer::TYPE_JUMP:
		//º¬xáº
		m_fSlowFall = 4.0f;
		//Ô
		m_nBuffTime = 360;
		break;

	default:
		break;
	}
}

//======================================================
//Xe[WÆ½Á½
//======================================================
void CPlayer::CollisionStage(void)
{
	//bVÌîñæ¾
	std::vector<CMeshField*> pMesh = CStage::GetMesh();
	bool bCollision = true;
	D3DXVECTOR3 shadowPos = m_apModel[0]->GetShadowPos();
	//bVtB[hÌ nÌ»èð·é
	m_bCollisionField.resize(CStage::m_nMaxMesh);
	for (int nCnt = 0; nCnt < CStage::m_nMaxMesh; nCnt++)
	{
		if (pMesh[nCnt] != nullptr)
		{
			//bVÌ½è»è
			m_bCollisionField[nCnt] = pMesh[nCnt]->Collision(&m_pos, (m_size.y / 2.0f),true);
		}
		//nµÄ¢éÆ«ÍWvÅ«é
		if (m_bCollisionField[nCnt])
		{
			m_bJumping = true;
			m_fFriction = pMesh[nCnt]->GetFriction();

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{//fÌe
				m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, m_pos.y + 0.2f, m_pos.z));

				bCollision = pMesh[nCnt]->Collision(&D3DXVECTOR3(shadowPos.x, m_pos.y, shadowPos.z), 0.0f,false);

				if (!bCollision)
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

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{
				//bVtB[hÉGêÄ¢È¢Æ«ÌeÌÊuÌÝè
				bCollision = pMesh[nCnt]->Collision(&D3DXVECTOR3(shadowPos.x, pMesh[nCnt]->GetPos().y, shadowPos.z), 0.0f,false);

				if (!bCollision)
				{
					m_bShadow = false;
				}
				else
				{
					m_bShadow = true;
					return;
				}
			}
		}
	}

	//f¯Ìîñæ¾
	std::vector<CPlanet*> pPlanet = CStage::GetPlanet();	//»ê¼êÌf¯Ìîñ
	std::vector<float> fDif;								//»ê¼êÌf¯ÆÌ£
	std::vector<CPlanet*> pNearPlanet;						//Åàß¢f¯Ìîñ
	fDif.resize(CStage::m_nMaxPlanet);
	pNearPlanet.resize(CStage::m_nMaxPlanet);
	//f¯ÆvC[Ì£
	for (int nCnt = 0; nCnt < CStage::m_nMaxPlanet; nCnt++)
	{
		if (pPlanet[nCnt] != nullptr)
		{
			fDif[nCnt] = pPlanet[nCnt]->TargetDistance(this);
		}
	}

	//£Ìär
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
		//f¯Ì½è»è
		m_bCollisionPlanet = pNearPlanet[0]->CollisionSphere(&m_pos, &m_size);
		m_bInside = pNearPlanet[0]->SetGravity(&m_pos, &m_size, &m_move);

		if (m_bCollisionPlanet)
		{//f¯ÉæÁÄ¢éÆ«
			m_bJumping = true;
		}

		//================================
		//p¨í¹ñ]
		//================================

		//ñ]²ÌZo
		m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//²xNg
		m_norVec = m_pos - pNearPlanet[0]->GetPos();			//@üxNg
		D3DXVECTOR3 vecOver = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//ãûüxNg

		//@üxNgÌ³K»
		D3DXVec3Normalize(&m_norVec, &m_norVec);
		//OÏðÂ©ÁÄ²xNgðo·
		D3DXVec3Cross(&m_vecAxis, &vecOver, &m_norVec);
		//àÏÌZo
		float dot = D3DXVec3Dot(&vecOver, &m_norVec);
		//²ñ]ÉKvÈpxÌZo
		float angle = acosf(dot / (D3DXVec3Length(&vecOver) * D3DXVec3Length(&m_norVec)));

		//NH[^jIÌZo
		m_quat = D3DXQUATERNION(0, 0, 0, 1);
		D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, angle);
		D3DXMatrixRotationQuaternion(&m_mtxQuat, &m_quat);
	}
}

//======================================================
//üÍ
//======================================================
void CPlayer::Input(void)
{
	//JÌîñÌæ¾
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//vC[ÌÚ®
	if (CInputPad::GetJoypadPress(CInputPad::JOYKEY_A, 0))
	{//A{^ðµ±¯éÆ_bV
		m_fDash = 1.5f;
	}
	else
	{//£·Æßé
		m_fDash = 1.0f;
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_UP) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
	{//ªðµ½ç
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//¨ðµ½ç
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) == true || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//©ðµ½ç	
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x -= sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else
		{//ª
		 //isûüÌxNg
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x += sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		//[VÌÝè
		m_pMotion->SetPresentAnim(1);
	}
	//«ðµ½ç
	else if (CInputKeyboard::GetKeyboardPress(DIK_DOWN) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
	{
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//¨ðµ½ç
		 //isûüÌxNg
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//©ðµ½ç
		 //isûüÌxNg
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x -= sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else
		{//«
			if (!m_bInside)
			{//bVtB[hÉæÁÄ¢é
				m_move.x -= sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//ÌÍÍà
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		//[VÌÝè
		m_pMotion->SetPresentAnim(1);
	}
	//¨ðµ½ç
	else if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
	{
		if (!m_bInside)
		{//bVtB[hÉæÁÄ¢é
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//ÌÍÍà
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		//[VÌÝè
		m_pMotion->SetPresentAnim(1);
	}
	//©ðµ½ç
	else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
	{
		if (!m_bInside)
		{//bVtB[hÉæÁÄ¢é
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//ÌÍÍà
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		//[VÌÝè
		m_pMotion->SetPresentAnim(1);
	}

	//ÚIÌpxÌ³K»
	if (m_rotDest.y - GetRot().y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//¸
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	//»ÝÌpxÌ³K»
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//M~bNÌãÉæÁÄ¢½çWvÅ«éæ¤É·é
	for (int nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
	{
		if (!m_bJumping)
		{//WvµÄ¢È¯êÎAæÁÄ¢é©»è·é
			std::vector<CGimmick*> pGimmick = CStage::GetGimmick();
			std::vector<bool> bGimmick;
			bGimmick.resize(CStage::m_nMaxGimmick);

			for (nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
			{
				if (pGimmick[nCnt] != nullptr)
				{
					//ubNÌãÉnµÄ¢é©Ç¤©
					bGimmick[nCnt] = pGimmick[nCnt]->GetLanding();

					//nµÄ¢éÆ«ÍWvÅ«é
					if (bGimmick[nCnt])
					{
						m_move.y = 0.0f;
						m_pos.y = pGimmick[nCnt]->GetPos().y + (pGimmick[nCnt]->GetSize().y / 2.0f);
						m_bJumping = true;
					}
				}
			}
		}
	}

	//Wv
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
			{//WvÍª²®³êÄ¢½ç
				m_move.y = m_fJump * m_fBuffQuantity;
			}
			else
			{//WvÍÉÏ»ªÈ¯êÎ
				m_move.y = m_fJump;
			}
		}
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		//WvµÄ¢éóÔÉ·é
		m_bJumping = false;
	}

	//OñÊuðÛ¶
	m_posOld = m_pos;

	//Ú®ÊðÁZ
	m_pos += m_move;

	//Ú®ÊÌ¸
	m_move.x += (0.0f - m_move.x) * m_fFriction;
	m_move.z += (0.0f - m_move.z) * m_fFriction;

	if (m_bInside)
	{
		m_move.y += (0.0f - m_move.y) * m_fFriction;
	}
	else
	{//f¯ÌOÈç
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
	//fobN\¦
	CDebugProc::Print("»ÝÌpx%f\n", m_rot.y);
	CDebugProc::Print("»ÝÌÊu : %f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("JÌpx : %f\n", CameraRot.y);
	CDebugProc::Print("ÚIÌpx : %f\n", m_rotDest.y);
	CDebugProc::Print("Ú®Ê : %f %f %f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("NH[^jI %f %f %f %f\n", m_quat.x, m_quat.y, m_quat.z, m_quat.w);
	CDebugProc::Print("²xNg %f %f %f \n", m_vecAxis.x, m_vecAxis.y, m_vecAxis.z);
	CDebugProc::Print("­»øÊÌÔ %d \n", m_nBuffTime);
	if (m_bShadow)
	{
		CDebugProc::Print("eªoÄ¢é\n");
	}
	if (m_bJumping)
	{
		CDebugProc::Print("Wvoé\n");
	}
#endif // _DEBUG
}
//======================================================
//eÆM~bNÌ½è»è
//======================================================
void CPlayer::CollisionGimmick(void)
{
	//M~bNÌÍÍÉeÌÀWª éÈçM~bNÌãÉeðo·
	for (int nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
	{
		if (!m_bJumping)
		{//WvµÄ¢È¯êÎAæÁÄ¢é©»è·é
			std::vector<CGimmick*> pGimmick = CStage::GetGimmick();
			std::vector<bool> bGimmick;
			bGimmick.resize(CStage::m_nMaxGimmick);
			//eÌÀWÌæ¾
			D3DXVECTOR3 shadowPos = m_apModel[0]->GetShadowPos();

			for (nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
			{
				if (pGimmick[nCnt] != nullptr)
				{
					//M~bNÌÍÍÉeÌÀWª é©
					if (!m_bShadow)
					{//eªÁ¦Ä¢éÈç»è·é
						m_bShadow = pGimmick[nCnt]->Collision(shadowPos);
						if (m_bShadow)
						{
							for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
							{//fÌe
								m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, pGimmick[nCnt]->GetPos().y + (pGimmick[nCnt]->GetSize().y / 2.0f) + 0.2f, m_pos.z));
							}
						}
					}
				}
			}
		}
	}
}

//======================================================
//U
//======================================================
void CPlayer::Attack(void)
{
	//N[^CÌÝè
	m_fCT = 60.0f;

	//vC[Ì½è»èÉÁZ·éª
	D3DXVECTOR3 Attack_size = m_size + D3DXVECTOR3(7.0f, 0.0f, 7.0f);

	//qbg{bNXÌ¶¬
	m_pAttackHitbox = CCylinderHitbox::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), Attack_size, CHitbox::TYPE_OBSTACLE, 0, this, CHitbox::EFFECT_PUSH);
}

//======================================================
//fÌÇÝÝ
//======================================================
void CPlayer::LoadPlayer(void)
{
	int nNumParts;
	char aText[2000];						//¶ñði[·ézñ
	char FileName[MAX_MODEL][2000];			//2³zñ

	FILE *pFile; //t@C|C^ðé¾

	pFile = fopen("data/model/model.txt", "r");

	aText[0] = '\0';	//¶ñÈµ

	if (pFile != nullptr)
	{//t@CªJ¯½ê
	 //t@CÉüÍµ½f[^ð«o·
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//eLXgÌÅÌsðÇÝÞÜÅJèÔ·
			fgets(aText, MAX_WORD, pFile);        //ês²ÆÇÝÞ
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//eLXgÌÅãÌsðÇÝÞÜÅJèÔ·
			fscanf(pFile, "%s", &aText[0]);    //t@C©ç¶ñðÇÝÞ(ÇÝÝJn)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //ês²ÆÇÝÞ
				continue;
			}

			//t@Cl[ð¡ÂüÍ·é
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);					// = ðÇÝÞ
				fscanf(pFile, "%s", &FileName[m_nCntModel][0]);	//0ÔÚ©çÇÝÜêé

				//fp[cÌ¶¬
				m_apModel[m_nCntModel] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//fÌJEg
				m_nCntModel++;
			}

			if (strcmp(&aText[0], "CHARACTERSET") == 0)
			{
				while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //ês²ÆÇÝÞ
						continue;
					}

					if (strcmp(&aText[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = ðÇÝÞ
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "PARTSSET") == 0)
					{
						D3DXVECTOR3 pos, rot;
						int IndexParent = 0;	//eÌÔ
						int Ind = 0;

						while (strcmp(&aText[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //ês²ÆÇÝÞ
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

						//fp[cÌÇÝÝ
						m_apModel[Ind]->SetModel(&FileName[Ind][0]);
						m_apModel[Ind]->SetId(Ind);

						//fp[cÉîñªüÁÄ¢½ç
						if (m_apModel[Ind])
						{
							//fp[cÌÊuÆü«ÌÝè
							m_apModel[Ind]->SetRot(rot);
							m_apModel[Ind]->SetPos(pos);
						}

						//eÌÔª0æèº¾Á½ç
						if (IndexParent < 0)
						{
							//fp[cÌ}gbNXÌÝè
							m_apModel[Ind]->SetParent(nullptr);
						}
						//eÌÔªfp[cæè¬³©Á½ç
						else if (IndexParent < MAX_MODEL)
						{
							//fp[cÌ}gbNXÌÝè
							m_apModel[Ind]->SetParent(m_apModel[IndexParent]);
						}
					}
				}
			}
		}
		//t@CðÂ¶é
		fclose(pFile);
	}
}