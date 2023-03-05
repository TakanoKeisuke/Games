//========================================================
//
//���b�V���t�B�[���h
//Author:����]��
//
//========================================================
#ifndef _MESHFIELD_H_				//���̃}�N����`������Ă��Ȃ�������
#define _MESHFIELD_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//���b�V���t�B�[���h�N���X
class CMeshField : public CObject
{
public:
	enum MESH_TYPE
	{
		TYPE_NONE = 0,
		TYPE_X_UPPER,				//X�����ɉE���オ��
		TYPE_X_LOWER,				//X�����ɉE��������
		TYPE_Z_UPPER,				//Z�����ɉE���オ��
		TYPE_Z_LOWER,				//Z�����ɉE��������
		TYPE_ICE,					//����
		TYPE_MAX
	};

	explicit CMeshField(int nPriority = PRIORITY_3);			//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CMeshField() override;										//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override; //������
	virtual void Uninit(void) override; //�I��
	virtual void Update(void) override; //�X�V
	virtual void Draw(void) override; //�`��
	
	const D3DXVECTOR3 GetPos(void) { return m_pos; }					//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }					//size�̎擾
	void LoadTexture(const char *aFileName);							//�e�N�X�`���̐ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//pos�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			//�T�C�Y�̐ݒ�
	void Normal(void);													//�@���̌v�Z

	bool CMeshField::Collision(D3DXVECTOR3 *pos, float fRadius);		//�����蔻��
	bool CMeshField::ShadowCollision(D3DXVECTOR3 *pos, float fRadius);		//�����蔻��
	float GetFriction(void) { return m_fFriction; }						//���C�W���̎擾
	//�ÓI�����o�֐�
	static CMeshField *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR2 &block, MESH_TYPE type, int nPriority); //����

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;							//���W
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_size;							//�傫��
	D3DXVECTOR2 m_block;						//�u���b�N��
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	MESH_TYPE m_type;							//���b�V���t�B�[���h�̌���
	float m_nVertex;							//�o�[�e�b�N�X��
	float m_nIndex;								//�C���f�b�N�X��
	float m_nPrimitive;							//�|���S����
	float m_fFriction;							//���C�W��
	bool m_bTexture;							//�e�N�X�`���̗L��
};

#endif