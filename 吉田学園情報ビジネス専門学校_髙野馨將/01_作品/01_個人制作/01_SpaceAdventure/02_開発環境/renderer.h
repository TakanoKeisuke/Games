//=============================================================================
//
// �����_�����O
// Author:����]��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//�����_�����O�N���X
class CRenderer
{
public:
	CRenderer();													//�R���X�g���N�^
	~CRenderer();													//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);							//������
	void Uninit(void);												//�I��
	void Update(void);												//�X�V
	void Draw(void);												//�`��
	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}		//Device�̎擾
	//�ÓI�����o�ϐ�
	static const int SCREEN_WIDTH = 1280;							// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;							// �X�N���[���̍���

private:
	void DrawFPS();								//FPS�̕`��

	//�����o�ϐ�
	LPDIRECT3D9 m_pD3D;							// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Device�I�u�W�F�N�g
	LPD3DXFONT m_pFont;							//�t�H���g
};
#endif