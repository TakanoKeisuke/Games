//=============================================================================
//
// �I�u�W�F�N�g2D
// Author:����]��
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"

// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

//=============================================================================
// �\���̒�`
//=============================================================================

// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//�I�u�W�F�N�g�N���X
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = PRIORITY_3);			//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CObject2D() override;									//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) override; //������
	virtual void Uninit(void) override; //�I��
	virtual void Update(void) override; //�X�V
	virtual void Draw(void) override; //�`��
	const D3DXVECTOR3 GetPos(void) { return m_pos; }						//pos�̒l���擾����
	const D3DXVECTOR3 GetSize(void) { return m_size; }						//�T�C�Y�̏��擾
	const int GetLife(void) { return m_nLife; }								//���C�t�̏��擾
	const void SetLife(const int &life) { m_nLife = life; }					//���C�t�̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) {m_pTexture = pTexture; }	//�e�N�X�`���̎擾
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; ; }					//pos�̐ݒ�
	void SetLifePos(const D3DXVECTOR3 &pos, const float &size,const float &life);						//life�̐ݒ�
	void SetPlayerPos(const D3DXVECTOR3 &pos);						//PlayerPos�̐ݒ�
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//�T�C�Y�̐ݒ�
	bool Collision(const D3DXVECTOR3 &Destpos, const D3DXVECTOR3 &Destsize, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);
	void SetCol(D3DXCOLOR col);										//�J���[�̐ݒ�
	void CObject2D::SetTex(float BesideSplit, float nNumIndex);	//�e�N�X�`�����W�̊m��
	//�ÓI�����o�֐�
	static CObject2D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //����

protected:
	//�����o�֐�
	void SetVtx(void);
	
private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;							//�|���S���̍��W
	D3DXVECTOR3 m_size;							//�|���S���̑傫��
	int m_nLife;								//���C�t
};

#endif