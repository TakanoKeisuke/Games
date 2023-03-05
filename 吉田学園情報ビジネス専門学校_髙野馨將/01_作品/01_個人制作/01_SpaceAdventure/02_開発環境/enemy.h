//=============================================================================
//
// enemy.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "objectX.h"
#include "gimmick.h"

//前方宣言
class CCylinderHitbox;

//エネミークラス
class CEnemy : public CObjectX
{
public:
	explicit CEnemy(int nPriority = PRIORITY_3);		//コンストラクタ
	~CEnemy() override;									//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理
	void Chase(void);									//追尾処理
	//静的メンバ関数
	static CEnemy *Create(const D3DXVECTOR3 pos, int range);		//生成処理

private:
	//メンバ変数
	CCylinderHitbox *m_pHitbox;							//ヒットボックス
	CGimmick::GIMMICK_TYPE m_type;						//棘の種類
	float m_fHeight;									//サインカーブの幅
	float m_fRange;										//追ってくる範囲
};

#endif