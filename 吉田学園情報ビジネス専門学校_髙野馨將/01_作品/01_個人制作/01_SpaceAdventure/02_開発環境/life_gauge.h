//=============================================================================
//
// life_gauge.h
// Author:����]��
//
//=============================================================================
#ifndef _LIFE_GAUGE_H_
#define _LIFE_GAUGE_H_

#include "object2D.h"

//HP�Q�[�W�N���X
class CLife_gauge : public CObject2D
{
public:
	explicit CLife_gauge(int nPriority = PRIORITY_4);		//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CLife_gauge() override;									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw(void) override;							 //�`��

	//�ÓI�����o�֐�
	static CLife_gauge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size); //����

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
};

#endif