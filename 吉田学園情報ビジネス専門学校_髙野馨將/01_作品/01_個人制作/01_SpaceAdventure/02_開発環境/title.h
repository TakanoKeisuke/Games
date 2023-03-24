//=============================================================================
//
// �^�C�g������
// Author:����]��
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "mode.h"

//�O���錾
class CObject2D;

//�}�N����`
#define MAX_TITLE		(4)			//�|���S���̍ő吔

//�^�C�g���N���X
class CTitle : public CMode
{
public:
	CTitle();			//�R���X�g���N�^
	~CTitle();			//�f�X�g���N�^
	//�����o�֐�
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��
	//�ÓI�����o�֐�
	static CTitle *Create();			//�^�C�g���̐���

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE];		//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D[MAX_TITLE];				//2D�|���S���̏��
	int m_nCounter;									//�_�Ŏ���
	int m_nSelect;									//�I��ł���ԍ�
};

#endif