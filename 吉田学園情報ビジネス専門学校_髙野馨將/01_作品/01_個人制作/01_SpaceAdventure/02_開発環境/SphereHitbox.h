//=============================================================================
//
// spherehitbox.h
// Author : ����]�� 
//
//=============================================================================
#ifndef _SPHERE_HITBOX_H_
#define _SPHERE_HITBOX_H_

#include "hitbox.h"

//�~���̓����蔻��̃N���X
class CSphereHitbox : public CHitbox
{
public:
	CSphereHitbox();						//�R���X�g���N�^
	~CSphereHitbox() override;				//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void    Uninit(void) override;			//�I������
	void    Update(void) override;			//�X�V����

	//��������
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CSphereHitbox *Hitbox);
private:

	bool SphereCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);		//�~�Ɖ~���̓����蔻��
	bool SphereSphereHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);			//�~�Ɖ~�̓����蔻��
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);					//�_�Ƌ�`�̓����蔻��
};

#endif