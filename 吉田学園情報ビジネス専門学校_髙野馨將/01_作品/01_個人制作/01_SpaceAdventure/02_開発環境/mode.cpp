//=============================================================================
//
// ���[�h����
// Author:����]��
//
//=============================================================================
#include "game.h"
#include "result.h"
#include "title.h"
#include "ranking.h"
#include "mode.h"

//�ÓI�����o�ϐ��錾
CTitle *CMode::m_pTitle = nullptr;
CTutorial *CMode::m_pTutorial = nullptr;
CGame *CMode::m_pGame = nullptr;
CRanking *CMode::m_pRanking = nullptr;
CResult *CMode::m_pResult = nullptr;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMode::CMode() : CObject(PRIORITY_3)
{
	SetType(OBJTYPE_MODE);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMode::~CMode()
{
}