//=============================================================================
//
// �Q�[������
// Author:����]��
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

#include "object.h"

//�O���錾
class CTitle;
class CGame;
class CResult;
class CRanking;
class CTutorial;

//���[�h�N���X
class CMode : public CObject
{
public:
	CMode();			//�R���X�g���N�^
	~CMode() override;	//�f�X�g���N�^
	//���z�֐�
	virtual HRESULT Init() override { return S_OK; }	//������
	virtual void Uninit() override {}					//�I��
	virtual void Update() override {}					//�X�V
	virtual void Draw() override {}						//�`��
	void SetPos(const D3DXVECTOR3 pos) { pos; }		//�ʒu�̐ݒ�
	const D3DXVECTOR3 GetPos(void) { return{}; }				//pos�̎擾
	const D3DXVECTOR3 GetSize(void) { return{}; }				//size�̎擾
	
private:
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CRanking *m_pRanking;
};

#endif