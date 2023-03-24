//======================================================
//
//ビルボード
//Author:髙野馨將
//
//======================================================
#include "billboard.h"
#include "application.h"
#include "input.h"
#include <assert.h>
#include "object3d.h"

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	//初期化
	m_bTexture = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//======================================================
//デストラクタ
//======================================================
CBillboard::~CBillboard()
{
	//assert(m_pVtxBuff == nullptr);
}

//======================================================
//初期化処理
//======================================================
HRESULT CBillboard::Init(void)
{
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
	LoadTexture("data\\TEXTURE\\bullet000.png");

	//pVtxの生成
	SetVtx();

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CBillboard::Uninit(void)
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

	Break();
}

//======================================================
//更新処理
//======================================================
void CBillboard::Update(void)
{
	SetVtx();
}

//======================================================
//描画処理
//======================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX mtxView, mtxTrans;	//計算用マトリックス
									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;	//縦回転
	m_mtxWorld._22 = mtxView._22;	//縦回転
	m_mtxWorld._23 = mtxView._32;	//縦回転
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブ(ポリゴン(三角形))数
	//ライトを元に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================================================
//生成処理
//======================================================
CBillboard *CBillboard::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//動的確保
	CBillboard *pObject3D;
	pObject3D = new CBillboard(nPriority);

	if (pObject3D != nullptr)
	{
		//初期化
		pObject3D->Init();
		pObject3D->SetPos(pos);
		pObject3D->SetSize(size);
	}

	return pObject3D;
}

//======================================================
//pVtxの生成
//======================================================
void CBillboard::SetVtx(void)
{
	VERTEX_3D * pVtx;		//頂点情報へのポインタ
							//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);

	// norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

////======================================================
////色の変更
////======================================================
//void CBillboard::SetCol(D3DXCOLOR col)
//{
//	VERTEX_3D * pVtx;		//頂点情報へのポインタ
//							//頂点バッファをロックし、頂点情報へのポインタを取得
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//頂点カラーの設定
//	pVtx[0].col = col;
//	pVtx[1].col = col;
//	pVtx[2].col = col;
//	pVtx[3].col = col;
//
//	//頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//}

//======================================================
//テクスチャの読み込み
//======================================================
void CBillboard::LoadTexture(const char *aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		aFileName,
		&m_pTexture);

	m_bTexture = true;
}