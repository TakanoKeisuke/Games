//============================================
//
//	particle.h
//	Author: saito shian TAKANO KEISUKE
//
//============================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//�C���N���[�h
#include "main.h"
#include "object.h"

//�p�[�e�B�N���N���X
class CParticle : public CObject
{
public:

	enum PARTICLETYPE
	{
		PARTICLETYPE_FIRE = 0,		//�R���Ă�p�[�e�B�N��
		PARTICLETYPE_FOUNTAIN,		//�����p�[�e�B�N��
		PARTICLETYPE_SPLINTER		//�j�Ѓp�[�e�B�N��
	};

	explicit CParticle(int nPriority = PRIORITY_5);										//�R���X�g���N�^
	~CParticle()override;								//�f�X�g���N�^

	virtual HRESULT Init(void)override;							//�p�[�e�B�N���̏���������
	virtual void Uninit(void)override;							//�p�[�e�B�N���̏I������
	virtual void Update(void)override;							//�p�[�e�B�N���̍X�V����
	virtual void Draw(void)override;							//�p�[�e�B�N���̕`�揈��

	CParticle *SetTexture(char *pFile);					//�e�N�X�`���̐ݒ�

	void SetPos(const D3DXVECTOR3 pos);									//�p�[�e�B�N���̈ʒu����
	void SetSize(D3DXVECTOR3 size);										//�p�[�e�B�N���̃T�C�Y�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						//�p�[�e�B�N���̉�]����
	void SetMove(D3DXVECTOR3 move) { m_move = move; }					//�p�[�e�B�N���̈ړ�����
	void SetLength(float length) { length; }							//�����̐ݒ菈��
	void SetParticle(D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//�p�[�e�B�N���̐ݒ菈��
	void SetParticleType(PARTICLETYPE type);							//�p�[�e�B�N���̎�ނ̐ݒ�

	const D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�̎擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }			//�ړ��ʂ̎擾
	const D3DXVECTOR3 GetSize(void) { return m_size; }		//�T�C�Y�̎擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//��]�̎擾
	float GetLength(void) { return float(); }				//�g��k���̃X�P�[���̎擾

	static CParticle *CParticle::Create(PARTICLETYPE type, D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_rot;						//����
	D3DXCOLOR m_col;						//�F

	PARTICLETYPE m_type;					//�p�[�e�B�N���̎��

	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	int m_nLife;							//�̗�
	float m_Radius;							//���a
};

#endif
