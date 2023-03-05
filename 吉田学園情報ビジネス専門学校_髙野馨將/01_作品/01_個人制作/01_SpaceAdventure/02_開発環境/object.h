//=============================================================================
//
// オブジェクト
// Author:髙野馨將
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

//オブジェクトクラス
class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,	//タイプなし
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_MODEL,		//モデル
		OBJTYPE_MODE,		//モード
		OBJTYPE_BOSS,		//ボス
		OBJTYPE_MAX
	};

	enum EPriority
	{
		PRIORITY_1 = 0,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_MAX
	};

	explicit CObject(int nPriority = PRIORITY_3);		//オーバーライドされたコンストラクタ
	virtual ~CObject();									//デストラクタ

	//純粋仮想関数
	virtual HRESULT Init() = 0;							//初期化
	virtual void Uninit() = 0;							//終了
	virtual void Update() = 0;							//更新
	virtual void Draw() = 0;							//描画
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//位置の設定
	virtual const D3DXVECTOR3 GetSize(void) = 0;		//サイズの取得
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//位置の取得

	//静的メンバ関数
	static void ReleaseMode();
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static int Random(const int min, const int max) { return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)); }				//乱数を返す処理

	//メンバ関数
	void SetType(EObjType type) { m_type = type; }
	EObjType GetType() { return m_type; }
	void Flag() { m_bDeath = true; }
	void Break();

private:
	//静的メンバ変数
	static CObject *m_pTop[PRIORITY_MAX];					//先頭のオブジェクトへのポインタ
	static CObject *m_pCurrent[PRIORITY_MAX];				//現在(一番後ろ)のオブジェクトへのポインタ
	//メンバ変数
	int m_nPriority;										//優先順位
	bool m_bDeath;											//死亡フラグ
	EObjType m_type;
	D3DXVECTOR3 m_move;
	CObject *m_pPrev;										//前のオブジェクトへのポインタ
	CObject *m_pNext;										//次のオブジェクトへのポインタ
};

#endif;