//=============================================================================
//
// secret_item.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _SECRET_ITEM_H_
#define _SECRET_ITEM_H_

#include "objectX.h"

//前方宣言
class CCylinderHitbox;

//隠しアイテムクラス
class CSecret_item : public CObjectX
{
public:
	explicit CSecret_item(int nPriority = PRIORITY_3);			//コンストラクタ
	~CSecret_item() override;									//デストラクタ

	HRESULT Init(void) override;								//初期化処理
	void Uninit(void) override;									//終了処理
	void Update(void) override;									//更新処理
	void Draw(void) override;									//描画処理

	bool GetCollision(void) { return m_bCollision; }			//情報の取得

	static CSecret_item* Create(D3DXVECTOR3 pos,int number);	//生成処理

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;						//ヒットボックス
	int m_nNumber;
	bool m_bCollision;
};

#endif