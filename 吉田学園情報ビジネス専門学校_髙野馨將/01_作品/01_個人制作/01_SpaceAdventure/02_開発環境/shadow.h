//========================================================
//
//�e
//Author:����]��
//
//========================================================
#ifndef _SHADOW_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SHADOW_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object3d.h"

//�e�N���X
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = PRIORITY_3);			//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CShadow() override;									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void); //������
	void Uninit(void); //�I��
	void Update(void); //�X�V
	void Draw(void); //�`��
	const D3DXVECTOR3 GetPos(void) { return{}; }				//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return{}; }				//size�̎擾
	//�ÓI�����o�֐�
	static CShadow *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //����

private:
	//�����o�ϐ�
	bool m_bTexture;							//�e�N�X�`���̗L��
};

#endif