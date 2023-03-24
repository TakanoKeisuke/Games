//========================================================
//
//影
//Author:髙野馨將
//
//========================================================
#ifndef _SHADOW_H_				//このマクロ定義がされていなかったら
#define _SHADOW_H_				//二重インクルード防止のマクロ定義

#include "object3d.h"

//影クラス
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = PRIORITY_3);			//オーバーライドされたコンストラクタ
	~CShadow() override;									//デストラクタ

	//メンバ関数
	HRESULT Init(void); //初期化
	void Uninit(void); //終了
	void Update(void); //更新
	void Draw(void); //描画
	const D3DXVECTOR3 GetPos(void) { return{}; }				//posの取得
	const D3DXVECTOR3 GetSize(void) { return{}; }				//sizeの取得
	//静的メンバ関数
	static CShadow *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //生成

private:
	//メンバ変数
	bool m_bTexture;							//テクスチャの有無
};

#endif