//=============================================================================
//
// itemframe.h
// Author:髙野馨將
//
//=============================================================================
#ifndef _ITEMFRAME_H_
#define _ITEMFRAME_H_

#include "object2D.h"

//アイテムフレームクラス
class CItemFrame : public CObject2D
{
public:
	explicit CItemFrame(int nPriority = PRIORITY_4);		//オーバーライドされたコンストラクタ
	~CItemFrame() override;									//デストラクタ

	//メンバ関数
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw(void) override;							//描画

	void SetGetItem(bool bGet) { m_bGet = bGet; }		//取得の有無の設定
	//静的メンバ関数
	static CItemFrame *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//生成

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
	bool m_bGet;								//アイテムを入手しているかどうか
};

#endif