//=============================================================================
//
// デバック用フォント
// Author:髙野馨將
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "renderer.h"

//デバッククラス
class CDebugProc
{
public:
	CDebugProc();							//オーバーライドされたコンストラクタ
	~CDebugProc();							//デストラクタ

	//メンバ関数
	 void Init(void); //初期化
	 void Uninit(void); //更新

	 static void Print(const char *format, ...);
	 static void Draw(void);

private:
	//静的メンバ変数
	static LPD3DXFONT m_pFont;
	static char m_aStr[1024];
};

#endif