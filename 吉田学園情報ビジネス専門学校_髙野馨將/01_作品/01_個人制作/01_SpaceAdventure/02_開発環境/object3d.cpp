//======================================================
//
//オブジェクト3D
//Author:髙野馨將
//
//======================================================
#include "object3D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CObject3D::~CObject3D()
{//assert(m_pVtxBuff == nullptr);
}

//======================================================
//初期化処理
//======================================================
HRESULT CObject3D::Init(void)
{
	//初期化
	m_size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bTexture = false;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//テクスチャの設定
	LoadTexture("data\\TEXTURE\\sea.png");

	//pVtxの生成
	SetVtx();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CObject3D::Uninit(void)
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

	Flag();
}

//======================================================
//更新処理
//======================================================
void CObject3D::Update(void)
{
	//pVtxの生成
	SetVtx();
}

//======================================================
//描画処理
//======================================================
void CObject3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldPolygon);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldPolygon, &m_mtxWorldPolygon, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldPolygon);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブ(ポリゴン(三角形))数
	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//生成処理
//======================================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size,int nPriority)
{
	//動的確保
	CObject3D *pObject3D;
	pObject3D = new CObject3D(nPriority);

	if (pObject3D != nullptr)
	{
		//初期化
		pObject3D->Init();
		pObject3D->SetSize(size);
		pObject3D->SetPos(pos);
	}

	return pObject3D;
}

//======================================================
//pVtxの生成
//======================================================
void CObject3D::SetVtx(void)
{
	VERTEX_3D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = m_pos;
	pVtx[1].pos = m_pos;
	pVtx[2].pos = m_pos;
	pVtx[3].pos = m_pos;

	// norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//座標の設定
//======================================================
void CObject3D::SetSize(const D3DXVECTOR3 &size)
{
	m_size = size;

	VERTEX_3D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x,  0.0f, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x,  0.0f, -m_size.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//色の変更
//======================================================
void CObject3D::SetCol(D3DXCOLOR col)
{
	VERTEX_3D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//テクスチャ座標の確保
//======================================================
void CObject3D::SetTex(float BesideSplit, float nNumIndex)
{
	//頂点座標へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumIndex + 1.0f) / BesideSplit, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumIndex + 1.0f) / BesideSplit, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//======================================================
//テクスチャの読み込み
//======================================================
void CObject3D::LoadTexture(const char *aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}