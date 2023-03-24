//=============================================================================
//
// buff.h
// Author : ����]��
//
//=============================================================================
#ifndef _BUFF_H_
#define _BUFF_H_

#include "objectX.h"
#include "CylinderHitbox.h"

//�����A�C�e���N���X
class CBuff : public CObjectX
{
public:

	explicit CBuff(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CBuff() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CBuff* Create(const D3DXVECTOR3 pos, CHitbox::INTERACTION_EFFECT effect);			//��������

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;						//�q�b�g�{�b�N�X
	CHitbox::INTERACTION_EFFECT m_effect;			//��������

	bool m_bInvisible;
	int m_nInvincibleCnt;
};

#endif