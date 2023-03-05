//======================================================
//
//mesh_sphere.cpp
//Author : 髙野馨將
//
//======================================================
#include "application.h"
#include "mesh_sphere.h"
#include "object3d.h"
#include "debug.h"

//======================================================
//コンストラクタ
//======================================================
CMesh_sphere::CMesh_sphere(const int nPriority) : CMeshField(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
}

//======================================================
//デストラクタ
//======================================================
CMesh_sphere::~CMesh_sphere()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CMesh_sphere::Init(void)
{
	//初期化
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HALFSPHEAR_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * HALFSPHEAR_INDEXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点座標へのポインタ
	VERTEX_3D * pVtx = nullptr;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < HALFSPHEAR_Z_BLOCK + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < HALFSPHEAR_X_BLOCK + 1; nCntX++)
		{
			float fRot = (D3DX_PI * 2) / HALFSPHEAR_X_BLOCK * nCntX;
			float fHalfRot = (D3DX_PI) / HALFSPHEAR_Z_BLOCK * nCntZ;

			// 半径と、高さの計算
			float Radius = cosf(fHalfRot) * m_size.x;
			float Height = sinf(fHalfRot) * m_size.z;

			//頂点座標の設定
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.x = sinf(-fRot) * Radius;
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.z = cosf(-fRot) * Radius;
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.y = Height/* + 15.0f*/;

			//各頂点の法線の設定(ベクトルの大きさは1にする必要がある)
			pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラーの設定
			pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			switch (m_tex)
			{
			case CMesh_sphere::SPHERE_UP:
				//テクスチャ座標の設定
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * -nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * -nCntZ);
				break;

			case CMesh_sphere::SPHERE_DOWN:
				//テクスチャ座標の設定
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * nCntZ);
				break;

			case CMesh_sphere::SPHERE_MAX:
				//座標の設定
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.z = sinf(fHalfRot) * cosf(fRot) * -m_size.x;
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.x = sinf(fHalfRot) * sinf(fRot) * -m_size.x;
				pVtx[nCntX + (nCntZ * (HALFSPHEAR_X_BLOCK + 1))].pos.y = cosf(fHalfRot) * -m_size.x;
				//テクスチャ座標の設定
				pVtx[nCntX + (nCntZ *(HALFSPHEAR_X_BLOCK + 1))].tex = D3DXVECTOR2((1.0f / HALFSPHEAR_X_BLOCK) * nCntX, (1.0f / HALFSPHEAR_Z_BLOCK) * nCntZ);		
				break;

			default:
				break;
			}
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (int nCntZ = 0; nCntZ < HALFSPHEAR_Z_BLOCK; nCntZ++)
	{
		for (int nCntX = 0; nCntX < HALFSPHEAR_X_BLOCK + 1; nCntX++)
		{
			pIdx[0] = (WORD)((HALFSPHEAR_X_BLOCK + 1) + nCntX + nCntZ * (HALFSPHEAR_X_BLOCK + 1));
			pIdx[1] = (WORD)((HALFSPHEAR_X_BLOCK + 1) + nCntX + nCntZ * (HALFSPHEAR_X_BLOCK + 1) - (HALFSPHEAR_X_BLOCK + 1));

			pIdx += 2;
		}

		//縮退ポリゴン
		if (nCntZ < HALFSPHEAR_Z_BLOCK - 1)
		{
			pIdx[0] = (WORD)((HALFSPHEAR_X_BLOCK + 1)* nCntZ + HALFSPHEAR_X_BLOCK);
			pIdx[1] = (WORD)((HALFSPHEAR_X_BLOCK + 1) * (nCntZ + 2));

			pIdx += 2;
		}
	}
	//インデックスバッファの開放
	m_pIdxBuff->Unlock();

	//法線の計算
	Normal();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CMesh_sphere::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	//死亡フラグをtrueに
	Flag();
}

//======================================================
//更新処理
//======================================================
void CMesh_sphere::Update(void)
{
}

//======================================================
//描画処理
//======================================================
void CMesh_sphere::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//メッシュフィールドの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, HALFSPHEAR_VERTEX_NUM, 0, HALFSPHEAR_PRIMITIVE_NUM);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);

	//ライトを有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//======================================================
//法線の計算
//======================================================
void CMesh_sphere::Normal(void)
{
	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPolygon = 0; nCntPolygon < HALFSPHEAR_PRIMITIVE_NUM; nCntPolygon++)
	{
		// 変数宣言
		D3DXVECTOR3 Vtx[3] = {};
		D3DXVECTOR3 VtxLine[2] = {};

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			Vtx[nCnt] = pVtx[pIdx[nCntPolygon + nCnt]].pos;
		}

		if (Vtx[0] == Vtx[1]
			|| Vtx[0] == Vtx[2]
			|| Vtx[1] == Vtx[2])
		{// 縮退ポリゴンの場合
			continue;
		}

		// ポリゴンの辺ベクトル
		VtxLine[0] = Vtx[1] - Vtx[0];
		VtxLine[1] = Vtx[2] - Vtx[0];

		// 面法線ベクトル
		D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (nCntPolygon % 2 == 0)
		{// 面法線ベクトル(三次元の外積)
			D3DXVec3Cross(&norVec, &VtxLine[0], &VtxLine[1]);
		}
		else
		{// 面法線ベクトル(三次元の外積)
			D3DXVec3Cross(&norVec, &VtxLine[1], &VtxLine[0]);
		}

		//正規化
		D3DXVec3Normalize(&norVec, &norVec);

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			//法線ベクトルの加算
			pVtx[pIdx[nCntPolygon + nCnt]].nor += norVec;

			//正規化
			D3DXVec3Normalize(&pVtx[pIdx[nCntPolygon + nCnt]].nor, &pVtx[pIdx[nCntPolygon + nCnt]].nor);
		}

		// インデックスバッファのアンロック
		m_pIdxBuff->Unlock();

		// 頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	}
}

//======================================================
//生成処理
//======================================================
CMesh_sphere * CMesh_sphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, SPHERE_TEX tex)
{
	CMesh_sphere* pSphere = new CMesh_sphere(3);

	if (pSphere != nullptr)
	{
		pSphere->SetPos(pos);
		pSphere->SetSize(size);
		pSphere->SetRot(rot);
		pSphere->SetTex(tex);

		if (FAILED(pSphere->Init()))
		{
			return nullptr;
		}
	}

	return pSphere;
}

//======================================================
//テクスチャ読み込み処理
//======================================================
void CMesh_sphere::LoadTexture(const char * aFileName)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);
}

//======================================================
//当たり判定
//======================================================
bool CMesh_sphere::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	//当たり判定
	bool bCollison = false;

	//頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//対象のposの取得
	D3DXVECTOR3 posTarget = *pos;
	//計算用変数
	D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecLine[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecPos[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	float fInnerProduct[3] = { 0.0f };

	for (int nCntPolygon = 0; nCntPolygon < HALFSPHEAR_PRIMITIVE_NUM; nCntPolygon++)
	{
		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{//頂点座標の取得
			aVtx[nCntVtx] = pVtx[pIdx[nCntPolygon + nCntVtx]].pos;

			//ワールド座標にキャスト
			//変数宣言
			D3DXMATRIX        mtxWorldVtx;                //ワールドマトリックス
			D3DXMATRIX        mtxRot, mtxTrans;           //計算用マトリックス
				
			//ワールドマトリックスの初期化
			//行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
			D3DXMatrixIdentity(&mtxWorldVtx);

			//位置を反映
			//行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, aVtx[nCntVtx].x, aVtx[nCntVtx].y, aVtx[nCntVtx].z);
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);        //行列掛け算関数

			 //向きの反映
			 //行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

			//行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

			//位置を反映
			//行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans);        //行列掛け算関数

			aVtx[nCntVtx] = D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
		}

		if (aVtx[0] == aVtx[1]
			|| aVtx[0] == aVtx[2]
			|| aVtx[1] == aVtx[2])
		{//縮退ポリゴンの場合
			continue;
		}

		// ポリゴンの辺ベクトル
		aVecLine[0] = aVtx[1] - aVtx[0];
		aVecLine[1] = aVtx[2] - aVtx[1];
		aVecLine[2] = aVtx[0] - aVtx[2];

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{//頂点とターゲットのベクトル
			aVecPos[nCntVtx] = posTarget - aVtx[nCntVtx];

			//頂点とターゲットのベクトルとポリゴンの辺ベクトルの内積を算出
			fInnerProduct[nCntVtx] = (aVecLine[nCntVtx].z * aVecPos[nCntVtx].x) - (aVecLine[nCntVtx].x * aVecPos[nCntVtx].z);
		}

		if ((0.0f <= fInnerProduct[0]
			&& 0.0f <= fInnerProduct[1]
			&& 0.0f <= fInnerProduct[2])
			|| (0.0f >= fInnerProduct[0]
				&& 0.0f >= fInnerProduct[1]
				&& 0.0f >= fInnerProduct[2]))
		{// 判定の設定
			bCollison = true;

			// 面法線ベクトル
			D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 面法線ベクトル(三次元の外積)
			D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);

			//正規化
			D3DXVec3Normalize(&norVec, &norVec);

			//差分
			D3DXVECTOR3 sub = posTarget - m_pos;
			//D3DXVec3Normalize(&sub, &sub);

			//ベクトル
			D3DXVECTOR3 P = aVtx[0];
			D3DXVECTOR3 PA = m_pos - P;
			//D3DXVec3Normalize(&PA, &PA);
			D3DXVECTOR3 PB = posTarget - P;
			//D3DXVec3Normalize(&PB, &PB);

			//内積
			float dotPA = D3DXVec3Dot(&PA, &norVec);
			float dotPB = D3DXVec3Dot(&PB, &norVec);
			if (dotPA == 0 || dotPB == 0)
			{
				continue;
			}
			D3DXVECTOR3 pointX = m_pos + sub *(dotPA / (dotPA + dotPB));

			if (nCntPolygon % 2 == 0)
			{
				norVec *= -1.0f;
			}

			//角度の設定
			rot->x = norVec.x;
			rot->y = norVec.y;
			rot->z = norVec.z;
			//位置の設定
			//pos->y = (aVtx[0].y) - ((posTarget.x - aVtx[0].x) * norVec.x + (posTarget.z - aVtx[0].z) * norVec.z) / norVec.y; 
			//D3DXVECTOR3 cross[3] = {};
			//D3DXVECTOR3 X[3] = {};
			//for (int nCnt = 0; nCnt < 3; nCnt++)
			//{
			//	X[nCnt] = pointX - aVtx[nCnt];
			//}

			//D3DXVec3Cross(&cross[0], &aVecLine[0], &X[0]);
			//D3DXVec3Cross(&cross[1], &aVecLine[1], &X[1]);
			//D3DXVec3Cross(&cross[2], &aVecLine[2], &X[2]);

			//if ((int)cross[0].x == (int)cross[1].x
			//	&& (int)cross[0].y == (int)cross[1].y
			//	&& (int)cross[0].z == (int)cross[1].z
			//	&& (int)cross[0].x == (int)cross[2].x
			//	&& (int)cross[0].y == (int)cross[2].y
			//	&& (int)cross[0].z == (int)cross[2].z)
			//{
			//	pos->x = pointX.x;
			//	pos->y = pointX.y;
			//	pos->z = pointX.z;
			//}

#ifdef _DEBUG
			//デバック
			CDebugProc::Print("内にいるポリゴン : %d\n", nCntPolygon);
			//float randcolr = (rand() % 10) * 1.0f;
			//float randcolg = (rand() % 10) * 1.0f;
			//float randcolb = (rand() % 10) * 1.0f;
			//pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			//pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			//pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
#endif //DEBUG

			break;
		}
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//当たり判定を返す
	return bCollison;
}