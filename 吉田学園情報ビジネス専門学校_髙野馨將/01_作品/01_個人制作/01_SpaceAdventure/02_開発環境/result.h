//=============================================================================
//
// リザルト処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "mode.h"

//前方宣言
class CObject2D;

//マクロ定義
#define MAX_RESULT		(3)			//ポリゴンの最大数

//リザルトクラス
class CResult : public CMode
{
public:
	CResult();			//コンストラクタ
	~CResult();			//デストラクタ
	//メンバ関数
	HRESULT Init();			//初期化
	void Uninit();			//終了
	void Update();			//更新
	//静的メンバ関数
	static CResult *Create();	//ポリゴンの生成
	static void SetClear(bool clear) { b_clear = clear; }
	static bool GetClear() { return b_clear; }

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT];		//テクスチャへのポインタ
	CObject2D *m_pObject2D;
	static bool b_clear;							//クリアしたか

};
#endif