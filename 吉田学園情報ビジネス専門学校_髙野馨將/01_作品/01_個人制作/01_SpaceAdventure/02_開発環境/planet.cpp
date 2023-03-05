//======================================================
//
//planet.cpp
//Author:髙野馨將
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include <assert.h>
#include "planet.h"
#include "mesh_sphere.h"

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CPlanet::CPlanet(int nPriority) : CMesh_sphere(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CPlanet::~CPlanet()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CPlanet::Init(void)
{
	//初期化
	CMesh_sphere::Init();
	m_binside = false;

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CPlanet::Uninit(void)
{
	//終了処理
	CMesh_sphere::Uninit();
}

//======================================================
//更新処理
//======================================================
void CPlanet::Update(void)
{
}

//======================================================
//引力の設定
//======================================================
bool CPlanet::SetGravity(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove)
{
	//情報の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize() + D3DXVECTOR3(20.0f,20.0f,20.0f);
	D3DXVECTOR3 posTarget = *pPos;
	D3DXVECTOR3 sizeTarget = *pSize;
	//内側に入っていない
	m_binside = false;

	// 判定を行う距離を算出
	float fJudgeDistance = sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y) + (sizeTarget.z * sizeTarget.z));
	fJudgeDistance += sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	
	//お互いの位置の差を算出
	D3DXVECTOR3 sub = posTarget - pos;
	float fDistance = sqrtf((sub.x * sub.x) + (sub.y * sub.y) + (sub.z * sub.z));

	if (fDistance < fJudgeDistance)
	{
		//引力の方向
		D3DXVec3Normalize(&sub, &sub);
		sub *= -1.5f;

		//重力の加算
		pMove->x += sub.x;
		pMove->y += sub.y;
		pMove->z += sub.z;

		//内側に入っている
		m_binside = true;
	}

	return m_binside;
}

//======================================================
//当たり判定処理
//======================================================
bool CPlanet::CollisionSphere(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize)
{
	//変数宣言
	bool bCollision = false;

	//目標の情報取得
	D3DXVECTOR3 pos = *pPos;
	D3DXVECTOR3 size = *pSize / 2.0f;

	//自分の情報を取得する
	D3DXVECTOR3 posTarget  = GetPos();
	D3DXVECTOR3 sizeTarget = GetSize() / 2.0f;

	//判定を行う距離を算出
	float fJudgeDistance = sqrtf((size.x * size.x) + (size.y * size.y) + (size.z * size.z));
	fJudgeDistance += sqrtf((sizeTarget.x * sizeTarget.x) + (sizeTarget.y * sizeTarget.y) + (sizeTarget.z * sizeTarget.z));

	// お互いの位置の差を算出
	D3DXVECTOR3 distance = posTarget - pos;
	float fDistance = sqrtf((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));

	if (fDistance <= fJudgeDistance)
	{//位置の差が判定を行う距離より短い場合
		bCollision = true;
		//角度の算出
		D3DXVECTOR3 rotDiff;
		rotDiff.y = atan2f(distance.x, distance.z);
		rotDiff.x = atan2f(sqrtf((distance.x * distance.x) + (distance.z * distance.z)), distance.y);
		rotDiff.z = 0.0f;

		//位置の算出
		pPos->z = posTarget.z - sinf(rotDiff.x) * cosf(rotDiff.y) * fJudgeDistance;
		pPos->x = posTarget.x - sinf(rotDiff.x) * sinf(rotDiff.y) * fJudgeDistance;
		pPos->y = posTarget.y - cosf(rotDiff.x) * fJudgeDistance;
	}

	return bCollision;
}

//======================================================
//目標との距離を算出する処理
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
//生成処理
//======================================================
CPlanet *CPlanet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//動的確保
	CPlanet *pPlanet = new CPlanet;

	if (pPlanet != nullptr)
	{
		//初期化
		pPlanet->SetSize(size);
		pPlanet->SetPos(pos);
		pPlanet->SetRot(rot);
		pPlanet->SetTex(SPHERE_MAX);
		pPlanet->Init();
	}

	return pPlanet;
}