//=============================================================================
//
// スコア処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "object2D.h"

//マクロ定義
#define MAX_SCORE    (8)        //スコアの桁数

//前方宣言
class CNumber;

//スコアクラス
class CScore : public CObject2D
{
public:
	explicit CScore(int nPriority = PRIORITY_4);					//コンストラクタ
	~CScore() override;			//デストラクタ

	HRESULT Init() override;    //初期化処理
	void Uninit() override;     //終了処理
	void Update() override;     //更新処理
	void Draw() override;       //描画処理
	static CScore *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);    //ポリゴンの生成

	void SetScore(int nScore);    //スコアの設定処理
	void AddScore(int nValue) { SetScore(m_nScore + nValue); }  //スコアの加算処理
	int GetScore() { return m_nScore; }							//スコア情報の取得処理

private:
	CNumber *m_apNumber[MAX_SCORE];		//Number型の配列
	int m_nScore;                       //スコアの値
};
#endif