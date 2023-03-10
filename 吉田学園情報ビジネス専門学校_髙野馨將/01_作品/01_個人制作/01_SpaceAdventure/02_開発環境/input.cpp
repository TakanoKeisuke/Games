//=============================================================================
//
// input.cpp
// Author:ϋόμ] Ricci Alex
//
//=============================================================================

//CN[ht@C
#include "input.h"

//ΓIo[ΟΜιΎ
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//RXgN^
CInput::CInput()
{
	//o[ΟπNA·ι
	m_pDevice = nullptr;
}

//fXgN^
CInput::~CInput()
{

}

//ϊ»
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd, GUID guid)
{
	//DirectInputIuWFNgΜΆ¬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//όΝfoCX(L[{[h)ΜΆ¬
	if (FAILED(m_pInput->CreateDevice(guid, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//IΉ
void CInput::Uninit(void)
{
	//CvbgfoCXΜjό
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

	//foCXΜjό
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

//CvbgfoCXΜζΎ
LPDIRECTINPUTDEVICE8 CInput::GetInputDevice(void)
{
	return m_pDevice;
}