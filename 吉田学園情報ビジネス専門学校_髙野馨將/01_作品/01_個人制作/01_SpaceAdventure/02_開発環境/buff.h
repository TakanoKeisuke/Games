//=============================================================================
//
// buff.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _BUFF_H_
#define _BUFF_H_

#include "objectX.h"
#include "CylinderHitbox.h"

//強化アイテムクラス
class CBuff : public CObjectX
{
public:

	explicit CBuff(int nPriority = PRIORITY_3);		//コンストラクタ
	~CBuff() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static CBuff* Create(const D3DXVECTOR3 pos, CHitbox::INTERACTION_EFFECT effect);			//生成処理

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;						//ヒットボックス
	CHitbox::INTERACTION_EFFECT m_effect;			//強化効果

	bool m_bInvisible;
	int m_nInvincibleCnt;
};

#endif