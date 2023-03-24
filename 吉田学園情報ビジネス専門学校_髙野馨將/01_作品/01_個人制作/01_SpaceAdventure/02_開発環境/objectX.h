//=============================================================================
//
// オブジェクト3D
// Author:髙野馨將
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "object.h"

//オブジェクトクラス
class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = PRIORITY_3);						//オーバーライドされたコンストラクタ
	~CObjectX() override;												//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;								//初期化
	virtual void Uninit(void) override;									//終了
	virtual void Update(void) override;									//更新
	virtual void Draw(void) override;									//描画
	virtual void DrawSphere();											//描画
	void Shadow(void);													//平面投影
	bool CollisionMesh(const D3DXVECTOR3 pos,const D3DXVECTOR3 size);	//メッシュフィールドとの当たり判定

	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }					//位置の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			//大きさの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }				//角度の設定
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }			//移動量の設定
	void SetRotation(const D3DXVECTOR3 &rotation) { m_rotation = rotation; }			//回転量の設定
	void SetWorldMatrix(const D3DXMATRIX &mtxWorld) { m_mtxWorld = mtxWorld; }			//ワールドマトリックスの取得

	const D3DXVECTOR3 GetPos(void) { return m_pos; }					//位置の取得
	const D3DXVECTOR3 GetSize(void) { return m_size; }					//大きさの取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }							//角度の取得
	D3DXVECTOR3 GetMove(void) { return m_move; }						//移動量の取得
	D3DXMATRIX  GetWorldMatrix(void) { return m_mtxWorld; }				//ワールドマトリックスのの取得
	void CObjectX::LoadModel(const char *aFileName);					//モデルの設定
	//静的メンバ関数
	static CObjectX *Create(const D3DXVECTOR3 &pos, int nPriority);		//生成

private:
	//メンバ変数
	D3DXVECTOR3	m_pos;							//モデルの座標
	D3DXVECTOR3	m_ShadowPos;					//影の座標
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_size;							//サイズ
	D3DXVECTOR3 m_move;							//移動量
	D3DXVECTOR3 m_Min;							//最小値
	D3DXVECTOR3 m_Max;							//最大値
	D3DXVECTOR3 m_rotation;						//回転量
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	LPD3DXMESH m_MeshModel;						//メッシュ情報へのポインタ
	LPD3DXBUFFER m_BuffMatModel;				//マテリアル情報へのポインタ
	DWORD m_NumMatModel;						//マテリアル情報の数
	bool m_bModel;								//モデルの有無
	bool m_bCollision;							//当たり判定
};

#endif