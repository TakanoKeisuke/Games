//=============================================================================
//
// �I�u�W�F�N�g3D
// Author:����]��
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"

//�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = PRIORITY_3);						//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CObjectX() override;												//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override;								//������
	virtual void Uninit(void) override;									//�I��
	virtual void Update(void) override;									//�X�V
	virtual void Draw(void) override;									//�`��
	virtual void DrawSphere();											//�`��
	void Shadow(void);													//���ʓ��e
	bool CollisionMesh(const D3DXVECTOR3 pos,const D3DXVECTOR3 size);	//���b�V���t�B�[���h�Ƃ̓����蔻��

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//�ʒu�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			//�傫���̐ݒ�
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }				//�p�x�̐ݒ�
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }			//�ړ��ʂ̐ݒ�
	void SetRotation(const D3DXVECTOR3 &rotation) { m_rotation = rotation; }			//��]�ʂ̐ݒ�
	void SetWorldMatrix(const D3DXMATRIX &mtxWorld) { m_mtxWorld = mtxWorld; }			//���[���h�}�g���b�N�X�̎擾

	const D3DXVECTOR3 GetPos(void) { return m_pos; }					//�ʒu�̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }					//�傫���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }							//�p�x�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; }						//�ړ��ʂ̎擾
	D3DXMATRIX  GetWorldMatrix(void) { return m_mtxWorld; }				//���[���h�}�g���b�N�X�̂̎擾
	void CObjectX::LoadModel(const char *aFileName);					//���f���̐ݒ�
	//�ÓI�����o�֐�
	static CObjectX *Create(const D3DXVECTOR3 &pos, int nPriority);		//����

private:
	//�����o�ϐ�
	D3DXVECTOR3	m_pos;							//���f���̍��W
	D3DXVECTOR3	m_ShadowPos;					//�e�̍��W
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_size;							//�T�C�Y
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXVECTOR3 m_Min;							//�ŏ��l
	D3DXVECTOR3 m_Max;							//�ő�l
	D3DXVECTOR3 m_rotation;						//��]��
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	LPD3DXMESH m_MeshModel;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_BuffMatModel;				//�}�e���A�����ւ̃|�C���^
	DWORD m_NumMatModel;						//�}�e���A�����̐�
	bool m_bModel;								//���f���̗L��
	bool m_bCollision;							//�����蔻��
};

#endif