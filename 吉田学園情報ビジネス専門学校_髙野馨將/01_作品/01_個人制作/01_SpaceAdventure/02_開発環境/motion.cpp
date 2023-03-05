//======================================================
//
//motion.cpp
//Author : ����]�� KAJITA HIROMU
//
//======================================================
#include "motion.h"
#include "model.h"
#include "game.h"
#include <stdio.h>

//�A�j���[�V�������̃e�L�X�g�t�@�C���̑��΃p�X
char* CMotion::m_pAnimPass[ANIM_TYPE_MAX] =
{
	{ "data\\TEXT\\motion.txt" },
};

//�ÓI�����o�ϐ��錾
CMotion::MotionSet CMotion::m_AnimSet[] = {};

//======================================================
//�R���X�g���N�^
//======================================================
CMotion::CMotion()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CMotion::~CMotion()
{
}

//======================================================
//����������
//======================================================
HRESULT CMotion::Init()
{
	m_nPresentMotionSet = 0;	//�Đ�����郂�[�V�����Z�b�g�̔ԍ�
	m_nPresentFrame = 0;		//���݂̃t���[��	

	m_nNumkey = 2;				//�L�[�̑���
	m_nCurrentKey = 0;			//���݂̃L�[�ԍ�
	m_nCountMotion = 0;			//���[�V�����J�E���^�[
	m_bLoop = true;

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CMotion::Uninit()
{
}

//======================================================
//�X�V����
//======================================================
void CMotion::Update()
{
	for (int nCntModel = 0; nCntModel < CPlayer::MAX_MODEL; nCntModel++)
	{
		//�v���C���[�̏����擾
		CPlayer *pPlayer = CGame::GetPlayer();
		if (pPlayer != nullptr)
		{
			CModel *pModel[CPlayer::MAX_MODEL] = {};
			pModel[nCntModel] = pPlayer->GetModel(nCntModel);

			if (m_bLoop)
			{
				if (pModel[nCntModel] != nullptr)
				{
					D3DXVECTOR3 NowPointPos;
					D3DXVECTOR3 NowPointRot;

					// �ړI�̃L�[
					int nDestKey = m_nCurrentKey + 1;

					if (nDestKey >= m_nNumkey)
					{
						nDestKey = 0;
					}

					//����
					D3DXVECTOR3 SubPos = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosX - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosX,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosY - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosY,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosZ - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosZ);

					//���Βl�̌v�Z
					float ratio = (float)m_nCountMotion / (float)m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].nFrame;

					//���ݒn�̐ݒ�
					NowPointPos = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosX + (SubPos.x * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosY + (SubPos.y * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosZ + (SubPos.z * ratio));

					//����
					D3DXVECTOR3 SubRot = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotX - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotX,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotY - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotY,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotZ - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotZ);

					//���݂̌����̐ݒ�
					NowPointRot = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotX + (SubRot.x * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotY + (SubRot.y * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotZ + (SubRot.z * ratio));

					//���݂̈ʒu
					pModel[nCntModel]->SetPos(D3DXVECTOR3(NowPointPos.x, NowPointPos.y + 10.0f, NowPointPos.z + 5.0f));
					pModel[nCntModel]->SetRot(NowPointRot);
				}
			}
		}
	}

	//�J�E���^�[��i�߂�
	m_nCountMotion++;

	//���݂̍Đ��t���[���ɒB������
	if (m_nCountMotion >= 60)
	{
		m_nCurrentKey++;		//���݂̃L�[�ԍ���i�߂�
		m_nCountMotion = 0;		//���[�V�����J�E���^�[�̏�����
	}

	//���݂̃L�[�ԍ����L�[�̑����ɒB������
	if (m_nCurrentKey >= m_nNumkey)
	{
		m_nPresentMotionSet++;
		m_nCurrentKey = 0;
	}

	//���̃��[�V����
	m_nPresentFrame++;		//���݃t���[�����X�V����

	int nextAnim = m_AnimSet[m_nPresentMotionSet].nLoopAnim;

	if (m_nPresentFrame > m_AnimSet[m_nPresentMotionSet].aKeySet[m_nNumkey - 1].nFrame)
	{//�A�j���[�V�����̃��[�V�����Z�b�g�ő�t���[�����z�����ꍇ
		if (nextAnim == 0)
		{
			m_nPresentMotionSet = m_nPresentMotionSet;
		}
		else if (nextAnim == 1)
		{
			m_bLoop = false;
		}

		m_nPresentFrame = 0;				//�t���[����0�ɖ߂�
	}
}

//======================================================
//��������
//======================================================
CMotion * CMotion::Create(AnimType type)
{
	//�A�j���[�^�[�𐶐�����
	CMotion* pMotion = new CMotion;

	if (FAILED(pMotion->Init()))
	{//����������
		return nullptr;
	}

	pMotion->m_type = type;					//��ނ̐ݒ�

	//���������A�j���[�^�[��Ԃ�
	return pMotion;
}

//======================================================
//�t�@�C���ǂݍ���
//======================================================
void CMotion::LoadFile()
{
	int nCntMotion = -1;		//���݂̃A�j���[�V�����J�E���^�[������������
	int nCntKeySet = -1;		//���݂̃L�[�Z�b�g������������
	int nCntKey = -1;			//���݂̃L�[������������
	char aText[2000] = {};		//��������i�[����z��

	//�t�@�C���|�C���^��錾
	FILE *pFile;

	//�t�@�C���ǂݍ���
	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//�e�L�X�g�̍ŏ��̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fgets(aText, MAX_WORDCOUNT, pFile);		//��s���Ɠǂݍ���
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//�e�L�X�g�̍Ō�̍s��ǂݍ��ނ܂ŌJ��Ԃ�
			fscanf(pFile, "%s", &aText[0]);	//�t�@�C�����當�����ǂݍ���(	�ǂݍ��݊J�n)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORDCOUNT, pFile);		//��s���Ɠǂݍ���
				continue;
			}

			if (strcmp(&aText[0], "MOTIONSET") == 0)
			{
				nCntMotion++;			//���[�V�����Z�b�g�̃J�E���^�[���C���N�������g����
				nCntKeySet = -1;		//�L�[�Z�b�g�����ɖ߂�

				while ((strcmp(&aText[0], "END_MOTIONSET") != 0))
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORDCOUNT, pFile);		//��s���Ɠǂݍ���
						continue;
					}

					else if (strcmp(&aText[0], "LOOP") == 0)
					{
						int LOOP = 0;
						fscanf(pFile, "%s %d", &aText[0], &LOOP);

						m_AnimSet[nCntMotion].nLoopAnim = LOOP;	//���̃A�j���[�V������ݒ肷��
					}

					else if (strcmp(&aText[0], "KEYSET") == 0)
					{
						nCntKeySet++;								//�L�[�Z�b�g���C���N�������g����
						nCntKey = -1;								//�L�[�J�E���^�[�����ɖ߂�

						while ((strcmp(&aText[0], "END_KEYSET") != 0))
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORDCOUNT, pFile);		//��s���Ɠǂݍ���
								continue;
							}

							else if (strcmp(&aText[0], "FRAME") == 0)
							{
								int nFrames = 0;
								fscanf(pFile, "%s %d", &aText[0], &nFrames);

								m_AnimSet[nCntMotion].aKeySet[nCntKeySet].nFrame = nFrames;		//�t���[�����̐ݒ菈��
							}

							else if (strcmp(&aText[0], "KEY") == 0)
							{
								//�L�[�J�E���^�[���C���N�������g����
								nCntKey++;

								while ((strcmp(&aText[0], "END_KEY") != 0))
								{
									fscanf(pFile, "%s", &aText[0]);

									if (strcmp(&aText[0], "POS") == 0)
									{
										fscanf(pFile, "%s %f %f %f", &aText[0], &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosX, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosY, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosZ);
									}

									else if (strcmp(&aText[0], "ROT") == 0)
									{
										fscanf(pFile, "%s %f %f %f", &aText[0], &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotX, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotY, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotZ);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//======================================================
//�A�j���[�V�����̐ݒ�
//======================================================
void CMotion::SetPresentAnim(int nPresentAnim)
{
	if (m_nPresentMotionSet != nPresentAnim)
	{
		m_nPresentMotionSet = nPresentAnim;
		m_nPresentFrame = 0;
	}
}