//=============================================================================
//
// �i���o�[����
// Author:����]��
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

//�}�N����`
#define NUMBER_SIZE_X    (30.0f)        //�i���o�[1�̕�
#define NUMBER_SIZE_Y    (60.0f)       //�i���o�[1�̍���

//�i���o�[�N���X
class CNumber : public CObject2D
{
public:
	explicit CNumber(int nPriority = PRIORITY_4);            //�R���X�g���N�^
	~CNumber();           //�f�X�g���N�^

	HRESULT Init() override;							//����������
	void Uninit() override;								//�I������
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 &size);      //����

private:
	LPDIRECT3DTEXTURE9 m_pTexture;     //���ʃe�N�X�`���̃|�C���^
};
#endif