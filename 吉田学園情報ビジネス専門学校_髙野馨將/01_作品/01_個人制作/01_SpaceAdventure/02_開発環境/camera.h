//========================================================
//
//カメラ
//Author:髙野馨將
//
//========================================================
#ifndef _CAMERA_H_				//このマクロ定義がされていなかったら
#define _CAMERA_H_				//二重インクルード防止のマクロ定義

#include "main.h"

//カメラクラス
class CCamera
{
public:
	CCamera();															//コンストラクタ
	~CCamera();															//デストラクタ
	//メンバ関数
	void Init(void);													//初期化
	void Uninit(void);													//終了
	void Update(void);													//更新
	void TargetPlanet(void);											//近くの惑星をロックオンする
	void SetCamera(void);												//カメラの設定
	void SetPos(const D3DXVECTOR3 PosV, const D3DXVECTOR3 PosR);		//視点、注視点の設定
	void ShakeCamera(int nFrame, float fMagnitude);						//カメラを揺らす
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//向きの設定
	D3DXVECTOR3 GetRot(void) { return m_rot; }							//向きの取得
	CCamera *GetCamera(void){return m_camera;}							//カメラの情報の取得
	void StopShake(void);												//揺れの停止

private:
	//メンバ変数
	CCamera *m_camera;			//カメラの情報
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_posVDest;		//目的の視点
	D3DXVECTOR3 m_posRDest;		//目的の注視点
	D3DXVECTOR3 m_rotDest;		//目的の向き
	D3DXVECTOR3 m_move;			//移動量
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;			//上方向ベクトル
	D3DXVECTOR3 posV;			//ローカル座標の視点
	D3DXVECTOR3 posR;			//ローカル座標の注視点

	int m_nQuakeFrameCount;		//カメラを揺らすフレーム数
	float m_fQuakeMagnitude;	//揺れの量
	float m_fDistance;			//距離
	bool m_bLock;				//カメラの固定
};
#endif