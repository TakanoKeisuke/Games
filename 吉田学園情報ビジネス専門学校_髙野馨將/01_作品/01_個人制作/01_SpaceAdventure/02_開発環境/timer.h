//=============================================================================
//
// timer.h
// Author:髙野馨將
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "object2D.h"

//前方宣言
class CNumber;

//タイマークラス
class CTimer : public CObject2D
{
public:
	const static int MAX_TIMER = 3;

	explicit CTimer(int nPriority = PRIORITY_4);		//オーバーライドされたコンストラクタ
	~CTimer() override;									//デストラクタ

	//メンバ関数
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw(void) override;							//描画

	void SetTimer(int nTimer);									//タイマーの設定
	void SubTimer(int nValue) { SetTimer(m_nTimer - nValue); }  //タイマーの加算処理
	int GetTimer(void) { return m_nTimer; }						//タイマーの取得
	//静的メンバ関数
	static CTimer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//生成

private:
	//メンバ変数
	CNumber *m_apNumber[MAX_TIMER];				//Number型の配列
	int m_nTimer;								//タイマーの値
	int m_nCntTimer;							//タイマーのカウント
};

#endif