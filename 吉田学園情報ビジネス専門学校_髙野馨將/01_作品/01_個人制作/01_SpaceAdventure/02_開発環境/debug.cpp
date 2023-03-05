//=============================================================================
//
// �f�o�b�N�p�t�H���g
// Author:����]��
//
//=============================================================================
#include "debug.h"
#include "application.h"
#include <stdio.h>

//�ÓI�����o�ϐ��錾
LPD3DXFONT CDebugProc::m_pFont;
char CDebugProc::m_aStr[1024];
//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CDebugProc::CDebugProc()
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CDebugProc::~CDebugProc()
{
	
}

//======================================================
//����������
//======================================================
void CDebugProc::Init(void)
{
	//������
	m_pFont = nullptr;
	m_aStr[0] = {};
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif
}

//======================================================
//�I������
//======================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG
}

//======================================================
//�ǂݍ��ݏ���
//======================================================
void CDebugProc::Print(const char *format, ...)
{
#ifdef _DEBUG
	//�i�[
	char aStr[1024] = {};

	va_list args;
	va_start(args, format);
	vsprintf(aStr,format,args);
	va_end(args);

	strcat(m_aStr, aStr);
#endif // _DEBUG
}

//======================================================
//�`�揈��
//======================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };

	if (m_pFont != nullptr)
	{
		// �e�L�X�g�`��
		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		m_aStr[0] = '\0';
	}
}