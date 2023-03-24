//======================================================
//
// Buff.cpp
// Author : 髙野馨將
//
//======================================================
#include "buff.h"
#include "stage.h"
#include "application.h"
#include "sound.h"
#include<vector>

//======================================================
//コンストラクタ
//======================================================
CBuff::CBuff(int nPriority) : CObjectX(nPriority)
{
}


//======================================================
//デストラクタ
//======================================================
CBuff::~CBuff()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CBuff::Init(void)
{
	//初期化
	m_pHitbox = nullptr;
	m_bInvisible = false;

	switch (m_effect)
	{
	case CHitbox::EFFECT_JUMP:
		//モデルの設定
		LoadModel("data\\model\\Coin02.x");
		break;

	case CHitbox::EFFECT_SPEED:
		//モデルの設定
		LoadModel("data\\model\\Coin03.x");
		break;

	default:
		break;
	}

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CBuff::Uninit(void)
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
void CBuff::Update(void)
{
	//情報の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();
	std::vector<CBuff*> pBuff = CStage::GetBuff();

	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	if (m_pHitbox != nullptr)
	{//当たり判定がnullではなかったら
		if (m_pHitbox->GetCollisionState())
		{//プレイヤーと当たった場合
			m_bInvisible = true;
			m_nInvincibleCnt = 360;

			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

			m_pHitbox->Release();		//ヒットボックスを消す
			m_pHitbox = nullptr;
		}
	}

	//無敵時間
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//カウンターの更新
	}

	//一定時間経つとリスポーンする処理
	for (int nCnt = 0; nCnt < CStage::m_nMaxBuff; nCnt++)
	{
		if (pBuff[nCnt]->m_nInvincibleCnt <= 0 && pBuff[nCnt]->m_pHitbox == nullptr)
		{
			pBuff[nCnt]->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff[nCnt], m_effect);
		}
	}

	//無敵時間
	if (m_nInvincibleCnt <= 60)
	{
		m_bInvisible = false;
	}

	//更新処理
	CObjectX::Update();
}

//======================================================
//描画処理
//======================================================
void CBuff::Draw(void)
{
	if (!m_bInvisible)
	{
		if (m_nInvincibleCnt % 10 <= 5)
		//描画
		CObjectX::Draw();
	}
}

//======================================================
//生成処理
//======================================================
CBuff *CBuff::Create(const D3DXVECTOR3 pos, CHitbox::INTERACTION_EFFECT effect)
{
	//動的確保
	CBuff *pBuff = new CBuff;

	if (pBuff != nullptr)
	{
		//位置の設定
		pBuff->m_effect = effect;
		pBuff->Init();
		pBuff->SetPos(pos);

		//横回転
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pBuff->SetRotation(rotation);

		//ヒットボックスを生成する
		pBuff->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 8.0f, 5.0f), CHitbox::TYPE_OBSTACLE, 0, pBuff, effect);
	}

	return pBuff;
}