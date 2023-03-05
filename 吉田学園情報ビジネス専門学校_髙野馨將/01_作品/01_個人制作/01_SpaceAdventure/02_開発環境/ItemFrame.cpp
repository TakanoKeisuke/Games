//======================================================
//
//itemframe.cpp
//Author:髙野馨將
//
//======================================================
#include "ItemFrame.h"
#include "application.h"
#include "game.h"

//======================================================
//コンストラクタ
//======================================================
CItemFrame::CItemFrame(int nPriority) : CObject2D(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CItemFrame::~CItemFrame()
{//何も書かない
}

//======================================================
//初期化処理
//======================================================
HRESULT CItemFrame::Init(void)
{
	//初期化処理
	CObject2D::Init();
	m_bGet = false;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Frame.png",
		&m_pTexture);

	//テクスチャの設定
	CObject2D::BindTexture(m_pTexture);

	//テクスチャ座標の設定
	SetTex(2.0f, 0.0f);

	return S_OK;
}

//======================================================
//更新処理
//======================================================
void CItemFrame::Uninit()
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
void CItemFrame::Update()
{
	//アイテムを入手していたら
	if (m_bGet)
	{
		//テクスチャ座標の設定
		SetTex(2.0f, 1.0f);
	}

	//更新処理
	CObject2D::Update();
}

//======================================================
//更新処理
//======================================================
void CItemFrame::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//======================================================
//生成処理
//======================================================
CItemFrame *CItemFrame::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//動的確保
	CItemFrame *pFrame = new CItemFrame;

	if (pFrame != nullptr)
	{
		//初期化
		pFrame->Init();
		pFrame->SetPos(pos);
		pFrame->SetSize(size);
	}

	return pFrame;
}