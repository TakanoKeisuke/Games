//======================================================
//
//life_gage.cpp
//Author:髙野馨將
//
//======================================================
#include "life_gauge.h"
#include "application.h"
#include "game.h"
#include "player.h"

//======================================================
//コンストラクタ
//======================================================
CLife_gauge::CLife_gauge(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CLife_gauge::~CLife_gauge()
{//何も書かない
}

//======================================================
//初期化処理
//======================================================
HRESULT CLife_gauge::Init(void)
{
	//初期化処理
	CObject2D::Init();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\life.png",
		&m_pTexture);

	//テクスチャの設定
	CObject2D::BindTexture(m_pTexture);

	//テクスチャ座標の設定
	SetTex(4.0f, 0.0f);

	return S_OK;
}

//======================================================
//更新処理
//======================================================
void CLife_gauge::Uninit()
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//解放処理
	Flag();
}

//======================================================
//更新処理
//======================================================
void CLife_gauge::Update()
{
	//カメラの情報の取得
	CPlayer *pPlayer = CGame::GetPlayer();
	int nLife = pPlayer->GetLife();

	if (nLife == 3)
	{
		//テクスチャ座標の設定
		SetTex(4.0f, 0.0f);
	}
	else if (nLife == 2)
	{
		//テクスチャ座標の設定
		SetTex(4.0f, 1.0f);
	}
	else if (nLife == 1)
	{
		//テクスチャ座標の設定
		SetTex(4.0f, 2.0f);
	}
	else if (nLife == 0)
	{
		//テクスチャ座標の設定
		SetTex(4.0f, 3.0f);
	}

	//更新処理
	CObject2D::Update();
}

//======================================================
//更新処理
//======================================================
void CLife_gauge::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//======================================================
//生成処理
//======================================================
CLife_gauge *CLife_gauge::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//動的確保
	CLife_gauge *pLife = new CLife_gauge;

	if (pLife != nullptr)
	{
		//初期化
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(size);
	}

	return pLife;
}