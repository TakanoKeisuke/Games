//=============================================================================
//
// ���f��
// Author:����]��
//
//=============================================================================
#ifndef _CMODEL_H_
#define _CMODEL_H_

#include "object.h"

//���f���N���X
class CModel
{
public:
	CModel();								//�R���X�g���N�^
	~CModel();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);		//������
	void Uninit(void);		//�I��
	void Update(void);		//�X�V
	void Draw(void);		//�`��
	void Shadow(void);		//���ʓ��e

	void SetParent(CModel *pModel) { m_pParent = pModel; }				//�e�̐ݒ�
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }				//�ʒu�̐ݒ�
	void SetShadowPos(const D3DXVECTOR3 &pos) { m_ShadowPos = pos; }	//�e�̈ʒu�̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }				//�p�x�̐ݒ�
	void SetId(const int nId) { m_nMatId = nId; }						//�ԍ��̐ݒ�

	D3DXVECTOR3 GetPos(void) { return m_pos; }							//pos�̎擾
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }					//���[���h�}�g���b�N�X�̎擾
	D3DXVECTOR3 GetShadowPos(void) { return m_Shadow; }					//�e�̈ʒu�̎擾

	//�ÓI�����o�֐�
	void SetMatrix(D3DXMATRIX *mtx) { m_mtxWorld = *mtx; }
	void SetModel(const char *pFileName);
	static CModel *Create(const D3DXVECTOR3 &pos); //����

private:
	//�����o�ϐ�
	CModel *m_pParent;							//�e���f���ւ̃|�C���^
	D3DXVECTOR3	m_pos;							//���f���̍��W
	D3DXVECTOR3	m_ShadowPos;					//�e�̍��W
	D3DXVECTOR3	m_Shadow;						//�e�̍��W
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxShadow;						//�e�̃}�g���b�N�X
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	LPD3DXMESH m_MeshModel;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_BuffMatModel;				//�}�e���A�����ւ̃|�C���^
	DWORD m_NumMatModel;						//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9 *m_pTexture;				//�e�N�X�`���|�C���^
	bool m_bModel;								//���f���̗L��
	int m_nMatId;								//�}�e���A���̔ԍ�
};

#endif