//=============================================================================
//
// hitbox.h
// Author : 髙野馨將 Ricci Alex
//
//=============================================================================
#ifndef _CYLINDER_HITBOX_H_
#define _CYLINDER_HITBOX_H_

#include "hitbox.h"

//円柱の当たり判定のクラス
class CCylinderHitbox : public CHitbox
{
public:
	CCylinderHitbox();						//コンストラクタ
	~CCylinderHitbox() override;			//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void    Uninit(void) override;			//終了処理
	void    Update(void) override;			//更新処理

	//生成処理
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CCylinderHitbox *Hitbox);
private:

	bool CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect);							//円柱と円柱の当たり判定
	//bool CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);		//円柱と矩形の当たり判定
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);				//点と矩形の当たり判定
};

#endif