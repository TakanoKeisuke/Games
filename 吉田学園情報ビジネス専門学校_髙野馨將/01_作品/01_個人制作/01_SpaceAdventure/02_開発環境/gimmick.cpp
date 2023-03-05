//======================================================
//
// gimmick.cpp
// Author : 髙野馨將
//
//======================================================
#include "gimmick.h"
#include "player.h"
#include "game.h"
#include "application.h"

//======================================================
//コンストラクタ
//======================================================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority)
{
}

//======================================================
//デストラクタ
//======================================================
CGimmick::~CGimmick()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CGimmick::Init(void)
{
	//初期化
	OriginPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nFallTime = 120;
	m_nRespawnTime = 0;
	m_fHeight = 0.0f;
	m_fRange = 0.0f;
	m_fSpeed = 1.0f;
	m_bLanding = false;
	m_bCountStart = false;
	m_bRespawn = false;
	CObjectX::Init();

	//モデルの設定
	if (m_type == TYPE_FALL)
	{
		LoadModel("data\\model\\FallFloor.x");
	}
	else if (m_type == TYPE_FALL_LONG)
	{
		LoadModel("data\\model\\LongFallFloor.x");
	}
	else
	{
		LoadModel("data\\model\\MoveFloor.x");
	}

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CGimmick::Uninit(void)
{
	//解放処理
	Flag();
}

//======================================================
//更新処理
//======================================================
void CGimmick::Update(void)
{
	//種類ごとの処理
	TypeEffect();

	//更新処理
	CObjectX::Update();

	//当たり判定の有無
	if (m_nInvincibleCnt > 0)
	{//点滅中は無し
		m_nInvincibleCnt--;
	}
	else if (m_nInvincibleCnt == 0)
	{
		//押し出し処理
		m_bLanding = PushPlayer();
	}

	//再生成処理
	if (m_bRespawn)
	{
		Respawn(OriginPos,m_feffect,m_type);
		m_nInvincibleCnt = 60;
	}

	//再生成時間が一定時間に達したら
	if (m_nRespawnTime >= 60)
	{
		m_nRespawnTime = 0;
		m_bRespawn = true;
	}

	//床が一定の高さより落ちたら
	if (GetPos().y <= -200.0f)
	{
		//リスポーンさせる
		m_nRespawnTime++;
	}

}

//======================================================
//描画処理
//======================================================
void CGimmick::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{
		//描画
		CObjectX::Draw();
	}
}

//======================================================
//生成処理
//======================================================
CGimmick *CGimmick::Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed)
{
	//動的確保
	CGimmick *pGimmick = new CGimmick;

	if (pGimmick != nullptr)
	{
		//位置の設定
		pGimmick->m_type = type;
		pGimmick->Init();
		pGimmick->OriginPos = pos;
		pGimmick->m_feffect = effect;
		pGimmick->m_fSpeed = speed;
		pGimmick->SetPos(pos);
		if (type == TYPE_FALL || type == TYPE_FALL_LONG)
		{
			pGimmick->m_nFallTime = (int)effect;
		}
		else
		{
			pGimmick->m_fRange = effect;
		}
	}

	return pGimmick;
}

//======================================================
//種類の効果処理
//======================================================
void CGimmick::TypeEffect(void)
{
	//情報の取得
	D3DXVECTOR3 move = CObjectX::GetMove();
	//sinカーブ
	m_fHeight += D3DX_PI * (0.004f * m_fSpeed);

	if (m_type != TYPE_NONE)
	{
		switch (m_type)
		{
		case CGimmick::TYPE_MOVE_X:
			move.x = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
			break;

		case CGimmick::TYPE_MOVE_Y:
			move.y = sinf((D3DX_PI * 0.25f) + m_fHeight)  * m_fRange;
			break;

		case CGimmick::TYPE_MOVE_Z:
			move.z = sinf((D3DX_PI * 0.25f) + m_fHeight) * m_fRange;
			break;

		case CGimmick::TYPE_FALL:
			//落下処理
			Fall();

			//落ちる時間に達したら
			if (m_nFallTime < 0)
			{
				//落とす
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		case CGimmick::TYPE_FALL_LONG:
			//落下処理
			Fall();

			//落ちる時間に達したら
			if (m_nFallTime < 0)
			{
				//落とす
				move.y -= 1.0f;
				m_bCountStart = false;
			}
			break;

		default:
			break;
		}
	}

	//移動量の設定
	SetMove(move);
}

//======================================================
//プレイヤーの押し出し処理
//======================================================
void CGimmick::Fall(void)
{
	//カメラの情報の取得
	CCamera *pCamera = CApplication::GetCamera();

	//まだ一度も乗っていなかったら
	if (m_bLanding && !m_bCountStart)
	{//落ちるまでの時間
		m_bCountStart = true;
	}

	//一度でも乗ったら
	if (m_bCountStart)
	{//落ちるまでの時間の減少
		m_nFallTime--;
	}

	//乗っている間
	if (m_bLanding)
	{
		//カメラを揺らす
		pCamera->ShakeCamera(1, 1.0f);
	}
}
//======================================================
//プレイヤーの押し出し処理
//======================================================
bool CGimmick::PushPlayer(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 size = GetSize() / 2.0f;
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		D3DXVECTOR3 PlayerSize = pPlayer->GetSize() / 2.0f;
		//内側に埋まってるか判定をする
		bool bCollision = false;

		//ブロックの範囲内に入ったら
		if (pos.x - size.x <= PlayerPos.x + PlayerSize.x && pos.x + size.x >= PlayerPos.x - PlayerSize.x
			&& pos.z - size.z <= PlayerPos.z + PlayerSize.z && pos.z + size.z >= PlayerPos.z - PlayerSize.z
			&& pos.y + size.y >= PlayerPos.y && pos.y - size.y <= PlayerPos.y + (PlayerSize.y * 2.0f))
		{
			//左側から当たった場合
			if ((pPlayer->GetPosOld().x + PlayerSize.x) + move.x <= pos.x - size.x + 1.0f)
			{//プレイヤーの押し出し
				PlayerPos.x = pos.x - size.x - PlayerSize.x - 0.1f;
				bCollision = true;
			}
			//右側から当たった場合
			else if ((pPlayer->GetPosOld().x - PlayerSize.x) + move.x >= pos.x + size.x - 1.0f)
			{//プレイヤーの押し出し
				PlayerPos.x = pos.x + size.x + PlayerSize.x + 0.1f;
				bCollision = true;
			}

			//奥側から当たった場合
			if ((pPlayer->GetPosOld().z - PlayerSize.z) - move.z >= pos.z + size.z - 1.0f)
			{//プレイヤーの押し出し
				PlayerPos.z = pos.z + size.z + PlayerSize.z + 0.1f;
				bCollision = true;
			}
			//手前側から当たった場合
			else if ((pPlayer->GetPosOld().z + PlayerSize.z) + move.z <= pos.z - size.z + 1.0f)
			{//プレイヤーの押し出し
				PlayerPos.z = pos.z - size.z - PlayerSize.z - 0.1f;
				bCollision = true;
			}

			//上側から当たった場合
			if (pos.y + size.y <= pPlayer->GetPos().y - move.y)
			{//プレイヤーの押し出し
				PlayerPos.y = pos.y + size.y;
				//ブロックの移動量を加算
				PlayerPos += move;
				//プレイヤーの位置を設定
				pPlayer->SetPos(PlayerPos);
				bCollision = true;
				return true;
			}

			//下側から当たった場合
			if (move.y >= 0.0f)
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) - move.y)
				{//プレイヤーの押し出し
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}
			else
			{
				if (pos.y - size.y >= pPlayer->GetPosOld().y + (PlayerSize.y * 2.0f) + move.y)
				{//プレイヤーの押し出し
					PlayerPos.y = pos.y - size.y - (PlayerSize.y * 2.0f);
					bCollision = true;
				}
			}

			if (!bCollision)
			{//当たり判定の中にめり込んだら上に押し出す
				PlayerPos.y = pos.y + size.y;
				//プレイヤーの位置を設定
				pPlayer->SetPos(PlayerPos);
				return true;
			}
			//プレイヤーの位置を設定
			pPlayer->SetPos(PlayerPos);

		}
	}
	return false;
}

//======================================================
//再生成処理
//======================================================
void CGimmick::Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type)
{
	//位置の設定
	Init();
	SetPos(pos);
	OriginPos = pos;
	m_type = type;
	if (type == TYPE_FALL || type == TYPE_FALL_LONG)
	{
		m_nFallTime = (int)effect;
	}
	else
	{
		m_fRange = effect;
	}
}