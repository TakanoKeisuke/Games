//======================================================
//
// secret_item.cpp
// Author : 髙野馨將
//
//======================================================
#include "secret_item.h"
#include "CylinderHitbox.h"
#include "ItemFrame.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "score.h"

//======================================================
//コンストラクタ
//======================================================
CSecret_item::CSecret_item(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CSecret_item::~CSecret_item()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CSecret_item::Init(void)
{
	//初期化
	m_pHitbox = nullptr;
	m_bCollision = false;
	m_nNumber = 0;

	//モデルの設定
	LoadModel("data\\model\\Coin01.x");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CSecret_item::Uninit(void)
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
//更新処理
//======================================================
void CSecret_item::Update(void)
{
	//情報の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();

	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//当たり判定がnullではなかったら
		if (m_pHitbox->GetCollisionState())
		{//プレイヤーと当たった場合
		 //スコアの加算
			CScore *pScore = CGame::GetScore();
			pScore->AddScore(1000);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//ヒットボックスを消す
			CItemFrame *pFrame = CGame::GetFrame(m_nNumber);	//フレームにセットする
			pFrame->SetGetItem(true);
			Uninit();					//コインを消す

			return;
		}
	}

	//更新処理
	CObjectX::Update();
}

//======================================================
//描画処理
//======================================================
void CSecret_item::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成処理
//======================================================
CSecret_item *CSecret_item::Create(const D3DXVECTOR3 pos, int number)
{
	//動的確保
	CSecret_item *pItem = new CSecret_item;

	if (pItem != nullptr)
	{
		//位置の設定
		pItem->Init();
		pItem->m_nNumber = number;
		pItem->SetPos(pos);

		//横回転
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pItem->SetRotation(rotation);

		//ヒットボックスを生成する
		pItem->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(8.0f, 8.0f, 8.0f), CHitbox::TYPE_OBSTACLE, 0, pItem, CHitbox::EFFECT_HEAL);
	}

	return pItem;
}