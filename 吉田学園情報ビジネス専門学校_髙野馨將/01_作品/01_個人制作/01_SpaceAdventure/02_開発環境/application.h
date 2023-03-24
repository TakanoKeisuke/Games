//=============================================================================
//
// �A�v���P�[�V����(�}�l�[�W���[)
// Author:����]��
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

//�O���錾
class CSound;
class CDebugProc;
class CInputPad;

//�A�v���P�[�V�����Ǘ��N���X
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_TUTORIAL,		//�`���[�g���A��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_RANKING,		//�����L���O
		MODE_MAX
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);  //������
	void Uninit();		//�I��
	void Update();		//�X�V
	void Draw();		//�`��

	//�ÓI�����o�֐�
	static void SetMode(MODE mode);
	static MODE GetMode() { return m_mode; }
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CCamera *GetCamera() { return m_pCamera; }
	static CSound *GetSound() { return m_pSound; }
	static CLight *GetLight() { return m_pLight; }
	static CInputPad* GetPad(void) { return m_pPad; }

private:
	//�ÓI�����o�ϐ�
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