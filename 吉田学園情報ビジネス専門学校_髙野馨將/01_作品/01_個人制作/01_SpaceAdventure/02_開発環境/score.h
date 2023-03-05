//=============================================================================
//
// �X�R�A����
// Author:����]��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "object2D.h"

//�}�N����`
#define MAX_SCORE    (8)        //�X�R�A�̌���

//�O���錾
class CNumber;

//�X�R�A�N���X
class CScore : public CObject2D
{
public:
	explicit CScore(int nPriority = PRIORITY_4);					//�R���X�g���N�^
	~CScore() override;			//�f�X�g���N�^

	HRESULT Init() override;    //����������
	void Uninit() override;     //�I������
	void Update() override;     //�X�V����
	void Draw() override;       //�`�揈��
	static CScore *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);    //�|���S���̐���

	void SetScore(int nScore);    //�X�R�A�̐ݒ菈��
	void AddScore(int nValue) { SetScore(m_nScore + nValue); }  //�X�R�A�̉��Z����
	int GetScore() { return m_nScore; }							//�X�R�A���̎擾����

private:
	CNumber *m_apNumber[MAX_SCORE];		//Number�^�̔z��
	int m_nScore;                       //�X�R�A�̒l
};
#endif