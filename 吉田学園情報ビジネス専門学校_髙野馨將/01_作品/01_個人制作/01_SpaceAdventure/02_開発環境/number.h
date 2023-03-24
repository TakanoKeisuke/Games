//=============================================================================
//
// ナンバー処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

//マクロ定義
#define NUMBER_SIZE_X    (30.0f)        //ナンバー1つの幅
#define NUMBER_SIZE_Y    (60.0f)       //ナンバー1つの高さ

//ナンバークラス
class CNumber : public CObject2D
{
public:
	explicit CNumber(int nPriority = PRIORITY_4);            //コンストラクタ
	~CNumber();           //デストラクタ

	HRESULT Init() override;							//初期化処理
	void Uninit() override;								//終了処理
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 &size);      //生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture;     //共通テクスチャのポインタ
};
#endif