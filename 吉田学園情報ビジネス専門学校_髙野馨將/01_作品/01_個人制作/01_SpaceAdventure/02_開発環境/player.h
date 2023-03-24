//=============================================================================
//
// player
// Author:髙野馨將
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include<vector>

//前方宣言
class CModel;
class CBoxHitbox;
class CCylinderHitbox;
class CSphereHitbox;
class CMotion;
class CShadow;

//プレイヤークラス
class CPlayer : public CObject
{
public:
	enum PLAYER_TYPE
	{
		TYPE_NONE = 0,
		TYPE_SPEED,
		TYPE_JUMP,
		TYPE_FLY,

		TYPE_MAX
	};

	static const int MAX_MODEL = 9;								//モデルの最大数
	static const int MAX_WORD = 512;

	explicit CPlayer(int nPriority = PRIORITY_3);					//オーバーライドされたコンストラクタ
	~CPlayer() override;											//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;							//初期化
	virtual void CPlayer::Uninit(void) override;					//終了
	virtual void Update(void) override;								//更新
	virtual void Draw(void) override;								//描画
	void LoadPlayer(void);											//プレイヤーモデルの読み込み
	void Input(void);												//入力
	void CollisionObj(void);										//オブジェクトと当たった時の処理
	void CollisionStage(void);										//ステージの当たり判定
	void CollisionGimmick(void);									//影とギミックの当たり判定
	void Attack(void);												//攻撃処理
	void BuffPlayer(void);											//プレイヤーの強化処理

	void BuffEffect(PLAYER_TYPE type);								//強化効果処理
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//posの設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//sizeの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }			//rotの設定
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }		//moveの設定

	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//posの取得
	const D3DXVECTOR3 GetPosOld(void) { return m_posOld; }			//posの取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//sizeの取得
	const D3DXVECTOR3 GetMove(void) { return m_move; }				//moveの取得
	const int GetLife(void) { return m_nLife; }						//体力の取得
	bool GetInside(void) { return m_bInside; }						//当たり判定の取得
	bool GetShadow(void) { return m_bShadow; }						//影の取得
	CModel *GetModel(int nCnt) { return m_apModel[nCnt]; }			//モデルの取得
	CMotion *GetMotion() { return m_pMotion; }						//モーションの取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//rotの取得
	
	//静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority); //生成

private:
	//静的メンバ変数
	static float m_fAcceleration;				//加速係数
	static float m_fJump;						//ジャンプ力
	static int m_nGoalCnt;						//ゴールからフェード迄の時間

	//メンバ変数
	CModel *m_apModel[MAX_MODEL];				//モデルの情報
	CMotion *m_pMotion;							//モーションの情報
	CSphereHitbox *m_pHitbox;					//ヒットボックス
	CCylinderHitbox *m_pAttackHitbox;			//攻撃のヒットボックス
	D3DXQUATERNION m_quat;						//クォータニオン
	D3DXVECTOR3 m_Vec;							//進行方向ベクトル
	D3DXVECTOR3	m_pos;							//位置
	D3DXVECTOR3 m_posOld;						//前回の位置
	D3DXVECTOR3	m_Originpos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_size;							//サイズ
	D3DXVECTOR3 m_rotDest;						//目的の角度
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_vecAxis;						//軸ベクトル
	D3DXVECTOR3 m_norVec;						//法線ベクトル
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	D3DXMATRIX m_mtxQuat;						//クォータニオン
	PLAYER_TYPE m_type;							//プレイヤーの種類

	int m_nLife;								//体力
	int m_nCntModel;							//モデル数をカウント
	int m_nInvincibleCnt;						//無敵時間
	int m_nBuffTime;							//強化時間
	int m_nCntGoal;								//ゴール後フェードするまでの時間
	float m_fCntSE;								//SEのカウント
	float m_fCT;								//クールタイム
	float m_fFriction;							//摩擦係数
	float m_fBuffQuantity;						//強化効果の量
	float m_fDash;								//ダッシュ時速度
	float m_fSlowFall;							//落下速度低下
	std::vector<bool> m_bCollisionField;		//地面の当たり判定
	bool m_bGoal;								//ゴールしたか
	bool m_bGimmick;							//ギミックに乗っているか
	bool m_bJumping;							//ジャンプしているか
	bool m_bCollisionPlanet;					//惑星の当たり判定
	bool m_bInside;								//惑星の範囲の内側に入っているか
	bool m_bModel;								//モデルの有無
	bool m_bShadow;								//影の有無
};

#endif