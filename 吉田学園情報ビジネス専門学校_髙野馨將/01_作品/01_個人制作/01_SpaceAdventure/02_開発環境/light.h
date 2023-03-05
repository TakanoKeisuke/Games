//========================================================
//
//ライト
//Author:髙野馨將
//
//========================================================
#ifndef _LIGHT_H_				//このマクロ定義がされていなかったら
#define _LIGHT_H_				//二重インクルード防止のマクロ定義

#include "main.h"

//ライトクラス
class CLight
{
private:
	static const int MAX_LIGHT = 1;
public:
	CLight();													//コンストラクタ
	~CLight();													//デストラクタ
	//メンバ関数
	void Init();
	void Uninit();
	void Update();
	D3DLIGHT9 GetLight() { return m_aLight[0]; }

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//ライト情報
};

#endif