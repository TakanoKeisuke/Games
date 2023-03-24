//=============================================================================
//
// heal.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _HEAL_H_
#define _HEAL_H_

#include "objectX.h"

//前方宣言
class CCylinderHitbox;

//回復クラス
class CHeal : public CObjectX
{
public:
	explicit CHeal(int nPriority = PRIORITY_3);		//コンストラクタ
	~CHeal() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static CHeal* Create(D3DXVECTOR3 pos);			//生成処理

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;						//ヒットボックス
};

#endif