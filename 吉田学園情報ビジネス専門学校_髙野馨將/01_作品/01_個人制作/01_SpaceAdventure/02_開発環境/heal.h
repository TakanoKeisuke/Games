//=============================================================================
//
// heal.h
// Author : ����]��
//
//=============================================================================
#ifndef _HEAL_H_
#define _HEAL_H_

#include "objectX.h"

//�O���錾
class CCylinderHitbox;

//�񕜃N���X
class CHeal : public CObjectX
{
public:
	explicit CHeal(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CHeal() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CHeal* Create(D3DXVECTOR3 pos);			//��������

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;						//�q�b�g�{�b�N�X
};

#endif