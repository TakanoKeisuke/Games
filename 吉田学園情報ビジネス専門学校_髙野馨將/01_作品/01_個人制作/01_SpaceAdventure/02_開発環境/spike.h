//=============================================================================
//
// Spike.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _SPIKE_H_
#define _SPIKE_H_

#include "objectX.h"
#include "gimmick.h"

//前方宣言
class CCylinderHitbox;

//障害物クラス
class CSpike : public CObjectX
{
public:
	explicit CSpike(int nPriority = PRIORITY_3);		//コンストラクタ
	~CSpike() override;									//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理
	//静的メンバ関数
	static CSpike *Create(const D3DXVECTOR3 pos, CGimmick::GIMMICK_TYPE type, int range);		//生成処理

private:
	//メンバ変数
	CCylinderHitbox *m_pHitbox;							//ヒットボックス
	CGimmick::GIMMICK_TYPE m_type;						//棘の種類
	float m_fHeight;									//サインカーブの幅
	float m_fRange;										//動く幅
};

#endif