//=============================================================================
//
// ���U���g����
// Author:����]��
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "mode.h"

//�O���錾
class CObject2D;

//�}�N����`
#define MAX_RESULT		(3)			//�|���S���̍ő吔

//���U���g�N���X
class CResult : public CMode
{
public:
	CResult();			//�R���X�g���N�^
	~CResult();			//�f�X�g���N�^
	//�����o�֐�
	HRESULT Init();			//������
	void Uninit();			//�I��
	void Update();			//�X�V
	//�ÓI�����o�֐�
	static CResult *Create();	//�|���S���̐���
	static void SetClear(bool clear) { b_clear = clear; }
	static bool GetClear() { return b_clear; }

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT];		//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D;
	static bool b_clear;							//�N���A������

};
#endif