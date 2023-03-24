//=============================================================================
//
// ステージ処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"
#include "meshfield.h"
#include <vector>

//前方宣言
class CPlayer;
class CMeshField;
class CMesh_sphere;
class CSphere;
class CPlanet;
class CGoal;
class CSpike;
class CHeal;
class CLife_gauge;
class CRing;
class CBuff;
class CGimmick;
class CSecret_item;
class CCheckpoint;
class CItemFrame;

//ステージクラス
class CStage
{
public:
	//モデルの種類
	enum MODEL_TYPE
	{
		MODEL_SPIKE = 0,
		MODEL_RING,
		MODEL_HEAL,
		MODEL_SECRET,
		MODEL_PLANET,
		MODEL_MESH,
		MODEL_GOAL,
		MODEL_CHECK,
		MODEL_TYPE_MAX
	};
	//ギミックの種類
	enum GIMMICK_TYPE
	{
		GIMMICK_MOVE_X = 0,
		GIMMICK_MOVE_Y,
		GIMMICK_MOVE_Z,
		GIMMICK_FALL,
		GIMMICK_FALL_LONG,
		GIMMICK_TYPE_MAX
	};
	//アイテムの種類
	enum ITEM_TYPE
	{
		ITEM_SPEED = 0,
		ITEM_JUMP,
		ITEM_TYPE_MAX
	};

	static const int MAX_PLANET = 2;								//惑星の最大数
	static const int MAX_SECRET = 3;								//隠しアイテムの最大数
	static const int MAX_GIMMICK = 2;								//ギミックの最大数
	static const int MAX_BUFF = 2;									//強化アイテムの最大数
	static const int MAX_WORD = 1024;								//読み込む文字の最大数

	CStage();	//コンストラクタ
	~CStage();	//デストラクタ
	//メンバ関数
	HRESULT Init();		//初期化
	void Uninit();		//終了
	void Update();		//更新
	void Load(void);	//ステージの読み込み処理

	//静的メンバ関数
	static void SetModelType(int count,D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR2 block,CMeshField::MESH_TYPE meshtype, MODEL_TYPE type, GIMMICK_TYPE gimmick);	//モデルの設定												//モデル設定処理
	static void SetItemType(D3DXVECTOR3 pos, ITEM_TYPE type);															//アイテムの設定
	static void SetGimmickType(const D3DXVECTOR3 pos, const float range, const float speed, GIMMICK_TYPE type);							//ギミックの設定
	static CStage *Create();																							//ステージの生成

	//情報の取得
	static std::vector<CSecret_item*> GetSecret() { return m_pSecret; }
	static std::vector<CPlanet*> GetPlanet() { return m_pPlanet; }
	static std::vector<CRing*> GetRing() { return m_pRing; }
	static std::vector<CMeshField*> GetMesh() { return m_pMesh; }
	static std::vector<CSpike*> GetSpike() { return m_pSpike; }
	static std::vector<CHeal*> GetHeal() { return m_pHeal; }
	static std::vector<CGimmick*> GetGimmick() { return m_pGimmick; }
	static std::vector<CBuff*> GetBuff() { return m_pBuff; }
	static std::vector<CCheckpoint*> GetCheck() { return m_pCheck; }
	static std::vector<CGoal*> GetGoal() { return m_pGoal; }
	static CLife_gauge *GetLifeGage() { return m_pLife; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CSphere *GetSphere() { return m_pSphere; }
	static CMesh_sphere *GetMesh_sphere() { return m_pMesh_sphere; }

	//最大数
	static int m_nMaxMesh;
	static int m_nMaxRing;
	static int m_nMaxHeal;
	static int m_nMaxSpike;
	static int m_nMaxPlanet;
	static int m_nMaxSecret;
	static int m_nMaxGimmick;
	static int m_nMaxBuff;
	static int m_nMaxGoal;
	static int m_nMaxCheck;

private:
	//静的メンバ変数
	static std::vector<CRing*> m_pRing;
	static std::vector<CMeshField*> m_pMesh;
	static std::vector<CSpike*> m_pSpike;
	static std::vector<CHeal*> m_pHeal;
	static std::vector<CPlanet*> m_pPlanet;
	static std::vector<CSecret_item*> m_pSecret;
	static std::vector<CGimmick*> m_pGimmick;
	static std::vector<CBuff*> m_pBuff;
	static std::vector<CCheckpoint*> m_pCheck;
	static std::vector<CGoal*> m_pGoal;
	static CItemFrame *m_pFrame[MAX_SECRET];
	static CPlayer *m_pPlayer;
	static CSphere *m_pSphere;
	static CMesh_sphere *m_pMesh_sphere;
	static CLife_gauge *m_pLife;
};
#endif