//========================================================
//
//�r���{�[�h
//Author:����]��
//
//========================================================
#ifndef _BILLBOARD_H_				//���̃}�N����`������Ă��Ȃ�������
#define _BILLBOARD_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//�r���{�[�h�N���X
class CBillboard : public CObject
{
public:
	explicit CBillboard(int nPriority = PRIORITY_3);			//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CBillboard() override;										//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override; //������
	virtual void Uninit(void) override; //�I��
	virtual void Update(void) override; //�X�V
	virtual void Draw(void) override; //�`��
	void LoadTexture(const char *aFileName);						//�e�N�X�`���̐ݒ�
	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//size�̎擾
	const D3DXCOLOR GetColor(void) { return m_color; }				//�J���[�̎擾
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//pos�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//�T�C�Y�̐ݒ�
	void SetCol(D3DXCOLOR col) { m_color = col; }					//�J���[�̐ݒ�
	//�ÓI�����o�֐�
	static CBillboard *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //����

protected:
	void CBillboard::SetVtx(void);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;							//�|���S���̍��W
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_size;							//�|���S���̑傫��
	D3DXCOLOR m_color;							//�F
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	bool m_bTexture;							//�e�N�X�`���̗L��
};
#endif