//=============================================================================
//
// �I�u�W�F�N�g
// Author:����]��
//
//=============================================================================
#include "object.h"

//�ÓI�����o�ϐ��錾
CObject *CObject::m_pTop[PRIORITY_MAX] = {};		//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};	//���݂̃I�u�W�F�N�g�ւ̃|�C���^
//======================================================
//�R���X�g���N�^
//======================================================
CObject::CObject(int nPriority /*=3*/)
{
	m_bDeath = false;

	//Next��Prev�̏�����
	m_pNext, m_pPrev = nullptr;

	//�I�u�W�F�N�g�����X�g�ɒǉ�
	if (m_pTop[nPriority] == nullptr)
	{//�擪��null��������
	 //Top�ɏ�������
		m_pTop[nPriority] = this;
	}
	else
	{//null����Ȃ�������
		m_pCurrent[nPriority]->m_pNext = this;	//���݂̃I�u�W�F�N�g��Next�ɏ�������
		this->m_pPrev = m_pCurrent[nPriority];	//Prev�Ɍ��݂̃I�u�W�F�N�g�̏�������
	}

	m_pCurrent[nPriority] = this;	//���݂̃I�u�W�F�N�g�ɏ�������
	m_nPriority = nPriority;		//Priority��ۑ�
}

//======================================================
//�f�X�g���N�^
//======================================================
CObject::~CObject()
{
}

//======================================================
//�S�Ẵ|���S���̔j������
//======================================================
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (!pCurrentObj->m_bDeath)
			{
				pCurrentObj->Uninit();	//Top��nullptr�ɂȂ�܂�Release���Ă�
			}

			pCurrentObj = pObjNext;
		}
	}

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (pCurrentObj->m_bDeath)
			{
				pCurrentObj->Break();
			}

			pCurrentObj = pObjNext;
		}

		m_pTop[nCnt] = nullptr;
		m_pCurrent[nCnt] = nullptr;
	}
}

//======================================================
//�X�V����
//======================================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		//Top�̏����|�C���^�ϐ��ɓ����
		CObject *NowPoint = m_pTop[nCnt];

		while (NowPoint)
		{
			//Update()�ō폜������pNext��������̂ŁA���O�ɕۑ����Ă���
			CObject *pObjectNext = NowPoint->m_pNext;

			if (!NowPoint->m_bDeath)
			{
				//�X�V����
				NowPoint->Update();
			}

			//Top��Next�̏�������
			NowPoint = pObjectNext;
		}

		while (NowPoint)
		{
			if (NowPoint->m_bDeath)
			{
				NowPoint->Break();
			}
		}
	}
}

//======================================================
//�`�揈��
//======================================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		//Top�̏����|�C���^�ϐ��ɓ����
		CObject *NowPoint = m_pTop[nCnt];

		while (NowPoint)
		{
			//Update()�ō폜������pNext��������̂ŁA���O�ɕۑ����Ă���
			CObject *pObjectNext = NowPoint->m_pNext;

			if (!NowPoint->m_bDeath)
			{
				NowPoint->Draw();
			}

			//Top��Next�̏�������
			NowPoint = pObjectNext;
		}
	}
}

//======================================================
//�j������
//======================================================
void CObject::Break()
{
	//�I�u�W�F�N�g�����X�g����폜
	if (m_pNext != nullptr)
	{
		if (m_pPrev != nullptr)
		{
			m_pNext->m_pPrev = this->m_pPrev;
			m_pPrev->m_pNext = this->m_pNext;
		}
		else
		{
			m_pNext->m_pPrev = this->m_pPrev;
			m_pTop[m_nPriority] = this->m_pNext;
		}
	}
	else
	{
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = this->m_pNext;
			m_pCurrent[m_nPriority] = this->m_pPrev;
		}
		else
		{
			m_pTop[m_nPriority] = nullptr;
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//this->Uninit();
	//�I�u�W�F�N�g��j��
	delete this;
}

//======================================================
//���[�h�̉������
//======================================================
void CObject::ReleaseMode()
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNext�̕ۑ�
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != OBJTYPE_MODE)
				{
					//�I�������̊֐��Ăяo��
					pObject->Break();
				}

				//pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}

		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNext�̕ۑ�
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != OBJTYPE_MODE)
				{
					pObject->Flag();
				}

				//pObject��pObject��pNext����
				pObject = pObjectNext;
			}
		}
	}
}