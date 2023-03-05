//=============================================================================
//
// ゲーム処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

//前方宣言
class CStage;
class CPlayer;
class CEnemy;
class CMesh_sphere;
class CSphere;
class CLife_gauge;
class CItemFrame;
class CParticle;
class CTimer;
class CScore;

//ゲームクラス
class CGame : public CMode
{
public:
	static const int MAX_SECRET = 3;								//隠しアイテムの最大数
	static const int MAX_HALF_SPHERE = 2;							//半球の最大数
	static const int MAX_PARTICLE = 20;								//パーティクルの最大数

	CGame();	//コンストラクタ
	~CGame();	//デストラクタ
	//メンバ関数
	HRESULT Init();		//初期化
	void Uninit();		//終了
	void Update();		//更新
	void Draw();		//描画

	//静的メンバ関数
	static CGame *Create();									//ゲームの生成
	//情報の取得
	static CItemFrame *GetFrame(int nCnt) { return m_pFrame[nCnt]; }
	static CLife_gauge *GetLifeGage() { return m_pLife; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CParticle **GetParticle() { return m_pParticle; }
	static CSphere *GetSphere() { return m_pSphere; }
	static CTimer *GetTimer() { return m_pTimer; }
	static CEnemy *GetEnemy() { return m_pEnemy; }
	static CMesh_sphere *GetMesh_sphere(int nCnt) { return m_pMesh_sphere[nCnt]; }
	static CScore *GetScore() { return m_pScore; }

private:
	//静的メンバ変数
	static CItemFrame *m_pFrame[MAX_SECRET];
	static CPlayer *m_pPlayer;
	static CSphere *m_pSphere;
	static CMesh_sphere *m_pMesh_sphere[MAX_HALF_SPHERE];
	static CLife_gauge *m_pLife;
	static CParticle *m_pParticle[MAX_PARTICLE];
	static CTimer *m_pTimer;
	static CEnemy *m_pEnemy;
	static CScore *m_pScore;
	static CStage *m_pStage;
};
#endif