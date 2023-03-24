//=============================================================================
//
// ランキング処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _RANKING_H_                        //このマクロ定義がされてなかったら
#define _RANKING_H_                        //二重インクルード防止のマクロ定義

#include "mode.h"

//前方宣言
class CObject2D;
class CFade;
class CNumber;

//マクロ定義
#define MAX_RANKING			(8)        //ランキングの桁数
#define MAX_RANKING_RANK    (5)        //ランキングの順位分
#define MAX_TEXTURE			(4)        //テクスチャの数

//ランキングクラス
class CRanking : public CMode
{
public:
	CRanking();
	~CRanking();

	//プロトタイプ宣言
	HRESULT Init();
	void Uninit();
	void Update();
	void Load();
	void Save();
	void SetRankingScore();
	static void GetRanking(int nRanking) { m_nRanking = nRanking; }
	static CRanking *Create();    //ランキングの生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE] = {};            //テクスチャへのポインタ
	CObject2D *m_pObject2D[3];                                  //Object2Dのポインタ変数
	CFade *m_pFade;
	static CNumber *m_apNumber[MAX_RANKING_RANK][MAX_RANKING];    //Number型の配列
	static int m_nRanking;
	static int m_nData[MAX_RANKING_RANK];
	bool m_bYourRank[MAX_RANKING_RANK];
	bool m_bColorChange;
};

#endif;