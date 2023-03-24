//======================================================
//
//timer.cpp
//Author:����]��
//
//======================================================
#include "timer.h"
#include "number.h"
#include "game.h"
#include "application.h"
#include "fade.h"

//======================================================
//�R���X�g���N�^
//======================================================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CTimer::~CTimer()
{//���������Ȃ�
}

//======================================================
//����������
//======================================================
HRESULT CTimer::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		//����
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((GetSize().x *nCnt) + (GetPos().x - GetSize().x * MAX_TIMER + GetSize().x / 2.0f)
			, GetPos().y
			, 0.0f)
			, D3DXVECTOR2(GetSize().x, GetSize().y));
	}

	//������
	m_nTimer = 0;

	//�^�C�}�[�̐ݒ�
	SetTimer(200);

	return S_OK;
}

//======================================================
//�X�V����
//======================================================
void CTimer::Uninit()
{
	//�i���o�[�̔j������
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
		}
	}

	//�������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CTimer::Update()
{
	m_nCntTimer++;
	//1�t���[�����ƂɃ^�C�}�[��1�����Z����
	if (m_nCntTimer >= 60)
	{
		m_nCntTimer = 0;
		SubTimer(1);
	}

	//�^�C�}�[��0�ɂȂ�����I��
	if (m_nTimer < 0)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			//���[�h�ݒ�
			CFade::SetFade(CApplication::MODE_RESULT);
			Uninit();
			return;
		}
	}
}

//======================================================
//�X�V����
//======================================================
void CTimer::Draw()
{
}

//======================================================
//��������
//======================================================
CTimer *CTimer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//���I�m��
	CTimer *pTimer = new CTimer;

	if (pTimer != nullptr)
	{
		//������
		pTimer->SetPos(pos);
		pTimer->SetSize(size);
		pTimer->Init();
	}

	return pTimer;
}

//====================================
//���Ԃ̐ݒ菈��
//====================================
void CTimer::SetTimer(int nTimer)
{
	int aPosTexU[MAX_TIMER];	//�e���̐������i�[

	m_nTimer = nTimer;
	aPosTexU[0] = m_nTimer % 1000 / 100;
	aPosTexU[1] = m_nTimer % 100 / 10;
	aPosTexU[2] = m_nTimer % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < MAX_TIMER; nCntScore++)
	{
		m_apNumber[nCntScore]->SetTex(10.0f, (float)aPosTexU[nCntScore]);
	}
}