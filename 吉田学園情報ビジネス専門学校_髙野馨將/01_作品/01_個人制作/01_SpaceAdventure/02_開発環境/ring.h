//=============================================================================
//
// ring.h
// Author : ����]��
//
//=============================================================================
#ifndef _RING_H_
#define _RING_H_

#include "objectX.h"

//�O���錾
class CSphereHitbox;

//�ړ��N���X
class CRing : public CObjectX
{
public:
	explicit CRing(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CRing() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CRing* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);			//��������

private:
	//�����o�ϐ�
	CSphereHitbox* m_pHitbox;					//�q�b�g�{�b�N�X
};

#endif