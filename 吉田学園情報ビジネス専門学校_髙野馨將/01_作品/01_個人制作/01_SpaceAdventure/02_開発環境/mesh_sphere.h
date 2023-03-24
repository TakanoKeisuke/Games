//======================================================
//
//mesh_sphere.h
//Author : ����]��
//
//======================================================
#ifndef  _MESH_SPHERE_H_				//���̃}�N����`������ĂȂ�������
#define  _MESH_SPHERE_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include "meshfield.h"
#include <vector>

//�}�N����`
#define HALFSPHEAR_X_BLOCK	(15)							//X�����̃u���b�N��
#define HALFSPHEAR_Z_BLOCK	(15)							//Z�����̃u���b�N��

#define MAX_SPHERE	(1)

#define HALFSPHEAR_VERTEX_NUM	((HALFSPHEAR_X_BLOCK + 1) * (HALFSPHEAR_Z_BLOCK + 1))
#define HALFSPHEAR_INDEXNUM		((HALFSPHEAR_X_BLOCK + 1) * 2 * HALFSPHEAR_Z_BLOCK + (HALFSPHEAR_Z_BLOCK - 1) * 2)
#define HALFSPHEAR_PRIMITIVE_NUM	(HALFSPHEAR_X_BLOCK * (HALFSPHEAR_Z_BLOCK * 2) + (HALFSPHEAR_Z_BLOCK - 1) * 4)

//���b�V���X�t�B�A�錾
class CMesh_sphere : public CMeshField
{
public:
	enum SPHERE_TEX
	{
		SPHERE_UP = 0,
		SPHERE_DOWN,
		SPHERE_MAX
	};

	CMesh_sphere(const int nPriority);					//�R���X�g���N�^
	~CMesh_sphere() override;

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����
	void Draw(void) override;		//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ菈��
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }				//�T�C�Y�̐ݒ�
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//�p�x�̐ݒ�
	void SetTex(const SPHERE_TEX tex) { m_tex = tex; }					//�e�N�X�`�����W�̐ݒ�

	const D3DXVECTOR3 GetSize(void) override { return  m_size; }		//�T�C�Y�̎擾
	const D3DXVECTOR3 GetPos(void) override { return  m_pos; }			//�ʒu�̎擾
	const D3DXVECTOR3 GetRot(void) { return  m_rot; }					//�p�x�̎擾

	void Normal(void);													//�@���̌v�Z
	static CMesh_sphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, SPHERE_TEX tex);		//��������

	void BindTexture(LPDIRECT3DTEXTURE9	pTexture) { m_pTexture = pTexture; }		//�e�N�X�`������
	void LoadTexture(const char *aFileName);										//�e�N�X�`���̓ǂݍ���
	bool CMesh_sphere::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);				//�����蔻��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	SPHERE_TEX m_tex;						//�e�N�X�`�����W�̌v�Z�Ɏg��
};

#endif
