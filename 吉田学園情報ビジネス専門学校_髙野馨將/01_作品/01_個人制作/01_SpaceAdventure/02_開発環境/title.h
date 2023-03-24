//=============================================================================
//
// タイトル処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "mode.h"

//前方宣言
class CObject2D;

//マクロ定義
#define MAX_TITLE		(4)			//ポリゴンの最大数

//タイトルクラス
class CTitle : public CMode
{
public:
	CTitle();			//コンストラクタ
	~CTitle();			//デストラクタ
	//メンバ関数
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画
	//静的メンバ関数
	static CTitle *Create();			//タイトルの生成

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE];		//テクスチャへのポインタ
	CObject2D *m_pObject2D[MAX_TITLE];				//2Dポリゴンの情報
	int m_nCounter;									//点滅時間
	int m_nSelect;									//選んでいる番号
};

#endif