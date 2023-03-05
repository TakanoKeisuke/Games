//======================================================
//
//motion.h
//Author : ����]�� KAJITA HIROMU
//
//======================================================
#ifndef  _MOTION_H_					//���̃}�N����`������ĂȂ�������
#define  _MOTION_H_					//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "player.h"

//�}�N����`
#define	MAX_WORDCOUNT	(1024)		//�����̍ő吔

//���[�V�����N���X
class CMotion
{
public:

	//�A�j���[�V�����̎��
	enum AnimType
	{
		ANIM_TYPE_PLAYER = 0,					//�v���C���[�A�j���[�V����
		ANIM_TYPE_MAX
	};

	struct KEY
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	};

	struct KEY_SET
	{
		int nFrame;
		KEY aKey[CPlayer::MAX_MODEL];
	};

	struct MotionSet
	{
		int nLoopAnim;
		KEY_SET aKeySet[2];
	};

	CMotion();									//�R���X�g���N�^
	~CMotion();									//�f�X�g���N�^

	HRESULT Init();								//����������
	void Uninit();								//�I������
	void Update();								//�X�V����

	static CMotion *Create(AnimType type);		//���[�V�����̐���

	static void LoadFile();
	void SetPresentAnim(int nPresentAnim);		//�A�j���[�V�����̐ݒ菈��

private:
	static char* m_pAnimPass[ANIM_TYPE_MAX];	//�A�j���[�V�����̊O���t�@�C���̑��΃p�X
	static MotionSet m_AnimSet[3];
	AnimType m_type;							//�A�j���[�V�����̎��

	int m_nNumkey;				//�L�[�̑���
	int m_nCurrentKey;			//���݂̃L�[�ԍ�
	int m_nCountMotion;			//���[�V�����J�E���^�[
	int m_nPresentFrame;		//���݂̃t���[��
	int m_nPresentMotionSet;	//�Đ�����郂�[�V�����Z�b�g�̔ԍ�

	bool m_bLoop;				//���[�v���邩���Ȃ���
};
#endif