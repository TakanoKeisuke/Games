//=============================================================================
//
// Sphere
// Author:髙野馨將
//
//=============================================================================
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "objectX.h"

//前方宣言
class CBoxHitbox;
class CCylinderHitbox;

//球クラス
class CSphere : public CObjectX
{
public:
	explicit CSphere(int nPriority = PRIORITY_3);					//オーバーライドされたコンストラクタ
	~CSphere() override;											//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;							//初期化
	virtual void CSphere::Uninit(void) override;					//終了
	virtual void Update(void) override;								//更新
	virtual void Draw(void) override;								//描画
	void Input(void);												//入力		
	//静的メンバ関数
	static CSphere *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, int nPriority); //生成

private:
	//メンバ変数
	CCylinderHitbox* m_pHitbox;					//ヒットボックス
	D3DXVECTOR3 m_rotDest;						//目的の角度
	D3DXVECTOR3 m_vecAxis;						//回転軸
	D3DXMATRIX m_mtxRot;						//回転マトリックス(保存用)
	D3DXQUATERNION m_quat;						//クォータニオン

	float m_fValueRot;							//回転角
	bool m_bModel;								//モデルの有無
};

#endif