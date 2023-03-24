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
#include "result.h"
#include "fade.h"
//#include "sound.h"
#include "game.h"

//�ÓI�����o�ϐ��錾
bool CResult::b_clear;
//======================================================
//�R���X�g���N�^
//======================================================
CResult::CResult() : CMode()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CResult::~CResult()
{
}

//======================================================
//����������
//======================================================
HRESULT CResult::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sea.png",
		&m_pTexture[0]);

	//PlaySound(SOUND_LABEL_BGM001);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f), PRIORITY_3);
	m_pObject2D->BindTexture(m_pTexture[0]);

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CResult::Uninit(void)
{
	//StopSound();
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	CObject::Flag();
}

//======================================================
//�X�V����
//======================================================
void CResult::Update(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (CInputKeyboard::GetKeyboardPress(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//���[�h�ݒ�
		CFade::SetFade(CApplication::MODE_RANKING);
	}
}

//======================================================
//��������
//======================================================
CResult * CResult::Create()
{
	//���I�m��
	CResult *pResult = new CResult;

	if (pResult != nullptr)
	{
		//������
		pResult->Init();
	}

	return pResult;
}
