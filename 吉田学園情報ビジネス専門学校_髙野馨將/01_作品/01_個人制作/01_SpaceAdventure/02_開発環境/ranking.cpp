//=============================================================================
//
// ランキング処理
// Author:髙野馨將
//
//=============================================================================
#include <stdio.h>
#include "application.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "ranking.h"
#include "fade.h"
#include "inputPad.h"
#include "sound.h"
#include "number.h"

//静的メンバ変数宣言
CNumber *CRanking::m_apNumber[MAX_RANKING_RANK][MAX_RANKING];
int CRanking::m_nData[MAX_RANKING_RANK];
int CRanking::m_nRanking;
//======================================================
//コンストラクタ
//======================================================
CRanking::CRanking() : CMode()
{
}

//======================================================
//デストラクタ
//======================================================
CRanking::~CRanking()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CRanking::Init(void)
{
	//初期化
	m_bYourRank[MAX_RANKING_RANK] = {};
	m_bColorChange = false;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.jpg",
		&m_pTexture[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rankinglogo.png",
		&m_pTexture[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&m_pTexture[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture[3]);

	//ポリゴンの生成
	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);
	//ポリゴンの生成
	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(600.0f, 80.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[1]->SetSize(D3DXVECTOR3(480.0f, 180.0f, 0.0f));
	m_pObject2D[1]->BindTexture(m_pTexture[1]);
	//ポリゴンの生成
	m_pObject2D[2] = CObject2D::Create(D3DXVECTOR3(200.0f, 420.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[2]->SetSize(D3DXVECTOR3(200.0f, 500.0f, 0.0f));
	m_pObject2D[2]->BindTexture(m_pTexture[2]);

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking] = CNumber::Create(D3DXVECTOR3(60.0f * nCntRanking + 400.0f, 100.0f * nCnt + 220.0f, 0.0f), D3DXVECTOR2(30.0f, 60.0f));
			m_apNumber[nCnt][nCntRanking]->BindTexture(m_pTexture[3]);
		}
	}

	//ファイル読み込み処理
	Load();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CRanking::Uninit(void)
{
	//破棄処理
	Flag();
}

//======================================================
//更新処理
//======================================================
void CRanking::Update(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (CInputKeyboard::GetKeyboardPress(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		Save();
		CFade::SetFade(CApplication::MODE_TITLE);
	}

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			if (m_bYourRank[nCnt])
			{//一度も色が変わってなかったら色を変える
				m_apNumber[nCnt][nCntRanking]->SetCol(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
				m_bColorChange = true;
			}
		}
		if (m_bColorChange)
		{//色が変わったら通らなくする
			return;
		}
	}
}

//============================
//ファイルに書き出す
//============================
void CRanking::Save()
{
	FILE*pFile;		//ファイルポインタ宣言

	//ファイルを開く
	pFile = fopen("data/Save/ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
		{
			//ファイルに数値を書き出す
			fprintf(pFile, "%d\n", m_nData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//============================
//ファイルから読み込む
//============================
void CRanking::Load()
{
	FILE*pFile;		//ファイルポインタ宣言

	//ファイルを開く
	pFile = fopen("data/Save/ranking.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
		{
			//ファイルから数値を読み込む
			fscanf(pFile, "%d\n", &m_nData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//====================================
//スコアの設定処理
//====================================
void CRanking::SetRankingScore()
{
	int aPosTexU[MAX_RANKING_RANK][MAX_RANKING];	//各桁の数字を格納

	//新しいスコアと古いスコアの比較
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK + 1; nCnt++)
	{
		if (m_nRanking > m_nData[4])
		{
			m_nData[4] = m_nRanking;
		}
	}
	//バブルソート
	for (int nCount = 0; nCount < MAX_RANKING_RANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKING_RANK; nCount2++)
		{
			if (m_nData[nCount] < m_nData[nCount2])
			{
				int nMin = m_nData[nCount];
				m_nData[nCount] = m_nData[nCount2];
				m_nData[nCount2] = nMin;
				m_bYourRank[nCount] = true;
			}
		}
	}
	for (int nCntScore = 0; nCntScore < MAX_RANKING_RANK; nCntScore++)
	{
		aPosTexU[nCntScore][0] = m_nData[nCntScore] % 100000000 / 1000000;
		aPosTexU[nCntScore][1] = m_nData[nCntScore] % 10000000 / 1000000;
		aPosTexU[nCntScore][2] = m_nData[nCntScore] % 1000000 / 100000;
		aPosTexU[nCntScore][3] = m_nData[nCntScore] % 100000 / 10000;
		aPosTexU[nCntScore][4] = m_nData[nCntScore] % 10000 / 1000;
		aPosTexU[nCntScore][5] = m_nData[nCntScore] % 1000 / 100;
		aPosTexU[nCntScore][6] = m_nData[nCntScore] % 100 / 10;
		aPosTexU[nCntScore][7] = m_nData[nCntScore] % 10 / 1;
	}

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking]->SetTex(10.0f, (float)aPosTexU[nCnt][nCntRanking]);
		}
	}
}

//======================================================
//生成処理
//======================================================
CRanking *CRanking::Create()
{
	//動的確保
	CRanking *pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		//初期化
		pRanking->Init();
		pRanking->SetRankingScore();
	}

	return pRanking;
}