//=============================================================================
//
// goal.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "objectX.h"

//前方宣言
class CCylinderHitbox;

//ゴールクラス
class CGoal : public CObjectX
{
public:
	explicit CGoal(int nPriority = PRIORITY_3);		//コンストラクタ
	~CGoal() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static CGoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//生成処理

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;					//ヒットボックス
};

#endif