//=============================================================================
//
// �����L���O����
// Author:����]��
//
//=============================================================================
#ifndef _RANKING_H_                        //���̃}�N����`������ĂȂ�������
#define _RANKING_H_                        //��d�C���N���[�h�h�~�̃}�N����`

#include "mode.h"

//�O���錾
class CObject2D;
class CFade;
class CNumber;

//�}�N����`
#define MAX_RANKING			(8)        //�����L���O�̌���
#define MAX_RANKING_RANK    (5)        //�����L���O�̏��ʕ�
#define MAX_TEXTURE			(4)        //�e�N�X�`���̐�

//�����L���O�N���X
class CRanking : public CMode
{
public:
	CRanking();
	~CRanking();

	//�v���g�^�C�v�錾
	HRESULT Init();
	void Uninit();
	void Update();
	void Load();
	void Save();
	void SetRankingScore();
	static void GetRanking(int nRanking) { m_nRanking = nRanking; }
	static CRanking *Create();    //�����L���O�̐���

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE] = {};            //�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D[3];                                  //Object2D�̃|�C���^�ϐ�
	CFade *m_pFade;
	static CNumber *m_apNumber[MAX_RANKING_RANK][MAX_RANKING];    //Number�^�̔z��
	static int m_nRanking;
	static int m_nData[MAX_RANKING_RANK];
	bool m_bYourRank[MAX_RANKING_RANK];
	bool m_bColorChange;
};

#endif;