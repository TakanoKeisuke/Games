//======================================================
//
//影
//Author:髙野馨將
//
//======================================================
#include "shadow.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CShadow::~CShadow()
{

}

//======================================================
//初期化処理
//======================================================
HRESULT CShadow::Init(void)
{
	//初期化
	CObject3D::Init();

	//テクスチャの設定
	LoadTexture("data\\TEXTURE\\shadow000.jpg");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}

//======================================================
//更新処理
//======================================================
void CShadow::Update(void)
{
	CObject3D::Update();
}

//======================================================
//描画処理
//======================================================
void CShadow::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CObject3D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//======================================================
//生成処理
//======================================================
CShadow *CShadow::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority)
{
	//動的確保
	CShadow *pShadow;
	pShadow = new CShadow(nPriority);

	if (pShadow != nullptr)
	{
		//初期化
		pShadow->Init();
		pShadow->SetSize(size);
		pShadow->SetPos(pos);
	}
	return pShadow;
}