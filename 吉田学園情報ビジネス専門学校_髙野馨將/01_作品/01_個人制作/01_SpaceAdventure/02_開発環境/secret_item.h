//=============================================================================
//
// secret_item.h
// Author : ����]��
//
//=============================================================================
#ifndef _SECRET_ITEM_H_
#define _SECRET_ITEM_H_

#include "objectX.h"

//�O���錾
class CCylinderHitbox;

//�B���A�C�e���N���X
class CSecret_item : public CObjectX
{
public:
	explicit CSecret_item(int nPriority = PRIORITY_3);			//�R���X�g���N�^
	~CSecret_item() override;									//�f�X�g���N�^

	HRESULT Init(void) override;								//����������
	void Uninit(void) override;									//�I������
	void Update(void) override;									//�X�V����
	void Draw(void) override;									//�`�揈��

	bool GetCollision(void) { return m_bCollision; }			//���̎擾

	static CSecret_item* Create(D3DXVECTOR3 pos,int number);	//��������

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;						//�q�b�g�{�b�N�X
	int m_nNumber;
	bool m_bCollision;
};

#endif