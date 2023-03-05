//======================================================
//
//オブジェクト2D
//Author:髙野馨將
//
//======================================================
#include "object2D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//クリア
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//======================================================
//デストラクタ
//======================================================
CObject2D::~CObject2D()
{//assert(m_pVtxBuff == nullptr);
}

//======================================================
//初期化処理
//======================================================
HRESULT CObject2D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//pVtxの生成
	SetVtx();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Flag();
}

//======================================================
//更新処理
//======================================================
void CObject2D::Update(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//描画処理
//======================================================
void CObject2D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//頂点情報の先頭アドレス
		2);											//プリミティブ(ポリゴン)数

	//テクスチャにnull設定
	pDevice->SetTexture(0, NULL);
}

//======================================================
//生成処理
//======================================================
CObject2D *CObject2D::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//動的確保
	CObject2D *pObject2D;
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{
		//初期化
		pObject2D->Init();
		pObject2D->SetSize(size);
		pObject2D->SetPos(pos);
	}
	return pObject2D;
}

//======================================================
//pVtxの生成
//======================================================
void CObject2D::SetVtx(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::SetLifePos(const D3DXVECTOR3 &pos,const float &size, const float &life)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x , pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size * life, pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x , pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size * life, pos.y + 50.0f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//プレイヤー座標の設定
//======================================================
void CObject2D::SetPlayerPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;

	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y / 2, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================
//色の変更
//======================================================
void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
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
void CObject2D::SetTex(float BesideSplit, float nNumIndex)
{
	//頂点座標へのポインタ
	VERTEX_2D *pVtx;

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
//当たり判定
//======================================================
bool CObject2D::Collision(const D3DXVECTOR3 &Destpos, const D3DXVECTOR3 &Destsize, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	if (Destpos.y - Destsize.y / 2.0f <= pos.y + size.y / 2.0f
		&& Destpos.y + Destsize.y / 2.0f >= pos.y - size.y / 2.0f
		&& Destpos.x + Destsize.x / 2.0f >= pos.x - size.x / 2.0f
		&& Destpos.x - Destsize.x / 2.0f <= pos.x + size.x / 2.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}