//=============================================================================
//
// C
// Author:ûüì]
//
//=============================================================================

//=============================================================================
// Cu[N
//=============================================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//=============================================================================
// CN[h
//=============================================================================
#include "application.h"
//=============================================================================
// èè`
//=============================================================================
namespace
{
	// EChEÌNX¼
	LPCTSTR CLASS_NAME = _T("AppClass");
	// EChEÌLvV¼
	LPCTSTR WINDOW_NAME = _T("Space Adventure");

	const int SCREEN_WIDTH = 1280;							// XN[Ì
	const int SCREEN_HEIGHT = 720;							// XN[Ì³
}

//=============================================================================
// O[oÏ
//=============================================================================
#ifdef _DEBUG
// tHg
LPD3DXFONT g_pFont = nullptr;
#endif // _DEBUG

#ifdef _DEBUG
// FPSJE^
int g_nCountFPS;
#endif // _DEBUG

//=============================================================================
// vg^Cvé¾
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// CÖ
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// EBhENXÌo^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// wèµ½NCAgÌæðmÛ·é½ßÉKvÈEBhEÀWðvZ
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// EBhEÌì¬
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//®ImÛ
	CApplication *pApllication = new CApplication;

	// ú»
	if (FAILED(pApllication->Init(hInstance,hWnd, TRUE)))
	{//æ2øÍFALSE¾Á½çAtXN[
		return -1;
	}

	// ªð\ðÝè
	timeBeginPeriod(1);

	// t[JEgú»
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

	// EChEÌ\¦
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// bZ[W[v
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()ªÄÎê½ç[vI¹
				break;
			}
			else
			{
				// bZ[WÌ|óÆfBXpb`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// »ÝÌÔðæ¾
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5b²ÆÉÀs
			 // FPSðZo
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// »ÝÌÔðÛ¶
				dwFrameCount = 0;
			}
#endif // _DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 1/60boß
			  // »ÝÌÔðÛ¶
				dwExecLastTime = dwCurrentTime;

				if (pApllication != nullptr)
				{
					// XV
					pApllication->Update();

					// `æ
					pApllication->Draw();
				}
#ifdef _DEBUG
				dwFrameCount++;
#endif // _DEBUG
			}
		}
	}
	
	if (pApllication != nullptr)
	{
		//I¹
		pApllication->Uninit();
		//Ìðú
		delete pApllication;
		//ú»
		pApllication = nullptr;
	}

	// EBhENXÌo^ðð
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ªð\ðß·
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// EChEvV[W
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]L[ª³ê½
						// EBhEðjü
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
//=============================================================================
// FPSæ¾
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif // _DEBUG