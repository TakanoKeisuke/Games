//======================================================
//
//mesh_sphere.h
//Author : 髙野馨將
//
//======================================================
#ifndef  _MESH_SPHERE_H_				//このマクロ定義がされてなかったら
#define  _MESH_SPHERE_H_				//二重インクルード防止のマクロ定義

#include "object.h"
#include "meshfield.h"
#include <vector>

//マクロ定義
#define HALFSPHEAR_X_BLOCK	(15)							//X方向のブロック数
#define HALFSPHEAR_Z_BLOCK	(15)							//Z方向のブロック数

#define MAX_SPHERE	(1)

#define HALFSPHEAR_VERTEX_NUM	((HALFSPHEAR_X_BLOCK + 1) * (HALFSPHEAR_Z_BLOCK + 1))
#define HALFSPHEAR_INDEXNUM		((HALFSPHEAR_X_BLOCK + 1) * 2 * HALFSPHEAR_Z_BLOCK + (HALFSPHEAR_Z_BLOCK - 1) * 2)
#define HALFSPHEAR_PRIMITIVE_NUM	(HALFSPHEAR_X_BLOCK * (HALFSPHEAR_Z_BLOCK * 2) + (HALFSPHEAR_Z_BLOCK - 1) * 4)

//メッシュスフィア宣言
class CMesh_sphere : public CMeshField
{
public:
	enum SPHERE_TEX
	{
		SPHERE_UP = 0,
		SPHERE_DOWN,
		SPHERE_MAX
	};

	CMesh_sphere(const int nPriority);					//コンストラクタ
	~CMesh_sphere() override;

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理
	void Draw(void) override;		//描画処理

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//位置の設定処理
	void SetSize(const D3DXVECTOR3 size) { m_size = size; }				//サイズの設定
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//角度の設定
	void SetTex(const SPHERE_TEX tex) { m_tex = tex; }					//テクスチャ座標の設定

	const D3DXVECTOR3 GetSize(void) override { return  m_size; }		//サイズの取得
	const D3DXVECTOR3 GetPos(void) override { return  m_pos; }			//位置の取得
	const D3DXVECTOR3 GetRot(void) { return  m_rot; }					//角度の取得

	void Normal(void);													//法線の計算
	static CMesh_sphere* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, SPHERE_TEX tex);		//生成処理

	void BindTexture(LPDIRECT3DTEXTURE9	pTexture) { m_pTexture = pTexture; }		//テクスチャを代入
	void LoadTexture(const char *aFileName);										//テクスチャの読み込み
	bool CMesh_sphere::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);				//当たり判定

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	SPHERE_TEX m_tex;						//テクスチャ座標の計算に使う
};

#endif
