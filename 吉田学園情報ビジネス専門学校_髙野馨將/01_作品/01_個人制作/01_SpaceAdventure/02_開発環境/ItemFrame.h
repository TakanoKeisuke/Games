//=============================================================================
//
// itemframe.h
// Author:����]��
//
//=============================================================================
#ifndef _ITEMFRAME_H_
#define _ITEMFRAME_H_

#include "object2D.h"

//�A�C�e���t���[���N���X
class CItemFrame : public CObject2D
{
public:
	explicit CItemFrame(int nPriority = PRIORITY_4);		//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CItemFrame() override;									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw(void) override;							//�`��

	void SetGetItem(bool bGet) { m_bGet = bGet; }		//�擾�̗L���̐ݒ�
	//�ÓI�����o�֐�
	static CItemFrame *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//����

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	bool m_bGet;								//�A�C�e������肵�Ă��邩�ǂ���
};

#endif