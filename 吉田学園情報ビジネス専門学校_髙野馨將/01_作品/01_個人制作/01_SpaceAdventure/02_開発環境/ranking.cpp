//=============================================================================
//
// �����L���O����
// Author:����]��
//
//=============================================================================
#include <stdio.h>
#include "application.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "ranking.h"
#include "fade.h"
#include "inputPad.h"
#include "sound.h"
#include "number.h"

//�ÓI�����o�ϐ��錾
CNumber *CRanking::m_apNumber[MAX_RANKING_RANK][MAX_RANKING];
int CRanking::m_nData[MAX_RANKING_RANK];
int CRanking::m_nRanking;
//======================================================
//�R���X�g���N�^
//======================================================
CRanking::CRanking() : CMode()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CRanking::~CRanking()
{
}

//======================================================
//����������
//======================================================
HRESULT CRanking::Init(void)
{
	//������
	m_bYourRank[MAX_RANKING_RANK] = {};
	m_bColorChange = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.jpg",
		&m_pTexture[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rankinglogo.png",
		&m_pTexture[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&m_pTexture[2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture[3]);

	//�|���S���̐���
	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);
	//�|���S���̐���
	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(600.0f, 80.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[1]->SetSize(D3DXVECTOR3(480.0f, 180.0f, 0.0f));
	m_pObject2D[1]->BindTexture(m_pTexture[1]);
	//�|���S���̐���
	m_pObject2D[2] = CObject2D::Create(D3DXVECTOR3(200.0f, 420.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), PRIORITY_3);
	m_pObject2D[2]->SetSize(D3DXVECTOR3(200.0f, 500.0f, 0.0f));
	m_pObject2D[2]->BindTexture(m_pTexture[2]);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking] = CNumber::Create(D3DXVECTOR3(60.0f * nCntRanking + 400.0f, 100.0f * nCnt + 220.0f, 0.0f), D3DXVECTOR2(30.0f, 60.0f));
			m_apNumber[nCnt][nCntRanking]->BindTexture(m_pTexture[3]);
		}
	}

	//�t�@�C���ǂݍ��ݏ���
	Load();

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CRanking::Uninit(void)
{
	//�j������
	Flag();
}

//======================================================
//�X�V����
//======================================================
void CRanking::Update(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (CInputKeyboard::GetKeyboardPress(DIK_RETURN) && CFade::GetFade() == CFade::FADE_NONE
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && CFade::GetFade() == CFade::FADE_NONE)
	{
		//���[�h�ݒ�
		Save();
		CFade::SetFade(CApplication::MODE_TITLE);
	}

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			if (m_bYourRank[nCnt])
			{//��x���F���ς���ĂȂ�������F��ς���
				m_apNumber[nCnt][nCntRanking]->SetCol(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
				m_bColorChange = true;
			}
		}
		if (m_bColorChange)
		{//�F���ς������ʂ�Ȃ�����
			return;
		}
	}
}

//============================
//�t�@�C���ɏ����o��
//============================
void CRanking::Save()
{
	FILE*pFile;		//�t�@�C���|�C���^�錾

	//�t�@�C�����J��
	pFile = fopen("data/Save/ranking.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
		{
			//�t�@�C���ɐ��l�������o��
			fprintf(pFile, "%d\n", m_nData[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***");
	}
}

//============================
//�t�@�C������ǂݍ���
//============================
void CRanking::Load()
{
	FILE*pFile;		//�t�@�C���|�C���^�錾

	//�t�@�C�����J��
	pFile = fopen("data/Save/ranking.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
		{
			//�t�@�C�����琔�l��ǂݍ���
			fscanf(pFile, "%d\n", &m_nData[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***");
	}
}

//====================================
//�X�R�A�̐ݒ菈��
//====================================
void CRanking::SetRankingScore()
{
	int aPosTexU[MAX_RANKING_RANK][MAX_RANKING];	//�e���̐������i�[

	//�V�����X�R�A�ƌÂ��X�R�A�̔�r
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK + 1; nCnt++)
	{
		if (m_nRanking > m_nData[4])
		{
			m_nData[4] = m_nRanking;
		}
	}
	//�o�u���\�[�g
	for (int nCount = 0; nCount < MAX_RANKING_RANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKING_RANK; nCount2++)
		{
			if (m_nData[nCount] < m_nData[nCount2])
			{
				int nMin = m_nData[nCount];
				m_nData[nCount] = m_nData[nCount2];
				m_nData[nCount2] = nMin;
				m_bYourRank[nCount] = true;
			}
		}
	}
	for (int nCntScore = 0; nCntScore < MAX_RANKING_RANK; nCntScore++)
	{
		aPosTexU[nCntScore][0] = m_nData[nCntScore] % 100000000 / 1000000;
		aPosTexU[nCntScore][1] = m_nData[nCntScore] % 10000000 / 1000000;
		aPosTexU[nCntScore][2] = m_nData[nCntScore] % 1000000 / 100000;
		aPosTexU[nCntScore][3] = m_nData[nCntScore] % 100000 / 10000;
		aPosTexU[nCntScore][4] = m_nData[nCntScore] % 10000 / 1000;
		aPosTexU[nCntScore][5] = m_nData[nCntScore] % 1000 / 100;
		aPosTexU[nCntScore][6] = m_nData[nCntScore] % 100 / 10;
		aPosTexU[nCntScore][7] = m_nData[nCntScore] % 10 / 1;
	}

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKING_RANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking]->SetTex(10.0f, (float)aPosTexU[nCnt][nCntRanking]);
		}
	}
}

//======================================================
//��������
//======================================================
CRanking *CRanking::Create()
{
	//���I�m��
	CRanking *pRanking = new CRanking;

	if (pRanking != nullptr)
	{
		//������
		pRanking->Init();
		pRanking->SetRankingScore();
	}

	return pRanking;
}