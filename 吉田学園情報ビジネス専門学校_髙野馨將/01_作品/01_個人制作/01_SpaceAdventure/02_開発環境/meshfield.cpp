//======================================================
//
//メッシュフィールド
//Author:髙野馨將
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "debug.h"
#include <assert.h>
#include "meshfield.h"

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CMeshField::~CMeshField()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CMeshField::Init(void)
{
	//初期化
	m_bTexture = false;
	m_fFriction = 0.45f;
	if (m_type == TYPE_ICE)
	{//タイプが氷の場合摩擦係数を下げる
		m_fFriction = 0.2f;
	}
	m_nVertex = ((m_block.x + 1.0f) * (m_block.y + 1.0f));
	m_nIndex = (((m_block.x + 1.0f)  * m_block.x * 2.0f) * m_block.y + (m_block.y - 1.0f) * 2.0f);
	m_nPrimitive = (m_block.x * m_block.y * 2.0f + 4.0f * (m_block.y - 1.0f));

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (int)m_nVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (int)m_nIndex,	//インデックス数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//テクスチャの設定
	if (m_type == TYPE_ICE)
	{
		LoadTexture("data\\TEXTURE\\ice.png");
	}
	else
	{
		LoadTexture("data\\TEXTURE\\block001.jpg");
	}

	VERTEX_3D * pVtx = NULL;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_block.y + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_block.x + 1; nCntX++)
		{
			//頂点座標の設定
			if (m_type == TYPE_X_UPPER)
			{//X方向に右肩上がり
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, m_size.y * nCntX, -m_size.z * nCntZ + m_size.z);
			}
			else if (m_type == TYPE_X_LOWER)
			{//X方向に右肩下がり
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, -m_size.y * nCntX, -m_size.z * nCntZ + m_size.z);
			}
			else if(m_type == TYPE_Z_UPPER)
			{//Z方向に右肩上がり
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, -m_size.y * nCntZ, -m_size.z * nCntZ + m_size.z);
			}
			else
			{//Z方向に右肩下がり
				pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].pos = D3DXVECTOR3(m_size.x * nCntX - m_size.x, m_size.y * nCntZ, -m_size.z * nCntZ + m_size.z);
			}
			//norの設定
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//頂点カラーの設定
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標の設定
			pVtx[nCntX + nCntZ * (int)(m_block.x + 1)].tex = D3DXVECTOR2((float)nCntX, (float)nCntZ);
		}
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD * pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxZ = 0; nCntIdxZ < m_block.y; nCntIdxZ++)
	{
		int nLine = nCntIdxZ * (int)((m_block.x + 1) * 2 + 2);	//列*(頂点数*2＋縮退ポリゴン)
		for (int nCntIdxX = 0; nCntIdxX <= m_block.x; nCntIdxX++)
		{
			//偶数番目
			pIdx[nCntIdxX * 2 + nLine] = (WORD)(((m_block.x + 1) * (nCntIdxZ + 1)) + nCntIdxX);
			//奇数番目
			pIdx[nCntIdxX * 2 + 1 + nLine] = (WORD)(((m_block.x + 1) * nCntIdxZ) + nCntIdxX);
			if (nCntIdxZ < m_block.y - 1)
			{
				pIdx[(int)((m_block.x + 1) * 2) + nLine] = (WORD)(m_block.x + (m_block.x + 1) * nCntIdxZ);
				pIdx[(int)((m_block.x + 1) * 2) + nLine + 1] = (WORD)(((m_block.x + 1)) * (2 + nCntIdxZ));
			}
		}
	}
	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	//法線の計算
	Normal();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CMeshField::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_bTexture)
	{
		//テクスチャの破棄
		if (m_pTexture != nullptr)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
	}

	//頂点バッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Flag();
}

//======================================================
//更新処理
//======================================================
void CMeshField::Update(void)
{
}

//======================================================
//描画処理
//======================================================
void CMeshField::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
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
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (int)m_nVertex, 0, (int)m_nPrimitive);	//プリミティブ(ポリゴン(三角形))数
	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//生成処理
//======================================================
CMeshField *CMeshField::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const D3DXVECTOR2 &block, MESH_TYPE type, int nPriority)
{
	//動的確保
	CMeshField *pMesh = new CMeshField(nPriority);

	if (pMesh != nullptr)
	{
		//初期化
		pMesh->SetSize(size);
		pMesh->SetPos(pos);
		pMesh->m_type = type;
		pMesh->m_rot = rot;
		pMesh->m_block = block;
		pMesh->Init();
	}

	return pMesh;
}

//======================================================
//テクスチャの読み込み
//======================================================
void CMeshField::LoadTexture(const char *aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}

//======================================================
//法線の計算
//======================================================
void CMeshField::Normal()
{
	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPolygon = 0; nCntPolygon < m_nPrimitive; nCntPolygon++)
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
//当たり判定
//======================================================
bool CMeshField::Collision(D3DXVECTOR3 *pos, float fRadius,bool bPush)
{
	// 当たり判定
	bool bCollison = false;

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// ターゲット情報の宣言
	D3DXVECTOR3 posTarget = *pos;

	// 計算用変数
	D3DXVECTOR3 aVtx[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecLine[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	D3DXVECTOR3 aVecPos[3] = { D3DXVECTOR3(0.0f,0.0f,0.0f) };
	float fInnerProduct[3] = { 0.0f };

	for (int nCntPolygon = 0; nCntPolygon < m_nPrimitive; nCntPolygon++)
	{
		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// 頂点座標の取得
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
		{// 縮退ポリゴンを飛ばす
			continue;
		}

		// ポリゴンの辺ベクトル
		aVecLine[0] = aVtx[1] - aVtx[0];
		aVecLine[1] = aVtx[2] - aVtx[1];
		aVecLine[2] = aVtx[0] - aVtx[2];

		for (int nCntVtx = 0; nCntVtx < 3; nCntVtx++)
		{// 頂点とターゲットのベクトル
			aVecPos[nCntVtx] = posTarget - aVtx[nCntVtx];

			// 頂点とターゲットのベクトルとポリゴンの辺ベクトルの内積を算出
			fInnerProduct[nCntVtx] = (aVecLine[nCntVtx].z * aVecPos[nCntVtx].x) - (aVecLine[nCntVtx].x * aVecPos[nCntVtx].z);
		}

		if ((0.0f <= fInnerProduct[0]
			&& 0.0f <= fInnerProduct[1]
			&& 0.0f <= fInnerProduct[2])
			|| (0.0f >= fInnerProduct[0]
				&& 0.0f >= fInnerProduct[1]
				&& 0.0f >= fInnerProduct[2]))
		{
			// 面法線ベクトル
			D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 面法線ベクトル
			D3DXVec3Cross(&norVec, &aVecLine[0], &aVecLine[1]);

			// 面法線ベクトルの正規化
			D3DXVec3Normalize(&norVec, &norVec);

			// 高さの交差点の算出
			float fIntersection = aVtx[0].y - ((posTarget.x - aVtx[0].x) * norVec.x + (posTarget.z - aVtx[0].z) * norVec.z) / norVec.y;

			if (fIntersection >= posTarget.y && fIntersection <= posTarget.y + fRadius)
			{// 位置の設定
				if (bPush)
				{
					pos->y = fIntersection;
				}

				// 判定の設定
				bCollison = true;

#ifdef _DEBUG
				//デバック表示
				/*CDebugProc::Print("内にいるポリゴン : %d\n", nCntPolygon);
				CDebugProc::Print("頂点%dの法線 | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon, pVtx[pIdx[nCntPolygon]].nor.x, pVtx[pIdx[nCntPolygon]].nor.y, pVtx[pIdx[nCntPolygon]].nor.z);
				CDebugProc::Print("頂点%dの法線 | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 1, pVtx[pIdx[nCntPolygon + 1]].nor.x, pVtx[pIdx[nCntPolygon + 1]].nor.y, pVtx[pIdx[nCntPolygon + 1]].nor.z);
				CDebugProc::Print("頂点%dの法線 | X : %.3f | Y : %.3f | Z : %.3f |\n", nCntPolygon + 2, pVtx[pIdx[nCntPolygon + 2]].nor.x, pVtx[pIdx[nCntPolygon + 2]].nor.y, pVtx[pIdx[nCntPolygon + 2]].nor.z);*/
				//pVtx[pIdx[nCntPolygon]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				//pVtx[pIdx[nCntPolygon + 1]].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				//pVtx[pIdx[nCntPolygon + 2]].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
#endif // _DEBUG
				break;
			}
		}
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//判定を返す
	return bCollison;
}