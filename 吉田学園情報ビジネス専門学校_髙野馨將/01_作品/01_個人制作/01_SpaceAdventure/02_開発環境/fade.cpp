//=============================================================================
//
// �t�F�[�h����
// Author:����]��
//
//=============================================================================
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "renderer.h"

//�ÓI�����o�ϐ�
CApplication::MODE CFade::m_ModeNext = {};	//���̉��(���[�h)
CFade::FADE CFade::m_pFade = {};			//�t�F�[�h�̏��	
D3DXCOLOR CFade::m_Color = {};				//�J���[
//======================================================
//�R���X�g���N�^
//======================================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_MODE);
}

//======================================================
//�f�X�g���N�^
//======================================================
CFade::~CFade()
{
}

//======================================================
//����������
//======================================================
void CFade::Init(CApplication::MODE modeNext)
{
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),PRIORITY_5);

	//������
	m_pFade = FADE_IN;		//�t�F�[�h�C����Ԃ�
	m_ModeNext = modeNext;
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	m_pObject2D->SetPos(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f));
	m_pObject2D->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D->SetCol(m_Color);
	m_pObject2D->SetType(CObject::OBJTYPE_MODE);

	//���[�h�̐ݒ�
	CApplication::SetMode(m_ModeNext);
}

//======================================================
//�I������
//======================================================
void CFade::Uninit(void)
{
	//�������
	CObject::Flag();
}

//======================================================
//����������
//======================================================
void CFade::Update(void)
{
	if (m_pFade != FADE_NONE)
	{
		if (m_pFade == FADE_IN)
		{//�t�F�[�h�C�����
			m_Color.a -= 0.07f;		//�|���S���𓧖��ɂ��Ă���
			if (m_Color.a <= 0.0f)
			{
				m_Color.a = 0.0f;
				m_pFade = FADE_NONE;		//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_pFade == FADE_OUT)
		{ //�t�F�[�h�A�E�g���
			m_Color.a += 0.07f;		//�|���S����s�����ɂ��Ă���
			if (m_Color.a >= 1.0f)
			{
				m_Color.a = 1.0f;
				m_pFade = FADE_IN;		//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�(���̉�ʂɈڍs)
				CApplication::SetMode(m_ModeNext);
			}
		}
		m_pObject2D->SetCol(m_Color);
	}
}

//======================================================
//����������
//======================================================
void CFade::SetFade(CApplication::MODE modeNext)
{
	m_pFade = FADE_OUT;								//�t�F�[�h�A�E�g��Ԃ�
	m_ModeNext = modeNext;							//���̉��(���[�h)��ݒ�
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����|���S��(����)�ɂ��Ă���
}

//======================================================
//����������
//======================================================
CFade * CFade::Create(CApplication::MODE modeNext)
{
	//���I�m��
	CFade *pFade = new CFade;

	if (pFade != nullptr)
	{
		//������
		pFade->Init(modeNext);
	}

	return pFade;
}
