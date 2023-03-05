//=============================================================================
//
// スコア処理
// Author:髙野馨將
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "score.h"
#include "ranking.h"
#include "result.h"
#include "number.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CObject2D(nPriority)
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{//何も書かない
}

//=============================================================================
//スコアの初期化処理
//=============================================================================
HRESULT CScore::Init()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//生成
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((GetSize().x *nCnt) + (GetPos().x - GetSize().x * MAX_SCORE + GetSize().x / 2.0f)
			, GetPos().y
			, 0.0f)
			, D3DXVECTOR2(GetSize().x, GetSize().y));
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
//スコアの終了処理
//=============================================================================
void CScore::Uninit()
{
	//ナンバーの破棄
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
		}
	}

	//破棄処理
	Flag();
}

//=============================================================================
//スコアの更新処理
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
//スコアの描画処理
//=============================================================================
void CScore::Draw()
{
}

//=============================================================================
//スコアの生成処理
//=============================================================================
CScore *CScore::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//動的確保
	CScore *pScore;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		//初期化
		pScore->SetPos(pos);
		pScore->SetSize(size);
		pScore->Init();
	}

	return pScore;
}

//=============================================================================
//スコアの設定処理
//=============================================================================
void CScore::SetScore(int nScore)
{
	int aPosTexU[8];	//各桁の数字を格納

	m_nScore = nScore;

	aPosTexU[0] = m_nScore % 100000000 / 10000000;
	aPosTexU[1] = m_nScore % 10000000 / 1000000;
	aPosTexU[2] = m_nScore % 1000000 / 100000;
	aPosTexU[3] = m_nScore % 100000 / 10000;
	aPosTexU[4] = m_nScore % 10000 / 1000;
	aPosTexU[5] = m_nScore % 1000 / 100;
	aPosTexU[6] = m_nScore % 100 / 10;
	aPosTexU[7] = m_nScore % 10 / 1;

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetTex(10.0f, (float)aPosTexU[nCntScore]);
	}

	CRanking::GetRanking(m_nScore);
}