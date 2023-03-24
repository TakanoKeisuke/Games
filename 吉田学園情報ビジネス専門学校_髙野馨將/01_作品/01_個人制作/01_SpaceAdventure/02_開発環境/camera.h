//========================================================
//
//�J����
//Author:����]��
//
//========================================================
#ifndef _CAMERA_H_				//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�J�����N���X
class CCamera
{
public:
	CCamera();															//�R���X�g���N�^
	~CCamera();															//�f�X�g���N�^
	//�����o�֐�
	void Init(void);													//������
	void Uninit(void);													//�I��
	void Update(void);													//�X�V
	void TargetPlanet(void);											//�߂��̘f�������b�N�I������
	void SetCamera(void);												//�J�����̐ݒ�
	void SetPos(const D3DXVECTOR3 PosV, const D3DXVECTOR3 PosR);		//���_�A�����_�̐ݒ�
	void ShakeCamera(int nFrame, float fMagnitude);						//�J������h�炷
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//�����̐ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }							//�����̎擾
	CCamera *GetCamera(void){return m_camera;}							//�J�����̏��̎擾
	void StopShake(void);												//�h��̒�~

private:
	//�����o�ϐ�
	CCamera *m_camera;			//�J�����̏��
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_posVDest;		//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;		//�ړI�̒����_
	D3DXVECTOR3 m_rotDest;		//�ړI�̌���
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 posV;			//���[�J�����W�̎��_
	D3DXVECTOR3 posR;			//���[�J�����W�̒����_

	int m_nQuakeFrameCount;		//�J������h�炷�t���[����
	float m_fQuakeMagnitude;	//�h��̗�
	float m_fDistance;			//����
	bool m_bLock;				//�J�����̌Œ�
};
#endif