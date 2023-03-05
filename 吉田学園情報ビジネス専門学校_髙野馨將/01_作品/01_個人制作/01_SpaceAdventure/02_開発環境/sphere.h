//=============================================================================
//
// Sphere
// Author:����]��
//
//=============================================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "objectX.h"

//�O���錾
class CBoxHitbox;
class CCylinderHitbox;

//���N���X
class CSphere : public CObjectX
{
public:
	explicit CSphere(int nPriority = PRIORITY_3);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CSphere() override;											//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;							//������
	virtual void CSphere::Uninit(void) override;					//�I��
	virtual void Update(void) override;								//�X�V
	virtual void Draw(void) override;								//�`��
	void Input(void);												//����		
	//�ÓI�����o�֐�
	static CSphere *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, int nPriority); //����

private:
	//�����o�ϐ�
	CCylinderHitbox* m_pHitbox;					//�q�b�g�{�b�N�X
	D3DXVECTOR3 m_rotDest;						//�ړI�̊p�x
	D3DXVECTOR3 m_vecAxis;						//��]��
	D3DXMATRIX m_mtxRot;						//��]�}�g���b�N�X(�ۑ��p)
	D3DXQUATERNION m_quat;						//�N�H�[�^�j�I��

	float m_fValueRot;							//��]�p
	bool m_bModel;								//���f���̗L��
};

#endif