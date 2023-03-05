//=============================================================================
//
// checkpoint.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _CHECKPOINT_H_
#define _CHECKPOINT_H_

#include "objectX.h"

//前方宣言
class CCylinderHitbox;

//中継地点クラス
class CCheckpoint : public CObjectX
{
public:
	explicit CCheckpoint(int nPriority = PRIORITY_3);		//コンストラクタ
	~CCheckpoint() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static CCheckpoint* Create(D3DXVECTOR3 pos);			//生成処理

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;						//ヒットボックス
};

#endif