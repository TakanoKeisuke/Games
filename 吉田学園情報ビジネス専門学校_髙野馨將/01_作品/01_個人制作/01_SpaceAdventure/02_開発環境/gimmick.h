//=============================================================================
//
// gimmick.h
// Author : 髙野馨將
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "objectX.h"

//ギミッククラス
class CGimmick : public CObjectX
{
public:
	enum GIMMICK_TYPE
	{
		TYPE_NONE = 0,
		TYPE_MOVE_X,
		TYPE_MOVE_Y,
		TYPE_MOVE_Z,
		TYPE_FALL,
		TYPE_FALL_LONG,

		TYPE_MAX
	};
	explicit CGimmick(int nPriority = PRIORITY_3);		//コンストラクタ
	~CGimmick() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理
	void TypeEffect(void);								//種類ごとの処理

	bool PushPlayer(void);								//プレイヤーの押出処理
	bool GetLanding(void) { return m_bLanding; }		//着地しているかの取得

	void Fall(void);																									//落下処理
	void Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type);												//再生成処理
	static CGimmick* Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed);			//生成処理

private:
	//メンバ変数
	GIMMICK_TYPE m_type;								//ギミックの種類
	D3DXVECTOR3 OriginPos;								//最初のpos
	int m_nFallTime;									//落ちるまで時間
	int m_nRespawnTime;									//再生成時間
	int m_nInvincibleCnt;
	float m_fHeight;									//サインカーブの幅
	float m_fSpeed;										//速度
	float m_fRange;										//範囲
	float m_feffect;									//効果量の保存
	bool m_bCountStart;									//落ちるはじめるか
	bool m_bLanding;									//着地しているか
	bool m_bRespawn;									//落ちたら再生成する
};

#endif