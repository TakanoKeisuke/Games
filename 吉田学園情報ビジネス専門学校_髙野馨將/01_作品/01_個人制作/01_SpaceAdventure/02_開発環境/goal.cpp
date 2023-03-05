//======================================================
//
// goal.cpp
// Author : 髙野馨將
//
//======================================================
#include "goal.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//======================================================
//コンストラクタ
//======================================================
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CGoal::~CGoal()
{
}

//======================================================
//初期化
//======================================================
HRESULT CGoal::Init(void)
{
	//初期化
	m_pHitbox = nullptr;

	//モデルの設定
	LoadModel("data\\model\\star000.x");

	return S_OK;
}

//======================================================
//終了
//======================================================
void CGoal::Uninit(void)
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
void CGoal::Update(void)
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
			 //SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SECRET_GET);

			m_pHitbox->Release();		//ヒットボックスを消す
			Uninit();					//コインを消す

			return;
		}
	}

	//更新処理
	CObjectX::Update();
}

//======================================================
//描画
//======================================================
void CGoal::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成
//======================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスを生成する
	CGoal *pGoal = new CGoal;

	if (pGoal != nullptr)
	{
		//設定処理
		pGoal->Init();
		pGoal->SetSize(size);
		pGoal->SetPos(pos);

		//横回転
		D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f,1.0f,0.0f);
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.y *= 0.03f;
		pGoal->SetRotation(rotation);

		//当たり判定
		pGoal->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_OBSTACLE,0, pGoal,CHitbox::EFFECT_GOAL);
	}

	return pGoal;
}