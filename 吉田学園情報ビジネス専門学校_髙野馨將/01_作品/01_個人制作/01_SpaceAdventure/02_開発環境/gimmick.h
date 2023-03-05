//=============================================================================
//
// gimmick.h
// Author : ����]��
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "objectX.h"

//�M�~�b�N�N���X
class CGimmick : public CObjectX
{
public:
	enum GIMMICK_TYPE
	{
		TYPE_NONE = 0,
		TYPE_MOVE_X,
		TYPE_MOVE_Y,
		TYPE_MOVE_Z,
		TYPE_FALL,
		TYPE_FALL_LONG,

		TYPE_MAX
	};
	explicit CGimmick(int nPriority = PRIORITY_3);		//�R���X�g���N�^
	~CGimmick() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
	void TypeEffect(void);								//��ނ��Ƃ̏���

	bool PushPlayer(void);								//�v���C���[�̉��o����
	bool GetLanding(void) { return m_bLanding; }		//���n���Ă��邩�̎擾

	void Fall(void);																									//��������
	void Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type);												//�Đ�������
	static CGimmick* Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed);			//��������

private:
	//�����o�ϐ�
	GIMMICK_TYPE m_type;								//�M�~�b�N�̎��
	D3DXVECTOR3 OriginPos;								//�ŏ���pos
	int m_nFallTime;									//������܂Ŏ���
	int m_nRespawnTime;									//�Đ�������
	int m_nInvincibleCnt;
	float m_fHeight;									//�T�C���J�[�u�̕�
	float m_fSpeed;										//���x
	float m_fRange;										//�͈�
	float m_feffect;									//���ʗʂ̕ۑ�
	bool m_bCountStart;									//������͂��߂邩
	bool m_bLanding;									//���n���Ă��邩
	bool m_bRespawn;									//��������Đ�������
};

#endif