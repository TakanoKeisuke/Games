//=============================================================================
//
// ring.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _RING_H_
#define _RING_H_

#include "objectX.h"

//前方宣言
class CSphereHitbox;

//移動クラス
class CRing : public CObjectX
{
public:
	explicit CRing(int nPriority = PRIORITY_3);		//コンストラクタ
	~CRing() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	static CRing* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);			//生成処理

private:
	//メンバ変数
	CSphereHitbox* m_pHitbox;					//ヒットボックス
};

#endif