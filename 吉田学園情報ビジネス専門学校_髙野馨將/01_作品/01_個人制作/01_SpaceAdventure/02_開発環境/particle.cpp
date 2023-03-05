//============================================
//
//	particle.cpp
//	Author: saito shian TAKANO KEISUKE
//
//============================================
#include <assert.h>
#include "particle.h"
#include "application.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "object3d.h"
#include "debug.h"

//============================================
// パーティクルのコンストラクタ
//============================================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
}

//============================================
// パーティクルのデストラクタ
//============================================
CParticle::~CParticle()
{
}
//============================================
// パーティクルの初期化処理
//============================================
HRESULT CParticle::Init(void)
{
	//情報の取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//メンバ変数の初期化
	m_pTexture = nullptr;							//テクスチャの初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動の初期化
	m_size = D3DXVECTOR3(3.0f, 3.0f, 0.0f);			//サイズの初期化
	m_nLife = 50;									//体力の初期化
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//色の初期化

	//テクスチャの設
	SetTexture("data\\TEXTURE\\shadow000.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(ワールド座標ではなくローカル座標を設定)
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================
// パーティクルの終了処理
//============================================
void CParticle::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//破棄処理
	Flag();
}

//============================================
// パーティクルの更新処理
//============================================
void CParticle::Update(void)
{
	//位置の更新
	m_pos += m_move;

	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//頂点情報へのポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(-m_Radius, m_Radius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Radius, m_Radius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_Radius, -m_Radius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Radius, -m_Radius, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	//移動量減衰
	m_pos.x += (0.0f - m_move.x) * 0.1f;
	m_pos.y += (0.0f - m_move.y) * 0.1f;
	m_pos.z += (0.0f - m_move.z) * 0.1f;

	//位置の設定
	SetPos(m_pos);
	//移動の設定
	SetMove(m_move);
	//サイズの設定
	SetSize(m_size);
}

//============================================
// パーティクルの描画処理
//============================================
void CParticle::Draw(void)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);//行列初期化関数(第一引数の行列を単位行列に初期化)

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定	(2付くやつを消せばビルボードが上に向かない)
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	//行列回転関数(第一引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				//行列掛け算関数(第2引数 * 第三引数を第一引数に格納)

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		//行列移動関数(第一引数にx,y,z方向の移動行列を作成)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//zバッファ
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);	//ワールド座標行列の設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//パーティクルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zバッファの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//============================================
// パーティクルのテクスチャ処理
//============================================
CParticle * CParticle::SetTexture(char * pFile)
{
	//GetDeviveの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		pFile,
		&m_pTexture);

	return S_OK;
}

//============================================
// パーティクルの位置の設定
//============================================
void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================
// パーティクルのサイズの設定
//============================================
void CParticle::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================
// パーティクルの設定処理
//============================================
void CParticle::SetParticle(D3DXVECTOR3 pos, int life, D3DXCOLOR col)
{


	if (m_type == PARTICLETYPE_FIRE)
	{
		m_pos = pos;																		//位置
		m_move.x = sinf((float)(rand() % 10)) * ((float)(rand() % 15) / 15);				//xの移動量
		m_move.y = cosf((float)(rand() % 10)) * ((float)(rand() % 10) / 10);				//yの移動量
		m_move.z = sinf((float)(rand() % 10)) * ((float)(rand() % 15) / 15);				//zの移動量
		m_Radius = (float)(rand() % 5 + 2);													//半径の算出
		m_nLife = life;																		//寿命の算出
		m_col = col;																		//色
	}
	if (m_type == PARTICLETYPE_FOUNTAIN)
	{
		m_pos = pos;																		//位置
		m_move.x = sinf((float)(rand() % 100)) * ((float)(rand() % 10) / 50);				//xの移動量
		//m_move.y = 0.50f;																	//yの移動量
		m_move.z = sinf((float)(rand() % 100)) * ((float)(rand() % 10) / 50);				//zの移動量
		m_Radius = (float)(rand() % 5 + 2);													//半径の算出
		m_nLife = life;																		//寿命の算出
		m_col = col;																		//色
	}
	if (m_type == PARTICLETYPE_SPLINTER)
	{
		m_pos = pos;																		//位置
		m_move.x = sinf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//xの移動量
		m_move.y = cosf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//yの移動量
		m_move.z = sinf((float)(rand() % 250)) * ((float)(rand() % 15) / 35);				//zの移動量
		m_Radius = (float)(rand() % 5 + 1);													//半径の算出
		m_nLife = life;																		//寿命の算出
		m_col = col;																		//色
	}

}

//============================================
// パーティクルの種類の設定
//============================================
void CParticle::SetParticleType(PARTICLETYPE type)
{
	m_type = type;
}

//============================================
// パーティクルの生成
//============================================
CParticle * CParticle::Create(PARTICLETYPE type, D3DXVECTOR3 pos, int life, D3DXCOLOR col)
{
	CParticle *pParticle = nullptr;

	//パーティクルの生成
	pParticle = new CParticle(PRIORITY_5);				//パーティクルのインスタンス生成
	//nullチェック
	if (pParticle != nullptr)
	{
		pParticle->SetParticleType(type);
		//初期化処理
		pParticle->Init();
		pParticle->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pParticle->SetParticle(pos, life, col);
	}
	else
	{
		assert(false);
	}
	return pParticle;
}