//=============================================================================
//
// life_gauge.h
// Author:髙野馨將
//
//=============================================================================
#ifndef _LIFE_GAUGE_H_
#define _LIFE_GAUGE_H_

#include "object2D.h"

//HPゲージクラス
class CLife_gauge : public CObject2D
{
public:
	explicit CLife_gauge(int nPriority = PRIORITY_4);		//オーバーライドされたコンストラクタ
	~CLife_gauge() override;									//デストラクタ

	//メンバ関数
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw(void) override;							 //描画

	//静的メンバ関数
	static CLife_gauge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size); //生成

private:
	//メンバ変数
	LPDIRECT3DTEXTURE9	m_pTexture;				//テクスチャへのポインタ
};

#endif