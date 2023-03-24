//=============================================================================
//
// �^�C�g������
// Author:����]��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "mode.h"

//�O���錾
class CObject2D;

//�}�N����`
#define MAX_TUTORIAL		(1)			//�|���S���̍ő吔

//�`���[�g���A���N���X
class CTutorial : public CMode
{
public:
	CTutorial();			//�R���X�g���N�^
	~CTutorial();			//�f�X�g���N�^
						//�����o�֐�
	HRESULT Init();			//������
	void Uninit();				//�I��
	void Update();				//�X�V
	//�ÓI�����o�֐�
	static CTutorial *Create();	//�^�C�g���̐���

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIAL];		//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D;
};

#endif