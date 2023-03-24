//=============================================================================
//
// player
// Author:����]��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include<vector>

//�O���錾
class CModel;
class CBoxHitbox;
class CCylinderHitbox;
class CSphereHitbox;
class CMotion;
class CShadow;

//�v���C���[�N���X
class CPlayer : public CObject
{
public:
	enum PLAYER_TYPE
	{
		TYPE_NONE = 0,
		TYPE_SPEED,
		TYPE_JUMP,
		TYPE_FLY,

		TYPE_MAX
	};

	static const int MAX_MODEL = 9;								//���f���̍ő吔
	static const int MAX_WORD = 512;

	explicit CPlayer(int nPriority = PRIORITY_3);					//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CPlayer() override;											//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;							//������
	virtual void CPlayer::Uninit(void) override;					//�I��
	virtual void Update(void) override;								//�X�V
	virtual void Draw(void) override;								//�`��
	void LoadPlayer(void);											//�v���C���[���f���̓ǂݍ���
	void Input(void);												//����
	void CollisionObj(void);										//�I�u�W�F�N�g�Ɠ����������̏���
	void CollisionStage(void);										//�X�e�[�W�̓����蔻��
	void CollisionGimmick(void);									//�e�ƃM�~�b�N�̓����蔻��
	void Attack(void);												//�U������
	void BuffPlayer(void);											//�v���C���[�̋�������

	void BuffEffect(PLAYER_TYPE type);								//�������ʏ���
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//pos�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//size�̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }			//rot�̐ݒ�
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }		//move�̐ݒ�

	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//pos�̎擾
	const D3DXVECTOR3 GetPosOld(void) { return m_posOld; }			//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//size�̎擾
	const D3DXVECTOR3 GetMove(void) { return m_move; }				//move�̎擾
	const int GetLife(void) { return m_nLife; }						//�̗͂̎擾
	bool GetInside(void) { return m_bInside; }						//�����蔻��̎擾
	bool GetShadow(void) { return m_bShadow; }						//�e�̎擾
	CModel *GetModel(int nCnt) { return m_apModel[nCnt]; }			//���f���̎擾
	CMotion *GetMotion() { return m_pMotion; }						//���[�V�����̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//rot�̎擾
	
	//�ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority); //����

private:
	//�ÓI�����o�ϐ�
	static float m_fAcceleration;				//�����W��
	static float m_fJump;						//�W�����v��
	static int m_nGoalCnt;						//�S�[������t�F�[�h���̎���

	//�����o�ϐ�
	CModel *m_apModel[MAX_MODEL];				//���f���̏��
	CMotion *m_pMotion;							//���[�V�����̏��
	CSphereHitbox *m_pHitbox;					//�q�b�g�{�b�N�X
	CCylinderHitbox *m_pAttackHitbox;			//�U���̃q�b�g�{�b�N�X
	D3DXQUATERNION m_quat;						//�N�H�[�^�j�I��
	D3DXVECTOR3 m_Vec;							//�i�s�����x�N�g��
	D3DXVECTOR3	m_pos;							//�ʒu
	D3DXVECTOR3 m_posOld;						//�O��̈ʒu
	D3DXVECTOR3	m_Originpos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_size;							//�T�C�Y
	D3DXVECTOR3 m_rotDest;						//�ړI�̊p�x
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_vecAxis;						//���x�N�g��
	D3DXVECTOR3 m_norVec;						//�@���x�N�g��
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxQuat;						//�N�H�[�^�j�I��
	PLAYER_TYPE m_type;							//�v���C���[�̎��

	int m_nLife;								//�̗�
	int m_nCntModel;							//���f�������J�E���g
	int m_nInvincibleCnt;						//���G����
	int m_nBuffTime;							//��������
	int m_nCntGoal;								//�S�[����t�F�[�h����܂ł̎���
	float m_fCntSE;								//SE�̃J�E���g
	float m_fCT;								//�N�[���^�C��
	float m_fFriction;							//���C�W��
	float m_fBuffQuantity;						//�������ʂ̗�
	float m_fDash;								//�_�b�V�������x
	float m_fSlowFall;							//�������x�ቺ
	std::vector<bool> m_bCollisionField;		//�n�ʂ̓����蔻��
	bool m_bGoal;								//�S�[��������
	bool m_bGimmick;							//�M�~�b�N�ɏ���Ă��邩
	bool m_bJumping;							//�W�����v���Ă��邩
	bool m_bCollisionPlanet;					//�f���̓����蔻��
	bool m_bInside;								//�f���͈̔͂̓����ɓ����Ă��邩
	bool m_bModel;								//���f���̗L��
	bool m_bShadow;								//�e�̗L��
};

#endif