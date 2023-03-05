//=============================================================================
//
// モデル
// Author:髙野馨將
//
//=============================================================================
#ifndef _CMODEL_H_
#define _CMODEL_H_

#include "object.h"

//モデルクラス
class CModel
{
public:
	CModel();								//コンストラクタ
	~CModel();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画
	void Shadow(void);		//平面投影

	void SetParent(CModel *pModel) { m_pParent = pModel; }				//親の設定
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }				//位置の設定
	void SetShadowPos(const D3DXVECTOR3 &pos) { m_ShadowPos = pos; }	//影の位置の設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }				//角度の設定
	void SetId(const int nId) { m_nMatId = nId; }						//番号の設定

	D3DXVECTOR3 GetPos(void) { return m_pos; }							//posの取得
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }					//ワールドマトリックスの取得
	D3DXVECTOR3 GetShadowPos(void) { return m_Shadow; }					//影の位置の取得

	//静的メンバ関数
	void SetMatrix(D3DXMATRIX *mtx) { m_mtxWorld = *mtx; }
	void SetModel(const char *pFileName);
	static CModel *Create(const D3DXVECTOR3 &pos); //生成

private:
	//メンバ変数
	CModel *m_pParent;							//親モデルへのポインタ
	D3DXVECTOR3	m_pos;							//モデルの座標
	D3DXVECTOR3	m_ShadowPos;					//影の座標
	D3DXVECTOR3	m_Shadow;						//影の座標
	D3DXVECTOR3 m_rot;							//向き
	D3DXMATRIX m_mtxShadow;						//影のマトリックス
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	LPD3DXMESH m_MeshModel;						//メッシュ情報へのポインタ
	LPD3DXBUFFER m_BuffMatModel;				//マテリアル情報へのポインタ
	DWORD m_NumMatModel;						//マテリアル情報の数
	LPDIRECT3DTEXTURE9 *m_pTexture;				//テクスチャポインタ
	bool m_bModel;								//モデルの有無
	int m_nMatId;								//マテリアルの番号
};

#endif