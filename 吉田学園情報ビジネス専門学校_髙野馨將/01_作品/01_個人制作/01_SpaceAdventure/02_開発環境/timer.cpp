//======================================================
//
//timer.cpp
//Author:髙野馨將
//
//======================================================
#include "timer.h"
#include "number.h"
#include "game.h"
#include "application.h"
#include "fade.h"

//======================================================
//コンストラクタ
//======================================================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CTimer::~CTimer()
{//何も書かない
}

//======================================================
//初期化処理
//======================================================
HRESULT CTimer::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((GetSize().x *nCnt) + (GetPos().x - GetSize().x * MAX_TIMER + GetSize().x / 2.0f)
			, GetPos().y
			, 0.0f)
			, D3DXVECTOR2(GetSize().x, GetSize().y));
	}

	//初期化
	m_nTimer = 0;

	//タイマーの設定
	SetTimer(200);

	return S_OK;
}

//======================================================
//更新処理
//======================================================
void CTimer::Uninit()
{
	//ナンバーの破棄処理
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
		}
	}

	//解放処理
	Flag();
}

//======================================================
//更新処理
//======================================================
void CTimer::Update()
{
	m_nCntTimer++;
	//1フレームごとにタイマーを1ずつ減算する
	if (m_nCntTimer >= 60)
	{
		m_nCntTimer = 0;
		SubTimer(1);
	}

	//タイマーが0になったら終了
	if (m_nTimer < 0)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			//モード設定
			CFade::SetFade(CApplication::MODE_RESULT);
			Uninit();
			return;
		}
	}
}

//======================================================
//更新処理
//======================================================
void CTimer::Draw()
{
}

//======================================================
//生成処理
//======================================================
CTimer *CTimer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//動的確保
	CTimer *pTimer = new CTimer;

	if (pTimer != nullptr)
	{
		//初期化
		pTimer->SetPos(pos);
		pTimer->SetSize(size);
		pTimer->Init();
	}

	return pTimer;
}

//====================================
//時間の設定処理
//====================================
void CTimer::SetTimer(int nTimer)
{
	int aPosTexU[MAX_TIMER];	//各桁の数字を格納

	m_nTimer = nTimer;
	aPosTexU[0] = m_nTimer % 1000 / 100;
	aPosTexU[1] = m_nTimer % 100 / 10;
	aPosTexU[2] = m_nTimer % 10 / 1;

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_TIMER; nCntScore++)
	{
		m_apNumber[nCntScore]->SetTex(10.0f, (float)aPosTexU[nCntScore]);
	}
}