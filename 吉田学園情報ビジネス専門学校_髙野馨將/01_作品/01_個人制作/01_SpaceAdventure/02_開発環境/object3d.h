//=============================================================================
//
// �I�u�W�F�N�g3D
// Author:����]��
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

//====================================
//���_���W[3D]�̍\���̂��`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
}VERTEX_3D;

// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);    //���W�E�@���E�J���[

//�I�u�W�F�N�g�N���X
class CObject3D : public CObject
{
public:
	explicit CObject3D(int nPriority = PRIORITY_3);			//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CObject3D() override;									//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override; //������
	virtual void Uninit(void) override; //�I��
	virtual void Update(void) override; //�X�V
	virtual void Draw(void) override; //�`��
	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//size�̎擾
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	//�e�N�X�`���̎擾
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//pos�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size);										//�T�C�Y�̐ݒ�
	void SetCol(D3DXCOLOR col);													//�J���[�̐ݒ�
	void SetTex(float BesideSplit, float nNumIndex);					//�e�N�X�`�����W�̊m��
	void LoadTexture(const char *aFileName);							//�e�N�X�`���̐ݒ�
	 //�ÓI�����o�֐�
	static CObject3D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //����

protected:
	void CObject3D::SetVtx(void);

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;							//�|���S���̍��W
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_size;							//�|���S���̑傫��
	D3DXCOLOR m_color;							//�F
	D3DXMATRIX m_mtxWorldPolygon;				//���[���h�}�g���b�N�X
	bool m_bTexture;							//�e�N�X�`���̗L��
};

#endif