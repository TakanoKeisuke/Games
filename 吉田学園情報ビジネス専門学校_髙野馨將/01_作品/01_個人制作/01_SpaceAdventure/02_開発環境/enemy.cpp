//======================================================
//
// Spike.cpp
// Author : 髙野馨將
//
//======================================================
#include "enemy.h"
#include "CylinderHitbox.h"
#include "player.h"
#include "game.h"

//======================================================
//コンストラクタ
//======================================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CEnemy::~CEnemy()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CEnemy::Init(void)
{
	//初期化
	m_pHitbox = nullptr;
	m_type = CGimmick::TYPE_MAX;

	//モデルの設定
	LoadModel("data\\model\\spike.x");

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
{
	//情報の取得
	D3DXVECTOR3 pos = CObjectX::GetPos();
	D3DXVECTOR3 move = CObjectX::GetMove();

	//sinカーブ
	m_fHeight += D3DX_PI * 0.004f;

	switch (m_type)
	{
	case CGimmick::GIMMICK_TYPE::TYPE_MOVE_X:
		move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
		break;

	default:
		break;
	}
	if (m_pHitbox != nullptr)
	{//ヒットボックスがnullではなかったら
		m_pHitbox->SetPos(pos);
		m_pHitbox->Update();
	}

	//更新処理
	CObjectX::Update();

	//移動量の設定
	SetMove(move);
}

//======================================================
//描画処理
//======================================================
void CEnemy::Draw(void)
{
	//描画
	CObjectX::Draw();
}

//======================================================
//生成処理
//======================================================
CEnemy *CEnemy::Create(const D3DXVECTOR3 pos, int range)
{
	//動的確保
	CEnemy *pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		//位置の設定
		pEnemy->Init();
		pEnemy->SetPos(pos);
		pEnemy->m_fRange = (float)range / 2.0f;

		//ランダムで回転を設定する
		D3DXVECTOR3 rotation = D3DXVECTOR3((float)Random(-100, 100), (float)Random(-100, 100), (float)Random(-100, 100));
		D3DXVec3Normalize(&rotation, &rotation);
		rotation.x *= 0.1f;
		rotation.y *= 0.1f;
		rotation.z *= 0.1f;
		pEnemy->SetRotation(rotation);

		//ヒットボックスを生成する
		pEnemy->m_pHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 13.0f, 3.0f), CHitbox::TYPE_OBSTACLE, 0, pEnemy, CHitbox::EFFECT_DAMAGE);
	}

	return pEnemy;
}

//======================================================
//追尾処理
//======================================================
void CEnemy::Chase(void)
{
	//情報の取得
	//CPlayer *pPlayer = CGame::GetPlayer();


}