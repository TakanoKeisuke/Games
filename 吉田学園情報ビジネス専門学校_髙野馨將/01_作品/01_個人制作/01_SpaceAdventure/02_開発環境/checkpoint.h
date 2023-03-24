//=============================================================================
//
// checkpoint.h
// Author : ����]��
//
//=============================================================================
#ifndef _CHECKPOINT_H_
#define _CHECKPOINT_H_

#include "objectX.h"

//�O���錾
class CCylinderHitbox;

//���p�n�_�N���X
class CCheckpoint : public CObjectX
{
public:
	explicit CCheckpoint(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CCheckpoint() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CCheckpoint* Create(D3DXVECTOR3 pos);			//��������

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;						//�q�b�g�{�b�N�X
};

#endif