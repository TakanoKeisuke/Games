//=============================================================================
//
// モード処理
// Author:髙野馨將
//
//=============================================================================
#include "game.h"
#include "result.h"
#include "title.h"
#include "ranking.h"
#include "mode.h"

//静的メンバ変数宣言
CTitle *CMode::m_pTitle = nullptr;
CTutorial *CMode::m_pTutorial = nullptr;
CGame *CMode::m_pGame = nullptr;
CRanking *CMode::m_pRanking = nullptr;
CResult *CMode::m_pResult = nullptr;
//=============================================================================
//コンストラクタ
//=============================================================================
CMode::CMode() : CObject(PRIORITY_3)
{
	SetType(OBJTYPE_MODE);
}

//=============================================================================
//デストラクタ
//=============================================================================
CMode::~CMode()
{
}