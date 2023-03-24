//========================================================
//
//ビルボード
//Author:髙野馨將
//
//========================================================
#ifndef _BILLBOARD_H_				//このマクロ定義がされていなかったら
#define _BILLBOARD_H_				//二重インクルード防止のマクロ定義

#include "object.h"

//ビルボードクラス
class CBillboard : public CObject
{
public:
	explicit CBillboard(int nPriority = PRIORITY_3);			//オーバーライドされたコンストラクタ
	~CBillboard() override;										//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override; //初期化
	virtual void Uninit(void) override; //終了
	virtual void Update(void) override; //更新
	virtual void Draw(void) override; //描画
	void LoadTexture(const char *aFileName);						//テクスチャの設定
	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//posの取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//sizeの取得
	const D3DXCOLOR GetColor(void) { return m_color; }				//カラーの取得
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//posの設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//サイズの設定
	void SetCol(D3DXCOLOR col) { m_color = col; }					//カラーの設定
	//静的メンバ関数
	static CBillboard *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //生成

protected:
	void CBillboard::SetVtx(void);

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	D3DXVECTOR3	m_pos;							//ポリゴンの座標
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_size;							//ポリゴンの大きさ
	D3DXCOLOR m_color;							//色
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	bool m_bTexture;							//テクスチャの有無
};
#endif