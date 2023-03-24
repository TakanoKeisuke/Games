//============================================
//
//	particle.h
//	Author: saito shian TAKANO KEISUKE
//
//============================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//インクルード
#include "main.h"
#include "object.h"

//パーティクルクラス
class CParticle : public CObject
{
public:

	enum PARTICLETYPE
	{
		PARTICLETYPE_FIRE = 0,		//燃えてるパーティクル
		PARTICLETYPE_FOUNTAIN,		//噴水パーティクル
		PARTICLETYPE_SPLINTER		//破片パーティクル
	};

	explicit CParticle(int nPriority = PRIORITY_5);										//コンストラクタ
	~CParticle()override;								//デストラクタ

	virtual HRESULT Init(void)override;							//パーティクルの初期化処理
	virtual void Uninit(void)override;							//パーティクルの終了処理
	virtual void Update(void)override;							//パーティクルの更新処理
	virtual void Draw(void)override;							//パーティクルの描画処理

	CParticle *SetTexture(char *pFile);					//テクスチャの設定

	void SetPos(const D3DXVECTOR3 pos);									//パーティクルの位置処理
	void SetSize(D3DXVECTOR3 size);										//パーティクルのサイズの設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						//パーティクルの回転処理
	void SetMove(D3DXVECTOR3 move) { m_move = move; }					//パーティクルの移動処理
	void SetLength(float length) { length; }							//長さの設定処理
	void SetParticle(D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//パーティクルの設定処理
	void SetParticleType(PARTICLETYPE type);							//パーティクルの種類の設定

	const D3DXVECTOR3 GetPos(void) { return m_pos; }		//位置の取得処理
	D3DXVECTOR3 GetMove(void) { return m_move; }			//移動量の取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }		//サイズの取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//回転の取得
	float GetLength(void) { return float(); }				//拡大縮小のスケールの取得

	static CParticle *CParticle::Create(PARTICLETYPE type, D3DXVECTOR3 pos, int life, D3DXCOLOR col);			//生成

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_rot;						//向き
	D3DXCOLOR m_col;						//色

	PARTICLETYPE m_type;					//パーティクルの種類

	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	int m_nLife;							//体力
	float m_Radius;							//半径
};

#endif
