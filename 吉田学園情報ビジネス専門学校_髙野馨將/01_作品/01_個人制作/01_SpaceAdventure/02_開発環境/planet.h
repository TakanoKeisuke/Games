//======================================================
//
//planet.h
//Author : 髙野馨將
//
//======================================================
#ifndef  _PLANET_H_				//このマクロ定義がされてなかったら
#define  _PLANET_H_				//二重インクルード防止のマクロ定義

#include "object.h"
#include "mesh_sphere.h"
#include <vector>

//惑星クラス
class CPlanet : public CMesh_sphere
{
public:
	CPlanet(int nPriority = 3);			//コンストラクタ
	~CPlanet() override;

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	bool SetGravity(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);					//引力の設定
	bool GetInside(void) { return m_binside; }								//当たり判定の取得
	bool CollisionSphere(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pSize);			//円の当たり判定
	float TargetDistance(CObject *pTarget);									//目標との距離の算出

	static CPlanet *CPlanet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	bool m_binside;						//内側にいるかどうか
};

#endif
