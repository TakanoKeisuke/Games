//=============================================================================
//
// デバック用フォント
// Author:髙野馨將
//
//=============================================================================
#include "debug.h"
#include "application.h"
#include <stdio.h>

//静的メンバ変数宣言
LPD3DXFONT CDebugProc::m_pFont;
char CDebugProc::m_aStr[1024];
//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CDebugProc::CDebugProc()
{

}

//======================================================
//デストラクタ
//======================================================
CDebugProc::~CDebugProc()
{
	
}

//======================================================
//初期化処理
//======================================================
void CDebugProc::Init(void)
{
	//初期化
	m_pFont = nullptr;
	m_aStr[0] = {};
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif
}

//======================================================
//終了処理
//======================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG
}

//======================================================
//読み込み処理
//======================================================
void CDebugProc::Print(const char *format, ...)
{
#ifdef _DEBUG
	//格納
	char aStr[1024] = {};

	va_list args;
	va_start(args, format);
	vsprintf(aStr,format,args);
	va_end(args);

	strcat(m_aStr, aStr);
#endif // _DEBUG
}

//======================================================
//描画処理
//======================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };

	if (m_pFont != nullptr)
	{
		// テキスト描画
		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		m_aStr[0] = '\0';
	}
}