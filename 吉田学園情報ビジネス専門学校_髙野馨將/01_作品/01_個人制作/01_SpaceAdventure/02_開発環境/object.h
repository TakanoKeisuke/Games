//=============================================================================
//
// �I�u�W�F�N�g
// Author:����]��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,	//�^�C�v�Ȃ�
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_MODEL,		//���f��
		OBJTYPE_MODE,		//���[�h
		OBJTYPE_BOSS,		//�{�X
		OBJTYPE_MAX
	};

	enum EPriority
	{
		PRIORITY_1 = 0,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_MAX
	};

	explicit CObject(int nPriority = PRIORITY_3);		//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	virtual ~CObject();									//�f�X�g���N�^

	//�������z�֐�
	virtual HRESULT Init() = 0;							//������
	virtual void Uninit() = 0;							//�I��
	virtual void Update() = 0;							//�X�V
	virtual void Draw() = 0;							//�`��
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//�ʒu�̐ݒ�
	virtual const D3DXVECTOR3 GetSize(void) = 0;		//�T�C�Y�̎擾
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//�ʒu�̎擾

	//�ÓI�����o�֐�
	static void ReleaseMode();
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static int Random(const int min, const int max) { return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)); }				//������Ԃ�����

	//�����o�֐�
	void SetType(EObjType type) { m_type = type; }
	EObjType GetType() { return m_type; }
	void Flag() { m_bDeath = true; }
	void Break();

private:
	//�ÓI�����o�ϐ�
	static CObject *m_pTop[PRIORITY_MAX];					//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_pCurrent[PRIORITY_MAX];				//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|�C���^
	//�����o�ϐ�
	int m_nPriority;										//�D�揇��
	bool m_bDeath;											//���S�t���O
	EObjType m_type;
	D3DXVECTOR3 m_move;
	CObject *m_pPrev;										//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;										//���̃I�u�W�F�N�g�ւ̃|�C���^
};

#endif;