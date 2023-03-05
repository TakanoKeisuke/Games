//======================================================
//
// heal.cpp
// Author : 髙野馨將
//
//======================================================
#include "checkpoint.h"
#include "CylinderHitbox.h"
#include "game.h"
#include "application.h"
#include "sound.h"
#include "particle.h"
#include "score.h"

//======================================================
//コンストラクタ
//======================================================
CCheckpoint::CCheckpoint(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CCheckpoint::~CCheckpoint()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CCheckpoint::Init(void)
{
	//初期化
	m_pHitbox = nullptr;

	//モデルの設定
	LoadModel("data\\model\\checkpoint.x");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CCheckpoint::Uninit(void)
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
void CCheckpoint::Update(void)
{
	//情報の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 ParticlePos = pos + D3DXVECTOR3(0.0f,30.0f,0.0f);

	//パーティクルの生成
	CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, ParticlePos, 10, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));

	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//当たり判定がnullではなかったら
		if (m_pHitbox->GetCollisionState())
		{//プレイヤーと当たった場合
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHECK);

			m_pHitbox->Release();		//ヒットボックスを消す
			Uninit();					//自身を消す

			return;
		}
	}

	//更新処理
	CObjectX::Update();
}

//======================================================
//描画処理
//======================================================
void CCheckpoint::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成処理
//======================================================
CCheckpoint *CCheckpoint::Create(const D3DXVECTOR3 pos)
{
	//動的確保
	CCheckpoint *pCheck = new CCheckpoint;

	if (pCheck != nullptr)
	{
		//位置の設定
		pCheck->Init();
		pCheck->SetPos(pos);

		//ヒットボックスを生成する
		pCheck->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 7.0f, 2.0f), CHitbox::TYPE_OBSTACLE, 0, pCheck, CHitbox::EFFECT_CHECKPOINT);
	}

	return pCheck;
}