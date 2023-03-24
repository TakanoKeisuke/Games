//=============================================================================
//
// enemy.h
// Author : ����]��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "objectX.h"
#include "gimmick.h"

//�O���錾
class CCylinderHitbox;

//�G�l�~�[�N���X
class CEnemy : public CObjectX
{
public:
	explicit CEnemy(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CEnemy() override;									//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
	void Chase(void);									//�ǔ�����
	//�ÓI�����o�֐�
	static CEnemy *Create(const D3DXVECTOR3 pos, int range);		//��������

private:
	//�����o�ϐ�
	CCylinderHitbox *m_pHitbox;							//�q�b�g�{�b�N�X
	CGimmick::GIMMICK_TYPE m_type;						//���̎��
	float m_fHeight;									//�T�C���J�[�u�̕�
	float m_fRange;										//�ǂ��Ă���͈�
};

#endif