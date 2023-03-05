//======================================================
//
// heal.cpp
// Author : 髙野馨將
//
//======================================================
#include "heal.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "score.h"

//======================================================
//コンストラクタ
//======================================================
CHeal::CHeal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CHeal::~CHeal()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CHeal::Init(void)
{
	//初期化
	m_pHitbox = nullptr;

	//モデルの設定
	LoadModel("data\\model\\Coin00.x");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CHeal::Uninit(void)
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
void CHeal::Update(void)
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
			pScore->AddScore(100);

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN_GET);

			m_pHitbox->Release();		//ヒットボックスを消す
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
void CHeal::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成処理
//======================================================
CHeal *CHeal::Create(const D3DXVECTOR3 pos)
{
	//動的確保
	CHeal *pHeal = new CHeal;

	if (pHeal != nullptr)
	{
		//位置の設定
		pHeal->Init();
		pHeal->SetPos(pos);

		//横回転
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pHeal->SetRotation(rotation);

		//ヒットボックスを生成する
		pHeal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 10.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pHeal, CHitbox::EFFECT_HEAL);
	}

	return pHeal;
}