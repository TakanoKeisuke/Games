//=============================================================================
//
// hitbox.h
// Author : ����]�� Ricci Alex
//
//=============================================================================
#ifndef _CYLINDER_HITBOX_H_
#define _CYLINDER_HITBOX_H_

#include "hitbox.h"

//�~���̓����蔻��̃N���X
class CCylinderHitbox : public CHitbox
{
public:
	CCylinderHitbox();						//�R���X�g���N�^
	~CCylinderHitbox() override;			//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void    Uninit(void) override;			//�I������
	void    Update(void) override;			//�X�V����

	//��������
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CCylinderHitbox *Hitbox);
private:

	bool CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);							//�~���Ɖ~���̓����蔻��
	//bool CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);		//�~���Ƌ�`�̓����蔻��
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);				//�_�Ƌ�`�̓����蔻��
};

#endif