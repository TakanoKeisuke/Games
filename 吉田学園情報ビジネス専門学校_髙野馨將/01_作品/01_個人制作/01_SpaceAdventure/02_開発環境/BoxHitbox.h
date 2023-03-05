//=============================================================================
//
// BoxHitbox.h
// Author : 髙野馨將 Ricci Alex
//
//=============================================================================
#ifndef _BOX_HITBOX_H_
#define _BOX_HITBOX_H_

#include "hitbox.h"

//矩形の当たり判定のクラス
class CBoxHitbox : public CHitbox
{
public:
	CBoxHitbox();										//コンストラクタ
	~CBoxHitbox() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void    Uninit(void) override;						//終了処理
	void    Update(void) override;						//更新処理

	//静的メンバ関数
	//生成処理
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect);
	static void CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent,CBoxHitbox* Hitbox);
private:

	bool BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);					//当たり判定
};

#endif