//=============================================================================
//
// タイトル処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "mode.h"

//前方宣言
class CObject2D;

//マクロ定義
#define MAX_TUTORIAL		(1)			//ポリゴンの最大数

//チュートリアルクラス
class CTutorial : public CMode
{
public:
	CTutorial();			//コンストラクタ
	~CTutorial();			//デストラクタ
						//メンバ関数
	HRESULT Init();			//初期化
	void Uninit();				//終了
	void Update();				//更新
	//静的メンバ関数
	static CTutorial *Create();	//タイトルの生成

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIAL];		//テクスチャへのポインタ
	CObject2D *m_pObject2D;
};

#endif