//=============================================================================
//
// オブジェクト3D
// Author:髙野馨將
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

//====================================
//頂点座標[3D]の構造体を定義
//====================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ
}VERTEX_3D;

// 頂点フォーマット
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);    //座標・法線・カラー

//オブジェクトクラス
class CObject3D : public CObject
{
public:
	explicit CObject3D(int nPriority = PRIORITY_3);			//オーバーライドされたコンストラクタ
	~CObject3D() override;									//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override; //初期化
	virtual void Uninit(void) override; //終了
	virtual void Update(void) override; //更新
	virtual void Draw(void) override; //描画
	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//posの取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//sizeの取得
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	//テクスチャの取得
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//posの設定
	void SetSize(const D3DXVECTOR3 &size);										//サイズの設定
	void SetCol(D3DXCOLOR col);													//カラーの設定
	void SetTex(float BesideSplit, float nNumIndex);					//テクスチャ座標の確保
	void LoadTexture(const char *aFileName);							//テクスチャの設定
	 //静的メンバ関数
	static CObject3D *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //生成

protected:
	void CObject3D::SetVtx(void);

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;							//ポリゴンの座標
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_size;							//ポリゴンの大きさ
	D3DXCOLOR m_color;							//色
	D3DXMATRIX m_mtxWorldPolygon;				//ワールドマトリックス
	bool m_bTexture;							//テクスチャの有無
};

#endif