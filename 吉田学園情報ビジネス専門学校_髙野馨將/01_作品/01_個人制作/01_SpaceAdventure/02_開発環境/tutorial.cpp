//=============================================================================
//
// ���U���g����
// Author:����]��
//
//=============================================================================
#include "application.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "tutorial.h"
#include "fade.h"
#include "sound.h"
#include "inputPad.h"

//======================================================
//�R���X�g���N�^
//======================================================
CTutorial::CTutorial() : CMode()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CTutorial::~CTutorial()
{
}

//======================================================
//����������
//======================================================
HRESULT CTutorial::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\controller.png",
		&m_pTexture[0]);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f)
		,D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f), PRIORITY_3);
	m_pObject2D->BindTexture(m_pTexture[0]);

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CTutorial::Uninit(void)
{
	CObject::Flag();
}

//======================================================
//�X�V����
//======================================================
void CTutorial::Update(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//���[�h�ݒ�
		CFade::SetFade(CApplication::MODE_TITLE);
	}
}

//======================================================
//��������
//======================================================
CTutorial *CTutorial::Create()
{
	//���I�m��
	CTutorial *pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		//������
		pTutorial->Init();
	}

	return pTutorial;
}
