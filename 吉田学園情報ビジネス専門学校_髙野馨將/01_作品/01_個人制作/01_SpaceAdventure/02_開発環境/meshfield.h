//========================================================
//
//メッシュフィールド
//Author:髙野馨將
//
//========================================================
#ifndef _MESHFIELD_H_				//このマクロ定義がされていなかったら
#define _MESHFIELD_H_				//二重インクルード防止のマクロ定義

#include "object.h"

//メッシュフィールドクラス
class CMeshField : public CObject
{
public:
	enum MESH_TYPE
	{
		TYPE_NONE = 0,
		TYPE_X_UPPER,				//X方向に右肩上がり
		TYPE_X_LOWER,				//X方向に右肩下がり
		TYPE_Z_UPPER,				//Z方向に右肩上がり
		TYPE_Z_LOWER,				//Z方向に右肩下がり
		TYPE_ICE,					//滑る
		TYPE_MAX
	};

	explicit CMeshField(int nPriority = PRIORITY_3);			//オーバーライドされたコンストラクタ
	~CMeshField() override;										//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override; //初期化
	virtual void Uninit(void) override; //終了
	virtual void Update(void) override; //更新
	virtual void Draw(void) override; //描画
	
	const D3DXVECTOR3 GetPos(void) { return m_pos; }					//posの取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }					//sizeの取得
	void LoadTexture(const char *aFileName);							//テクスチャの設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//posの設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			//サイズの設定
	void Normal(void);													//法線の計算

	bool CMeshField::Collision(D3DXVECTOR3 *pos, float fRadius);		//当たり判定
	bool CMeshField::ShadowCollision(D3DXVECTOR3 *pos, float fRadius);		//当たり判定
	float GetFriction(void) { return m_fFriction; }						//摩擦係数の取得
	//静的メンバ関数
	static CMeshField *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR2 &block, MESH_TYPE type, int nPriority); //生成

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//インデックスバッファへのポインタ
	D3DXVECTOR3	m_pos;							//座標
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_size;							//大きさ
	D3DXVECTOR2 m_block;						//ブロック数
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	MESH_TYPE m_type;							//メッシュフィールドの向き
	float m_nVertex;							//バーテックス数
	float m_nIndex;								//インデックス数
	float m_nPrimitive;							//ポリゴン数
	float m_fFriction;							//摩擦係数
	bool m_bTexture;							//テクスチャの有無
};

#endif