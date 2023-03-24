//======================================================
//
//planet.h
//Author : ����]��
//
//======================================================
#ifndef  _PLANET_H_				//���̃}�N����`������ĂȂ�������
#define  _PLANET_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include "mesh_sphere.h"
#include <vector>

//�f���N���X
class CPlanet : public CMesh_sphere
{
public:
	CPlanet(int nPriority = 3);			//�R���X�g���N�^
	~CPlanet() override;

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	bool SetGravity(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);					//���͂̐ݒ�
	bool GetInside(void) { return m_binside; }								//�����蔻��̎擾
	bool CollisionSphere(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize);			//�~�̓����蔻��
	float TargetDistance(CObject *pTarget);									//�ڕW�Ƃ̋����̎Z�o

	static CPlanet *CPlanet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	bool m_binside;						//�����ɂ��邩�ǂ���
};

#endif
