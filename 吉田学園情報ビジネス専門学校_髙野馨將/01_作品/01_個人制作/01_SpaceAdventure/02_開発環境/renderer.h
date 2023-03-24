//=============================================================================
//
// レンダリング
// Author:髙野馨將
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//レンダリングクラス
class CRenderer
{
public:
	CRenderer();													//コンストラクタ
	~CRenderer();													//デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWnd, BOOL bWindow);							//初期化
	void Uninit(void);												//終了
	void Update(void);												//更新
	void Draw(void);												//描画
	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}		//Deviceの取得
	//静的メンバ変数
	static const int SCREEN_WIDTH = 1280;							// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;							// スクリーンの高さ

private:
	void DrawFPS();								//FPSの描画

	//メンバ変数
	LPDIRECT3D9 m_pD3D;							// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Deviceオブジェクト
	LPD3DXFONT m_pFont;							//フォント
};
#endif