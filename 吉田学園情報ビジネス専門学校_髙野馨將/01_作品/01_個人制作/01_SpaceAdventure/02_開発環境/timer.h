//=============================================================================
//
// timer.h
// Author:����]��
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "object2D.h"

//�O���錾
class CNumber;

//�^�C�}�[�N���X
class CTimer : public CObject2D
{
public:
	const static int MAX_TIMER = 3;

	explicit CTimer(int nPriority = PRIORITY_4);		//�I�[�o�[���C�h���ꂽ�R���X�g���N�^
	~CTimer() override;									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw(void) override;							//�`��

	void SetTimer(int nTimer);									//�^�C�}�[�̐ݒ�
	void SubTimer(int nValue) { SetTimer(m_nTimer - nValue); }  //�^�C�}�[�̉��Z����
	int GetTimer(void) { return m_nTimer; }						//�^�C�}�[�̎擾
	//�ÓI�����o�֐�
	static CTimer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//����

private:
	//�����o�ϐ�
	CNumber *m_apNumber[MAX_TIMER];				//Number�^�̔z��
	int m_nTimer;								//�^�C�}�[�̒l
	int m_nCntTimer;							//�^�C�}�[�̃J�E���g
};

#endif