//=============================================================================
//
//�A�v���P�[�V����(�}�l�[�W���[)
//Author:����]��
//
//=============================================================================
#include "application.h"
#include "object3d.h"
#include "objectX.h"
#include "player.h"
#include "billboard.h"
#include "debug.h"
#include "object2D.h"
#include "model.h"
#include "meshfield.h"
#include "sphere.h"
#include "result.h"
#include "title.h"
#include "game.h"
#include "mode.h"
#include "fade.h"
#include "motion.h"
#include "light.h"
#include "sound.h"
#include "inputPad.h"
#include "tutorial.h"
#include "ranking.h"

//�ÓI�����o�ϐ��錾
CRenderer *CApplication::m_pRenderer = nullptr;
CCamera *CApplication::m_pCamera = nullptr;
CLight *CApplication::m_pLight = nullptr;
CDebugProc *CApplication::m_pDebug = nullptr;
CObject *CApplication::m_pMode = nullptr;
CSound *CApplication::m_pSound = nullptr;
CInput *CApplication::m_pInput[2] = {};
CInputPad* CApplication::m_pPad = nullptr;
CApplication::MODE CApplication::m_mode = CApplication::MODE_TITLE;
//======================================================
//�R���X�g���N�^
//======================================================
CApplication::CApplication()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CApplication::~CApplication()
{//���������Ȃ�
}

//======================================================
//����������
//======================================================
HRESULT CApplication::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	//�L�[�{�[�h�C���X�^���X�̐������� 
	m_pInput[0] = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//���I�m��
	m_pRenderer = new CRenderer;

	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏�����
		m_pRenderer->Init(hWnd, bWindow);
	}

	//���I�m��
	m_pLight = new CLight;

	if (m_pLight != nullptr)
	{
		//���C�g�̏�����
		m_pLight->Init();
	}

	//���I�m��
	m_pCamera = new CCamera;

	if (m_pCamera != nullptr)
	{
		//�J�����̏�����
		m_pCamera->Init();
	}

	//���I�m��
	m_pDebug = new CDebugProc;

	if (m_pDebug != nullptr)
	{
		//�f�o�b�N�\���̏�����
		m_pDebug->Init();
	}

	//���I�m��
	m_pPad = new CInputPad;

	if (m_pPad != nullptr)
	{//�p�b�h�̏���������
		m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	}

	//���[�V�����̃t�@�C���ǂݍ���
	CMotion::LoadFile();

	//�T�E���h�̐���
	m_pSound = CSound::Create(hWnd);

	//���[�h�̐ݒ�
	CFade::Create(m_mode);

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CApplication::Uninit()
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			//�C���v�b�g�̏I������
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pPad != nullptr)
	{//�p�b�h�̔j������
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		//�J�����̏I������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pLight != nullptr)
	{
		//���C�g�̏I������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//�T�E���h�̔j������
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();				//�I������
		delete m_pSound;				//�j������
		m_pSound = nullptr;				//null�ɂ���
	}

	if (m_pDebug != nullptr)
	{
		//�f�o�b�N�\���̏I������
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//object�̑S�J��
	CObject::ReleaseAll();
}

//======================================================
//�X�V����
//======================================================
void CApplication::Update()
{
	//���͏����̍X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}
	//�p�b�h�̍X�V����
	if (m_pPad != nullptr)
	{
		m_pPad->Update();
	}
	//�����_���[�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	//�J�����̍X�V����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	//���C�g�̍X�V����
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
}

//======================================================
//�`�揈��
//======================================================
void CApplication::Draw()
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//======================================================
//���[�h�ݒ�
//======================================================
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	//���[�h�̉��
	CObject::ReleaseMode();

	m_mode = mode;

	if (m_pSound != nullptr && m_mode != MODE_TUTORIAL)
	{// �g�p���̃T�E���h��~
		m_pSound->Stop();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;

	case MODE_GAME:
		m_pMode = CGame::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		break;

	//case MODE_RESULT:
	//	m_pMode = CResult::Create();	
	//	break;

	case MODE_RESULT:
		m_pMode = CRanking::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_RESULT);
		break;

	default:
		break;
	}
}