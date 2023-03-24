//======================================================
//
// ring.cpp
// Author : 髙野馨將
//
//======================================================
#include "ring.h"
#include "CylinderHitbox.h"
#include "SphereHitbox.h"

//======================================================
//コンストラクタ
//======================================================
CRing::CRing(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CRing::~CRing()
{
}

//======================================================
//初期化
//======================================================
HRESULT CRing::Init(void)
{
	//初期化
	m_pHitbox = nullptr;

	//モデルの設定
	LoadModel("data\\model\\jump.x");

	return S_OK;
}

//======================================================
//終了
//======================================================
void CRing::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	//解放処理
	Flag();
}

//======================================================
//更新
//======================================================
void CRing::Update(void)
{
	//情報の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	//更新処理
	CObjectX::Update();
}

//======================================================
//描画
//======================================================
void CRing::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成
//======================================================
CRing *CRing::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンスを生成する
	CRing *pRing = new CRing;

	if (pRing != nullptr)
	{
		//設定処理
		pRing->Init();
		pRing->SetSize(size);
		pRing->SetPos(pos);
		pRing->SetRot(rot);

		//当たり判定
		pRing->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE, 0, pRing, CHitbox::EFFECT_FLY);
	}

	return pRing;
}