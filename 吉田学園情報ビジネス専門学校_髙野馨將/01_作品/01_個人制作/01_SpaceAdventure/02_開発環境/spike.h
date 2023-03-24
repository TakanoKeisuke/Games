//=============================================================================
//
// Spike.h
// Author : ����]��
//
//=============================================================================
#ifndef _SPIKE_H_
#define _SPIKE_H_

#include "objectX.h"
#include "gimmick.h"

//�O���錾
class CCylinderHitbox;

//��Q���N���X
class CSpike : public CObjectX
{
public:
	explicit CSpike(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CSpike() override;									//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
	//�ÓI�����o�֐�
	static CSpike *Create(const D3DXVECTOR3 pos, CGimmick::GIMMICK_TYPE type, int range);		//��������

private:
	//�����o�ϐ�
	CCylinderHitbox *m_pHitbox;							//�q�b�g�{�b�N�X
	CGimmick::GIMMICK_TYPE m_type;						//���̎��
	float m_fHeight;									//�T�C���J�[�u�̕�
	float m_fRange;										//������
};

#endif