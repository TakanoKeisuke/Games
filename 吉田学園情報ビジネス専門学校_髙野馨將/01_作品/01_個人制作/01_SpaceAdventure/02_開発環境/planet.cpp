//======================================================
//
//planet.cpp
//Author:����]��
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include <assert.h>
#include "planet.h"
#include "mesh_sphere.h"

//======================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//======================================================
CPlanet::CPlanet(int nPriority) : CMesh_sphere(nPriority)
{

}

//======================================================
//�f�X�g���N�^
//======================================================
CPlanet::~CPlanet()
{
}

//======================================================
//����������
//======================================================
HRESULT CPlanet::Init(void)
{
	//������
	CMesh_sphere::Init();
	m_binside = false;

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CPlanet::Uninit(void)
{
	//�I������
	CMesh_sphere::Uninit();
}

//======================================================
//�X�V����
//======================================================
void CPlanet::Update(void)
{
}

//======================================================
//���͂̐ݒ�
//======================================================
bool CPlanet::SetGravity(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove)
{
	//���̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize() + D3DXVECTOR3(20.0f,20.0f,20.0f);
	D3DXVECTOR3 posTarget = *pPos;
	D3DXVECTOR3 sizeTarget = *pSize;
	//�����ɓ����Ă��Ȃ�
	m_binside = false;

	// ������s���������Z�o
	float fJudgeDistance = sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y) + (sizeTarget.z * sizeTarget.z));
	fJudgeDistance += sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	
	//���݂��̈ʒu�̍����Z�o
	D3DXVECTOR3 sub = posTarget - pos;
	float fDistance = sqrtf((sub.x * sub.x) + (sub.y * sub.y) + (sub.z * sub.z));

	if (fDistance < fJudgeDistance)
	{
		//���͂̕���
		D3DXVec3Normalize(&sub, &sub);
		sub *= -1.5f;

		//�d�͂̉��Z
		pMove->x += sub.x;
		pMove->y += sub.y;
		pMove->z += sub.z;

		//�����ɓ����Ă���
		m_binside = true;
	}

	return m_binside;
}

//======================================================
//�����蔻�菈��
//======================================================
bool CPlanet::CollisionSphere(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize)
{
	//�ϐ��錾
	bool bCollision = false;

	//�ڕW�̏��擾
	D3DXVECTOR3 pos = *pPos;
	D3DXVECTOR3 size = *pSize / 2.0f;

	//�����̏����擾����
	D3DXVECTOR3 posTarget  = GetPos();
	D3DXVECTOR3 sizeTarget = GetSize() / 2.0f;

	//������s���������Z�o
	float fJudgeDistance = sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	fJudgeDistance += sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y) + (sizeTarget.z * sizeTarget.z));

	// ���݂��̈ʒu�̍����Z�o
	D3DXVECTOR3 distance = posTarget - pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));

	if (fDistance <= fJudgeDistance)
	{//�ʒu�̍���������s���������Z���ꍇ
		bCollision = true;
		//�p�x�̎Z�o
		D3DXVECTOR3 rotDiff;
		rotDiff.y = atan2f(distance.x, distance.z);
		rotDiff.x = atan2f(sqrtf((distance.x * distance.x) + (distance.z * distance.z)), distance.y);
		rotDiff.z = 0.0f;

		//�ʒu�̎Z�o
		pPos->z = posTarget.z - sinf(rotDiff.x) * cosf(rotDiff.y) * fJudgeDistance;
		pPos->x = posTarget.x - sinf(rotDiff.x) * sinf(rotDiff.y) * fJudgeDistance;
		pPos->y = posTarget.y - cosf(rotDiff.x) * fJudgeDistance;
	}

	return bCollision;
}

//======================================================
//�ڕW�Ƃ̋������Z�o���鏈��
//======================================================
float CPlanet::TargetDistance(CObject *pTarget)
{
	if (pTarget != nullptr)
	{
		D3DXVECTOR3 TargetPos = pTarget->GetPos();
		D3DXVECTOR3 dif = (TargetPos - GetPos());
		float fDistance = sqrtf((dif.x * dif.x) + (dif.y * dif.y) + (dif.z * dif.z));

		return fDistance;
	}

	return NULL;
}

//======================================================
//��������
//======================================================
CPlanet *CPlanet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//���I�m��
	CPlanet *pPlanet = new CPlanet;

	if (pPlanet != nullptr)
	{
		//������
		pPlanet->SetSize(size);
		pPlanet->SetPos(pos);
		pPlanet->SetRot(rot);
		pPlanet->SetTex(SPHERE_MAX);
		pPlanet->Init();
	}

	return pPlanet;
}