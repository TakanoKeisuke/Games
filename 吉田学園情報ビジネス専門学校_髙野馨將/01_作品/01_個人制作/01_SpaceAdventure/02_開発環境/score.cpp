//=============================================================================
//
// �X�R�A����
// Author:����]��
//
//=============================================================================
#include "application.h"
#include "renderer.h"
#include "score.h"
#include "ranking.h"
#include "result.h"
#include "number.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CObject2D(nPriority)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{//���������Ȃ�
}

//=============================================================================
//�X�R�A�̏���������
//=============================================================================
HRESULT CScore::Init()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//����
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((GetSize().x *nCnt) + (GetPos().x - GetSize().x * MAX_SCORE + GetSize().x / 2.0f)
			, GetPos().y
			, 0.0f)
			, D3DXVECTOR2(GetSize().x, GetSize().y));
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
//�X�R�A�̏I������
//=============================================================================
void CScore::Uninit()
{
	//�i���o�[�̔j��
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
		}
	}

	//�j������
	Flag();
}

//=============================================================================
//�X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
//�X�R�A�̕`�揈��
//=============================================================================
void CScore::Draw()
{
}

//=============================================================================
//�X�R�A�̐�������
//=============================================================================
CScore *CScore::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//���I�m��
	CScore *pScore;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		//������
		pScore->SetPos(pos);
		pScore->SetSize(size);
		pScore->Init();
	}

	return pScore;
}

//=============================================================================
//�X�R�A�̐ݒ菈��
//=============================================================================
void CScore::SetScore(int nScore)
{
	int aPosTexU[8];	//�e���̐������i�[

	m_nScore = nScore;

	aPosTexU[0] = m_nScore % 100000000 / 10000000;
	aPosTexU[1] = m_nScore % 10000000 / 1000000;
	aPosTexU[2] = m_nScore % 1000000 / 100000;
	aPosTexU[3] = m_nScore % 100000 / 10000;
	aPosTexU[4] = m_nScore % 10000 / 1000;
	aPosTexU[5] = m_nScore % 1000 / 100;
	aPosTexU[6] = m_nScore % 100 / 10;
	aPosTexU[7] = m_nScore % 10 / 1;

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetTex(10.0f, (float)aPosTexU[nCntScore]);
	}

	CRanking::GetRanking(m_nScore);
}