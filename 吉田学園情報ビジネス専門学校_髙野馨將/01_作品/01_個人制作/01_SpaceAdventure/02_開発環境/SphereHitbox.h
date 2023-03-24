//=============================================================================
//
// spherehitbox.h
// Author : 髙野馨將 
//
//=============================================================================
#ifndef _SPHERE_HITBOX_H_
#define _SPHERE_HITBOX_H_

#include "hitbox.h"

//円柱の当たり判定のクラス
class CSphereHitbox : public CHitbox
{
public:
	CSphereHitbox();						//コンストラクタ
	~CSphereHitbox() override;				//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void    Uninit(void) override;			//終了処理
	void    Update(void) override;			//更新処理

	//生成処理
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CSphereHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CSphereHitbox *Hitbox);
private:

	bool SphereCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);		//円と円柱の当たり判定
	bool SphereSphereHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);			//円と円の当たり判定
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);					//点と矩形の当たり判定
};

#endif