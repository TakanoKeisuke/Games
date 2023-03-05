//=============================================================================
//
// オブジェクト2D
// Author:髙野馨將
//
//=============================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"

// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

//=============================================================================
// 構造体定義
//=============================================================================

// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//オブジェクトクラス
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = PRIORITY_3);			//オーバーライドされたコンストラクタ
	~CObject2D() override;									//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override; //初期化
	virtual void Uninit(void) override; //終了
	virtual void Update(void) override; //更新
	virtual void Draw(void) override; //描画
	const D3DXVECTOR3 GetPos(void) { return m_pos; }						//posの値を取得する
	const D3DXVECTOR3 GetSize(void) { return m_size; }						//サイズの情報取得
	const int GetLife(void) { return m_nLife; }								//ライフの情報取得
	const void SetLife(const int &life) { m_nLife = life; }					//ライフの設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) {m_pTexture = pTexture; }	//テクスチャの取得
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; ; }					//posの設定
	void SetLifePos(const D3DXVECTOR3 &pos, const float &size,const float &life);						//lifeの設定
	void SetPlayerPos(const D3DXVECTOR3 &pos);						//PlayerPosの設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//サイズの設定
	bool Collision(const D3DXVECTOR3 &Destpos, const D3DXVECTOR3 &Destsize, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);
	void SetCol(D3DXCOLOR col);										//カラーの設定
	void CObject2D::SetTex(float BesideSplit, float nNumIndex);	//テクスチャ座標の確保
	//静的メンバ関数
	static CObject2D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //生成

protected:
	//メンバ関数
	void SetVtx(void);
	
private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;							//ポリゴンの座標
	D3DXVECTOR3 m_size;							//ポリゴンの大きさ
	int m_nLife;								//ライフ
};

#endif