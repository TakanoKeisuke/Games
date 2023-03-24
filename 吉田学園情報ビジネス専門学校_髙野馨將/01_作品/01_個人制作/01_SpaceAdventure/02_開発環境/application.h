//=============================================================================
//
// アプリケーション(マネージャー)
// Author:髙野馨將
//
//=============================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "renderer.h"
#include "input_keyboard.h"
#include "camera.h"
#include "light.h"

//#include "score.h"
//#include "combo.h"

//前方宣言
class CSound;
class CDebugProc;
class CInputPad;

//アプリケーション管理クラス
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル
		MODE_TUTORIAL,		//チュートリアル
		MODE_GAME,			//ゲーム
		MODE_RESULT,		//リザルト
		MODE_RANKING,		//ランキング
		MODE_MAX
	};

	CApplication();										//コンストラクタ
	~CApplication();									//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);  //初期化
	void Uninit();		//終了
	void Update();		//更新
	void Draw();		//描画

	//静的メンバ関数
	static void SetMode(MODE mode);
	static MODE GetMode() { return m_mode; }
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CCamera *GetCamera() { return m_pCamera; }
	static CSound *GetSound() { return m_pSound; }
	static CLight *GetLight() { return m_pLight; }
	static CInputPad* GetPad(void) { return m_pPad; }

private:
	//静的メンバ変数
	static CSound* m_pSound;
	static CLight *m_pLight;
	static CRenderer *m_pRenderer;
	static CCamera *m_pCamera;
	static CDebugProc *m_pDebug;
	static CObject *m_pMode;
	static CInput* m_pInput[2];
	static CInputPad *m_pPad;

	static MODE m_mode;
};
#endif;