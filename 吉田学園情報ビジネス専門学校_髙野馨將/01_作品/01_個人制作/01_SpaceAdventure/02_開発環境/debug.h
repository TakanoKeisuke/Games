//=============================================================================
//
// �f�o�b�N�p�t�H���g
// Author:����]��
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "renderer.h"

//�f�o�b�N�N���X
class CDebugProc
{
public:
	CDebugProc();							//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CDebugProc();							//�f�X�g���N�^

	//�����o�֐�
	 void Init(void); //������
	 void Uninit(void); //�X�V

	 static void Print(const char *format, ...);
	 static void Draw(void);

private:
	//�ÓI�����o�ϐ�
	static LPD3DXFONT m_pFont;
	static char m_aStr[1024];
};

#endif