//=============================================================================
//
// BoxHitbox.h
// Author : ����]�� Ricci Alex
//
//=============================================================================
#ifndef _BOX_HITBOX_H_
#define _BOX_HITBOX_H_

#include "hitbox.h"

//��`�̓����蔻��̃N���X
class CBoxHitbox : public CHitbox
{
public:
	CBoxHitbox();										//�R���X�g���N�^
	~CBoxHitbox() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void    Uninit(void) override;						//�I������
	void    Update(void) override;						//�X�V����

	//�ÓI�����o�֐�
	//��������
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent,CBoxHitbox* Hitbox);
private:

	bool BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);					//�����蔻��
};

#endif