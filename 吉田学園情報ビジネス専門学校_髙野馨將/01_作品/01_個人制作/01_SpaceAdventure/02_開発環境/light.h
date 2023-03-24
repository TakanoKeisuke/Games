//========================================================
//
//���C�g
//Author:����]��
//
//========================================================
#ifndef _LIGHT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _LIGHT_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//���C�g�N���X
class CLight
{
private:
	static const int MAX_LIGHT = 1;
public:
	CLight();													//�R���X�g���N�^
	~CLight();													//�f�X�g���N�^
	//�����o�֐�
	void Init();
	void Uninit();
	void Update();
	D3DLIGHT9 GetLight() { return m_aLight[0]; }

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//���C�g���
};

#endif