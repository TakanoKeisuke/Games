//=============================================================================
//
// goal.h
// Author : ����]��
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "objectX.h"

//�O���錾
class CCylinderHitbox;

//�S�[���N���X
class CGoal : public CObjectX
{
public:
	explicit CGoal(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CGoal() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CGoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//��������

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;					//�q�b�g�{�b�N�X
};

#endif