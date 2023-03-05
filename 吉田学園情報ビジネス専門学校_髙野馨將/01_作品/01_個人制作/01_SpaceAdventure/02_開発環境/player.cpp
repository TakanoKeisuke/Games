//======================================================
//
//プレイヤー
//Author:髙野馨將
//
//======================================================
#include "player.h"
#include "application.h"
#include "game.h"
#include "input.h"
#include "debug.h"
#include <assert.h>
#include <stdio.h>
#include "meshfield.h"
#include "BoxHitbox.h"
#include "CylinderHitbox.h"
#include "model.h"
#include "mesh_sphere.h"
#include "sphere.h"
#include "shadow.h"
#include "motion.h"
#include "fade.h"
#include "planet.h"
#include "gimmick.h"
#include "SphereHitbox.h"
#include "stage.h"
#include "sound.h"
#include "particle.h"
#include "inputPad.h"
#include "timer.h"

//静的メンバ変数宣言
float CPlayer::m_fAcceleration = 1.0f;		//加速係数
float CPlayer::m_fJump = 20.0f;				//ジャンプ力
//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CPlayer::~CPlayer()
{

}

//======================================================
//初期化処理
//======================================================
HRESULT CPlayer::Init(void)
{
	//初期化
	m_nCntModel = 0;
	m_nCntGoal = 0;
	m_fCT = 0.0f;
	m_fBuffQuantity = 0.0f;
	m_fFriction = 0.45f;
	m_fDash = 1.0f;
	m_fSlowFall = 1.0f;
	m_nLife = 3;
	m_nBuffTime = 0;
	m_pHitbox = nullptr;
	m_Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Originpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXQuaternionIdentity(&m_quat);
	D3DXMatrixIdentity(&m_mtxQuat);
	m_bModel = false;
	m_bShadow = true;
	m_bCollisionField = {};
	m_bJumping = false;
	m_bGoal = false;
	m_bInside = false;
	m_bCollisionPlanet = false;

#ifdef _DEBUG
	//デバックモード
	m_nLife = 300;
#endif // _DEBUG

	//モデルの生成
	LoadPlayer();

	return S_OK;
}

//======================================================
//更新処理
//======================================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();	//終了処理
			delete m_apModel[nCnt];		//破棄する
			m_apModel[nCnt] = nullptr;	//nullにする
		}
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//モーションの破棄処理
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//攻撃のヒットボックスの破棄処理
	if (m_pAttackHitbox != nullptr)
	{
		m_pAttackHitbox->Release();
		m_pAttackHitbox = nullptr;
	}

	//解放処理
	Flag();
}

//======================================================
//更新処理
//======================================================
void CPlayer::Update(void)
{
	//重力
	if (m_move.y >= -10.0f && !m_bInside)
	{
		m_move.y -= 1.0f;
	}

	//モーションの更新
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update();
	}

	//モーションの設定
	m_pMotion->SetPresentAnim(0);

	//キー入力
	Input();

	if (m_pHitbox != nullptr)
	{
		//オブジェクトの当たり判定
		CollisionObj();
	}

	//ステージの当たり判定
	CollisionStage();

	//プレイヤーの強化
	BuffPlayer();

	//プレイヤーが一定の高さより落ちたら
	if (GetPos().y <= -200.0f)
	{//ダメージを受ける
		m_pHitbox->SetEffect(CHitbox::EFFECT_DAMAGE);
		//プレイヤーの位置を戻す
		SetPos(m_Originpos);
	}

	if (m_bGoal)
	{//ゴールしたらカウントする
		m_nCntGoal++;
	}
	//ゴールカウントが120を超えたら
	if (m_nCntGoal >= 60 && CFade::GetFade() == CFade::FADE_NONE)
	{//遷移する
		m_nCntGoal = 0;
		//モード設定
		CFade::SetFade(CApplication::MODE_RESULT);
	}
}

//======================================================
//描画処理
//======================================================
void CPlayer::Draw(void)
{
	if (m_nInvincibleCnt % 10 <= 5)
	{//無敵状態だったら、点滅させる
	//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

		//計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		if (m_bInside)
		{//球に乗っているなら
			D3DXMatrixMultiply(&mtxRot, &mtxRot, &m_mtxQuat);
		}
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			//モデルの描画
			m_apModel[nCnt]->Draw();
		}
	}
}

//======================================================
//生成処理
//======================================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority)
{
	//動的確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer(nPriority);

	if (pPlayer != nullptr)
	{
		//初期化
		pPlayer->Init();
		pPlayer->m_pos = pos;
		pPlayer->m_Originpos = pos;
		pPlayer->m_rot = rot;
		pPlayer->m_size = size;

		//アニメーションの生成
		pPlayer->m_pMotion = CMotion::Create(CMotion::ANIM_TYPE_PLAYER);
		//ヒットボックスの生成
		pPlayer->m_pHitbox = CSphereHitbox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), size, CHitbox::TYPE_PLAYER, pPlayer);
	}

	return pPlayer;
}

//======================================================
//オブジェクトと当たった時
//======================================================
void CPlayer::CollisionObj(void)
{
	//情報を取得
	CCamera *pCamera = CApplication::GetCamera();		//カメラの情報
	CTimer *pTimer = CGame::GetTimer();					//スコアの情報

	//当たり判定の更新
	m_pHitbox->SetPos(m_pos);
	m_pHitbox->Update();

	//当たり判定のエフェクトを取得
	CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

	switch (effect)
	{

	case CHitbox::EFFECT_GOAL:
		//触れたらゴール
		m_bGoal = true;
		break;

	case CHitbox::EFFECT_DAMAGE:
		//体力を減らす
		if (m_nLife > 0)
		{
			m_nLife--;
		}

		//カメラを揺らす
		pCamera->ShakeCamera(20, 3.0f);

		//ノックバックの処理(新しい速度の設定)
		D3DXVec3Normalize(&m_move, &m_move);
		m_move.x *= -50.0f;
		m_move.y = 10.0f;
		m_move.z *= -50.f;

		//無敵状態カウンターを設定する
		m_nInvincibleCnt = 60;

		//体力がなくなったら
		if (m_nLife <= 0)
		{
			//スコアの減算
			pTimer->SubTimer(5);
		}

		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
			m_pHitbox->SetInvincibility(true);						//無敵状態を設定する
		}
		break;

	case CHitbox::EFFECT_HEAL:
		//体力が2以下の時増やす
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
		}
		break;

	case CHitbox::EFFECT_FLY:
		//飛ばす
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_Y, 0) && m_bJumping
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_X, 0) && m_bJumping)
		{
			if (m_fBuffQuantity != 0.0f)
			{//ジャンプ力が調整されていたら
				m_move.y = (m_fJump + 10.0f) * m_fBuffQuantity;
			}
			else
			{
				m_move.y = m_fJump + 50.0f;
			}
			//ジャンプした状態にする
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}
		if (m_bInside && m_bJumping)
		{
			//上方向に飛ばす
			m_move = m_norVec * 120.0f;
			//ジャンプした状態にする
			m_bJumping = false;
			//SE
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		}


		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
		}
		break;

	case CHitbox::EFFECT_SPEED:
		//強化効果の種類を設定
		m_type = TYPE_SPEED;
		//強化効果の時間を設定
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
		}
		break;

	case CHitbox::EFFECT_JUMP:
		//強化効果の種類を設定
		m_type = TYPE_JUMP;
		//強化効果の時間を設定
		m_nBuffTime = 300;
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUFF);

		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
		}
		break;

	case CHitbox::EFFECT_CHECKPOINT:

		//リスポーン地点の設定
		m_Originpos = m_pHitbox->GetPos();
		//体力が2以下の時増やす
		if (m_nLife <= 2)
		{
			m_nLife++;
		}

		if (m_pHitbox != nullptr)
		{//ヒットボックスのポインタがnullではなかったら
			m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//エフェクトを戻す
		}
		break;

	default:
		break;
	}

	//無敵時間
	if (m_nInvincibleCnt > 0)
	{
		m_nInvincibleCnt--;			//カウンターの更新

		if (m_nInvincibleCnt <= 0)
		{//0になったら、
			if (m_pHitbox != nullptr)
			{//ヒットボックスがnullではなかったら
				m_pHitbox->SetInvincibility(false);			//無敵状態が終わるように設定する
			}
		}
	}
}

//======================================================
//プレイヤーの強化処理
//======================================================
void CPlayer::BuffPlayer(void)
{
	//プレイヤーのタイプによって得られる強化
	if (m_type != TYPE_NONE && m_nBuffTime > 0)
	{
		BuffEffect(m_type);
		m_type = TYPE_NONE;
	}

	//強化効果の時間を減少
	if (m_nBuffTime > 0)
	{
		m_nBuffTime--;
		//パーティクルの生成
		CGame::GetParticle()[0] = CParticle::Create(CParticle::PARTICLETYPE_FOUNTAIN, m_pos, 30, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f));
	}

	//強化効果のリセット
	if (m_nBuffTime == 0)
	{
		m_fAcceleration = 1.0f;
		m_fSlowFall = 1.0f;
	}
}

//======================================================
//強化効果処理
//======================================================
void CPlayer::BuffEffect(PLAYER_TYPE type)
{
	switch (type)
	{
	case CPlayer::TYPE_SPEED:
		//加速
		m_fAcceleration = 2.0f;
		//時間
		m_nBuffTime = 300;
		break;

	case CPlayer::TYPE_JUMP:
		//落下速度低下
		m_fSlowFall = 4.0f;
		//時間
		m_nBuffTime = 360;
		break;

	default:
		break;
	}
}

//======================================================
//ステージと当たった時
//======================================================
void CPlayer::CollisionStage(void)
{
	//メッシュの情報取得
	std::vector<CMeshField*> pMesh = CStage::GetMesh();
	bool b = true;
	D3DXVECTOR3 shadowPos = m_apModel[0]->GetShadowPos();
	//メッシュフィールドの数 着地の判定をする
	m_bCollisionField.resize(CStage::m_nMaxMesh);
	for (int nCnt = 0; nCnt < CStage::m_nMaxMesh; nCnt++)
	{
		if (pMesh[nCnt] != nullptr)
		{
			//メッシュの当たり判定
			m_bCollisionField[nCnt] = pMesh[nCnt]->Collision(&m_pos, (m_size.y / 2.0f));
		}
		//着地しているときはジャンプできる
		if (m_bCollisionField[nCnt])
		{
			m_bJumping = true;
			m_fFriction = pMesh[nCnt]->GetFriction();

			for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
			{//モデルの影
				m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, m_pos.y + 0.2f, m_pos.z));

				b = pMesh[nCnt]->ShadowCollision(&D3DXVECTOR3(shadowPos.x, m_pos.y, shadowPos.z), 0.0f);

				if (!b)
				{
					m_bShadow = false;
				}
				else
				{
					m_bShadow = true;
				}
			}

			break;
		}
		else
		{
			m_fFriction = 0.45f;
			m_bJumping = false;

			//b = pMesh[nCnt]->ShadowCollision(&D3DXVECTOR3(shadowPos.x, 0.0f, shadowPos.z), 0.0f);

			//if (!b)
			//{
			//	m_bShadow = false;
			//}
			//else
			//{
			//	m_bShadow = true;
			//}
		}
	}




	//惑星の情報取得
	std::vector<CPlanet*> pPlanet = CStage::GetPlanet();	//それぞれの惑星の情報
	std::vector<float> fDif;								//それぞれの惑星との距離
	std::vector<CPlanet*> pNearPlanet;						//最も近い惑星の情報
	fDif.resize(CStage::m_nMaxPlanet);
	pNearPlanet.resize(CStage::m_nMaxPlanet);
	//惑星とプレイヤーの距離
	for (int nCnt = 0; nCnt < CStage::m_nMaxPlanet; nCnt++)
	{
		if (pPlanet[nCnt] != nullptr)
		{
			fDif[nCnt] = pPlanet[nCnt]->TargetDistance(this);
		}
	}

	//距離の比較
	for (int nCount = 0; nCount < CStage::m_nMaxPlanet - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < CStage::m_nMaxPlanet; nCount2++)
		{
			if (fDif[nCount] < fDif[nCount2])
			{
				pNearPlanet[0] = CStage::GetPlanet()[nCount];
			}
			else
			{
				pNearPlanet[0] = CStage::GetPlanet()[nCount2];
			}
		}
	}

	if (pNearPlanet[0] != nullptr)
	{
		//惑星の当たり判定
		m_bCollisionPlanet = pNearPlanet[0]->CollisionSphere(&m_pos, &m_size);
		m_bInside = pNearPlanet[0]->SetGravity(&m_pos, &m_size, &m_move);

		if (m_bCollisionPlanet)
		{//惑星に乗っているとき
			m_bJumping = true;
		}

		//================================
		//姿勢合わせ回転
		//================================

		//回転軸の算出
		m_vecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//軸ベクトル
		m_norVec = m_pos - pNearPlanet[0]->GetPos();			//法線ベクトル
		D3DXVECTOR3 vecOver = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//上方向ベクトル

		//法線ベクトルの正規化
		D3DXVec3Normalize(&m_norVec, &m_norVec);
		//外積をつかって軸ベクトルを出す
		D3DXVec3Cross(&m_vecAxis, &vecOver, &m_norVec);
		//内積の算出
		float dot = D3DXVec3Dot(&vecOver, &m_norVec);
		//軸回転に必要な角度の算出
		float angle = acosf(dot / (D3DXVec3Length(&vecOver) * D3DXVec3Length(&m_norVec)));

		//クォータニオンの算出
		m_quat = D3DXQUATERNION(0, 0, 0, 1);
		D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, angle);
		D3DXMatrixRotationQuaternion(&m_mtxQuat, &m_quat);
	}
}

//======================================================
//入力処理
//======================================================
void CPlayer::Input(void)
{
	//カメラの情報の取得
	CCamera *pCamera = CApplication::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//プレイヤーの移動
	if (CInputPad::GetJoypadPress(CInputPad::JOYKEY_A, 0))
	{//Aボタンを押し続けるとダッシュ
		m_fDash = 1.5f;
	}
	else
	{//離すと戻る
		m_fDash = 1.0f;
	}

	if (CInputKeyboard::GetKeyboardPress(DIK_UP) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y < -0.3f)
	{//↑を押したら
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//→を押したら
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x += sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) == true || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//←を押したら	
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x -= sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		else
		{//↑
		 //進行方向のベクトル
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x += sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = m_move;
				m_rotDest.y = CameraRot.y;
			}
		}
		//モーションの設定
		m_pMotion->SetPresentAnim(1);
	}
	//↓を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_DOWN) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).y > 0.3f)
	{
		if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
		{//→を押したら
		 //進行方向のベクトル
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x += sinf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z += cosf(D3DX_PI * 0.75f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
		{//←を押したら
		 //進行方向のベクトル
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x -= sinf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(D3DX_PI * 0.25f + CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		else
		{//↓
			if (!m_bInside)
			{//メッシュフィールドに乗っている時
				m_move.x -= sinf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_move.z -= cosf(CameraRot.y) * m_fAcceleration * m_fDash;
				m_rotDest.y = CameraRot.y;
			}
			else if (m_bInside && m_bCollisionPlanet)
			{//球の範囲内
				D3DXVec3Cross(&m_move, &m_norVec, &m_vecAxis);
				m_move = -m_move;
				m_rotDest.y = CameraRot.y + D3DX_PI;
			}
		}
		//モーションの設定
		m_pMotion->SetPresentAnim(1);
	}
	//→を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x > 0.3f)
	{
		if (!m_bInside)
		{//メッシュフィールドに乗っている時
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//球の範囲内
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		//モーションの設定
		m_pMotion->SetPresentAnim(1);
	}
	//←を押したら
	else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT) || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, 0).x < -0.3f)
	{
		if (!m_bInside)
		{//メッシュフィールドに乗っている時
			m_move.x -= sinf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_move.z -= cosf(D3DX_PI * 0.5f + CameraRot.y) * m_fAcceleration * m_fDash;
			m_rotDest.y = CameraRot.y + D3DX_PI * 0.5f;
		}
		else if (m_bInside && m_bCollisionPlanet)
		{//球の範囲内
			m_move.x += sinf(D3DX_PI * 0.5f + CameraRot.y);
			m_move.z += cosf(D3DX_PI * 0.5f + CameraRot.y);
			m_rotDest.y = CameraRot.y - D3DX_PI * 0.5f;
		}
		//モーションの設定
		m_pMotion->SetPresentAnim(1);
	}

	//目的の角度の正規化
	if (m_rotDest.y - GetRot().y > D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y - D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y = m_rotDest.y + D3DX_PI * 2;
	}

	//減衰
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	//現在の角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI * 2;
	}

	//ギミックの上に乗っていたらジャンプできるようにする
	for (int nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
	{
		if (!m_bJumping)
		{//ジャンプしていなければ、乗っているか判定する
			std::vector<CGimmick*> pGimmick = CStage::GetGimmick();
			std::vector<bool> bGimmick;
			bGimmick.resize(CStage::m_nMaxGimmick);
			for (nCnt = 0; nCnt < CStage::m_nMaxGimmick; nCnt++)
			{
				if (pGimmick[nCnt] != nullptr)
				{
					bGimmick[nCnt] = pGimmick[nCnt]->GetLanding();
					//着地しているときはジャンプできる
					if (bGimmick[nCnt])
					{
						for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
						{//モデルの影
							m_apModel[nCntModel]->SetShadowPos(D3DXVECTOR3(m_pos.x, m_pos.y + 0.2f, m_pos.z));
						}
						m_move.y = 0.0f;
						m_pos.y = pGimmick[nCnt]->GetPos().y + (pGimmick[nCnt]->GetSize().y / 2.0f);
						m_bJumping = true;
					}
				}
			}
		}
	}

	//ジャンプ
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && m_bJumping
		|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0) && m_bJumping)
	{
		if (m_bInside)
		{
			m_move = m_norVec * 10.0f;
		}
		else
		{
			if (m_fBuffQuantity != 0.0f)
			{//ジャンプ力が調整されていたら
				m_move.y = m_fJump * m_fBuffQuantity;
			}
			else
			{//ジャンプ力に変化がなければ
				m_move.y = m_fJump;
			}
		}
		//SE
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		//ジャンプしている状態にする
		m_bJumping = false;
	}

	////クールタイムがなければ攻撃
	//if (CInputKeyboard::GetKeyboardTrigger(DIK_V) && m_fCT <= 0.0f && m_pAttackHitbox == nullptr)
	//{
	//	//攻撃
	//	Attack();
	//}

	//if (m_fCT > 0)
	//{//攻撃中だったら
	//	//クールタイムの減少
	//	m_fCT--;
	//}

	//if (m_fCT <= 0.0f && m_pAttackHitbox != nullptr)
	//{//カウンターが0以下になったら
	//	m_pAttackHitbox->Release();			//ヒットボックスを破棄する
	//	m_pAttackHitbox = nullptr;			//ポインタをnullにする
	//	m_fCT = 0;							//カウンターを0に戻す
	//}

	//前回位置を保存
	m_posOld = m_pos;

	//移動量を加算
	m_pos += m_move;

	//移動量の減衰
	m_move.x += (0.0f - m_move.x) * m_fFriction;
	m_move.z += (0.0f - m_move.z) * m_fFriction;
	if (m_bInside)
	{
		m_move.y += (0.0f - m_move.y) * m_fFriction;
	}
	else
	{
		if (m_move.y < 0.0f)
		{
			m_move.y += (0.0f - m_move.y) * 0.1f * m_fSlowFall;
		}
		else
		{
			m_move.y += (0.0f - m_move.y) * 0.1f;
		}
	}

#ifdef _DEBUG
	//デバック表示
	CDebugProc::Print("現在の角度%f\n", m_rot.y);
	CDebugProc::Print("現在の位置 : %f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("カメラの角度 : %f\n", CameraRot.y);
	CDebugProc::Print("目的の角度 : %f\n", m_rotDest.y);
	CDebugProc::Print("移動量 : %f %f %f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("クォータニオン %f %f %f %f\n", m_quat.x, m_quat.y, m_quat.z, m_quat.w);
	CDebugProc::Print("軸ベクトル %f %f %f \n", m_vecAxis.x, m_vecAxis.y, m_vecAxis.z);
	CDebugProc::Print("強化効果の時間 %d \n", m_nBuffTime);
#endif // _DEBUG
}

//======================================================
//攻撃処理
//======================================================
void CPlayer::Attack(void)
{
	//クールタイムの設定
	m_fCT = 60.0f;

	//プレイヤーの当たり判定に加算する分
	D3DXVECTOR3 Attack_size = m_size + D3DXVECTOR3(7.0f, 0.0f, 7.0f);

	//ヒットボックスの生成
	m_pAttackHitbox = CCylinderHitbox::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), Attack_size, CHitbox::TYPE_OBSTACLE, 0, this, CHitbox::EFFECT_PUSH);
}

//======================================================
//モデルの読み込み
//======================================================
void CPlayer::LoadPlayer(void)
{
	int nNumParts;
	char aText[2000];						//文字列を格納する配列
	char FileName[MAX_MODEL][2000];			//2次元配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data/model/model.txt", "r");

	aText[0] = '\0';	//文字列なし

	if (pFile != nullptr)
	{//ファイルが開けた場合
	 //ファイルに入力したデータを書き出す処理
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
				continue;
			}

			//ファイルネームを複数個入力する
			if (strcmp(&aText[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &aText[0]);					// = を読み込む
				fscanf(pFile, "%s", &FileName[m_nCntModel][0]);	//0番目から読み込まれる

				//モデルパーツの生成
				m_apModel[m_nCntModel] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//モデル数のカウント
				m_nCntModel++;
			}

			if (strcmp(&aText[0], "CHARACTERSET") == 0)
			{
				while (strcmp(&aText[0], "END_CHARACTERSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);        // = を読み込む
						fscanf(pFile, "%d", &nNumParts);
					}

					if (strcmp(&aText[0], "PARTSSET") == 0)
					{
						D3DXVECTOR3 pos, rot;
						int IndexParent = 0;	//親の番号
						int Ind = 0;

						while (strcmp(&aText[0], "END_PARTSSET") != 0)
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
								continue;
							}

							if (strcmp(&aText[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &Ind);
							}
							else if (strcmp(&aText[0], "PARENT") == 0)
							{

								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%d", &IndexParent);
							}
							else if (strcmp(&aText[0], "POS") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								pos = D3DXVECTOR3(x, y, z);
							}
							else if (strcmp(&aText[0], "ROT") == 0)
							{
								float x = 0.0f;
								float y = 0.0f;
								float z = 0.0f;
								fscanf(pFile, "%s", &aText[0]);
								fscanf(pFile, "%f", &x);
								fscanf(pFile, "%f", &y);
								fscanf(pFile, "%f", &z);
								rot = D3DXVECTOR3(x, y, z);
							}
						}

						//モデルパーツの読み込み
						m_apModel[Ind]->SetModel(&FileName[Ind][0]);
						m_apModel[Ind]->SetId(Ind);

						//モデルパーツに情報が入っていたら
						if (m_apModel[Ind])
						{
							//モデルパーツの位置と向きの設定
							m_apModel[Ind]->SetRot(rot);
							m_apModel[Ind]->SetPos(pos);
						}

						//親の番号が0より下だったら
						if (IndexParent < 0)
						{
							//モデルパーツのマトリックスの設定
							m_apModel[Ind]->SetParent(nullptr);
						}
						//親の番号がモデルパーツより小さかったら
						else if (IndexParent < MAX_MODEL)
						{
							//モデルパーツのマトリックスの設定
							m_apModel[Ind]->SetParent(m_apModel[IndexParent]);
						}
					}
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}