//=============================================================================
//
// �Q�[������
// Author:����]��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

//�O���錾
class CStage;
class CPlayer;
class CEnemy;
class CMesh_sphere;
class CSphere;
class CLife_gauge;
class CItemFrame;
class CParticle;
class CTimer;
class CScore;

//�Q�[���N���X
class CGame : public CMode
{
public:
	static const int MAX_SECRET = 3;								//�B���A�C�e���̍ő吔
	static const int MAX_HALF_SPHERE = 2;							//�����̍ő吔
	static const int MAX_PARTICLE = 20;								//�p�[�e�B�N���̍ő吔

	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^
	//�����o�֐�
	HRESULT Init();		//������
	void Uninit();		//�I��
	void Update();		//�X�V
	void Draw();		//�`��

	//�ÓI�����o�֐�
	static CGame *Create();									//�Q�[���̐���
	//���̎擾
	static CItemFrame *GetFrame(int nCnt) { return m_pFrame[nCnt]; }
	static CLife_gauge *GetLifeGage() { return m_pLife; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CParticle **GetParticle() { return m_pParticle; }
	static CSphere *GetSphere() { return m_pSphere; }
	static CTimer *GetTimer() { return m_pTimer; }
	static CEnemy *GetEnemy() { return m_pEnemy; }
	static CMesh_sphere *GetMesh_sphere(int nCnt) { return m_pMesh_sphere[nCnt]; }
	static CScore *GetScore() { return m_pScore; }

private:
	//�ÓI�����o�ϐ�
	static CItemFrame *m_pFrame[MAX_SECRET];
	static CPlayer *m_pPlayer;
	static CSphere *m_pSphere;
	static CMesh_sphere *m_pMesh_sphere[MAX_HALF_SPHERE];
	static CLife_gauge *m_pLife;
	static CParticle *m_pParticle[MAX_PARTICLE];
	static CTimer *m_pTimer;
	static CEnemy *m_pEnemy;
	static CScore *m_pScore;
	static CStage *m_pStage;
};
#endif