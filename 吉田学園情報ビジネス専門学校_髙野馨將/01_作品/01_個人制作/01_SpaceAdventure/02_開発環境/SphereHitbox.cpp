//=============================================================================
//
// sphereHitbox.cpp
// Author : 髙野馨將
//
//=============================================================================
#include "SphereHitbox.h"

//======================================================
//コンストラクタ
//======================================================
CSphereHitbox::CSphereHitbox()
{
}

//======================================================
//デストラクタ
//======================================================
CSphereHitbox::~CSphereHitbox()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CSphereHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CSphereHitbox::Uninit(void)
{
	//終了処理
	CHitbox::Uninit();
}

//======================================================
//更新処理
//======================================================
void CSphereHitbox::Update(void)
{
	if (GetType() == TYPE_PLAYER)
	{//プレイヤーのヒットボックスだったら、
		std::vector <CHitbox*>* pHbx = GetAllHitbox();			//全部のヒットボックスを取得する

		for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
		{//取得したヒットボックスを全部判定する

			if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
			{//親が同じではなかったら

				HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();			//形の取得

				switch (shape)
				{
				case CHitbox::SHAPE_SPHERE:

				{//スフィアの場合

					if (SphereSphereHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize(), pHbx->data()[nCnt]->GetEffect()))
					{//当たった場合

						if (!GetInvincibility())
						{//無敵状態ではなかったら

							pHbx->data()[nCnt]->SetCollisionState(true);		//当たった状態にする

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//エフェクトがあったら、エフェクトを設定する
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				case CHitbox::SHAPE_BOX:
				{//矩形の場合

					if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
					{//当たった場合

						if (!GetInvincibility())
						{//無敵状態ではなかったら

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//エフェクトがあったら、エフェクトを設定する
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				case CHitbox::SHAPE_CYLINDER:
				{//シリンダーの場合

					if (SphereCylinderHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize(), pHbx->data()[nCnt]->GetEffect()))
					{//当たった場合

						if (!GetInvincibility())
						{//無敵状態ではなかったら

							pHbx->data()[nCnt]->SetCollisionState(true);		//当たった状態にする

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//エフェクトがあったら、エフェクトを設定する
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				default:
					break;
				}
			}
		}
	}

	//更新
	CHitbox::Update();
}

//======================================================
//生成処理
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CSphereHitbox* pHitbox = new CSphereHitbox;				//ヒットボックスの生成

	if (FAILED(pHitbox->Init()))
	{//初期化処理
		return nullptr;
	}

	//生成に必要な情報
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);

	return pHitbox;
}

//======================================================
//生成処理
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent)
{
	CSphereHitbox* pHitbox = new CSphereHitbox;				//ヒットボックスの生成

	if (FAILED(pHitbox->Init()))
	{//初期化処理
		return nullptr;
	}

	//生成に必要な情報
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//スコアの設定

	return pHitbox;
}

//======================================================
//生成処理
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect)
{
	//ヒットボックスの生成
	CSphereHitbox* pHitbox = new CSphereHitbox;

	if (FAILED(pHitbox->Init()))
	{//初期化処理
		return nullptr;
	}

	//生成に必要な情報
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//スコアの設定
	pHitbox->SetEffect(effect);							//エフェクトの設定

	return pHitbox;
}

//======================================================
//生成に必要な情報
//======================================================
void CSphereHitbox::CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CSphereHitbox *Hitbox)
{
	Hitbox->SetRelativePos(RelativePos);				//相対位置の設定
	Hitbox->SetPos(pos);								//位置の設定
	Hitbox->SetLastPos(pos);							//前回の位置の設定
	Hitbox->SetSize(size);								//サイズの設定
	Hitbox->SetType(type);								//種類の設定
	Hitbox->SetShape(CHitbox::SHAPE_SPHERE);			//形の設定
	Hitbox->SetParent(pParent);							//親の設定
}

//======================================================
//スフィアとシリンダーの当たり判定
//======================================================
bool CSphereHitbox::SphereCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect)
{
	D3DXVECTOR3 thisPos, thisSize;				//このヒットボックスの前回位置の取得
	thisPos = GetPos();							//このヒットボックスの現在位置の取得
	thisSize = GetSize();						//このヒットボックスののサイズ取得

	float fTop, fBottom;				//他のヒットボックスの上側と下側

	fTop = pos.y + size.y;				//上側の座標
	fBottom = pos.y;					//下側の座標

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//Y座標が重なった場合

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//距離
		fRadius = size.x + thisSize.x;				//半径の足し算

		if (fDistance < fRadius)
		{//距離は半径の足し算より小さかった
			if (effect == EFFECT_GOAL || effect == EFFECT_JUMP || effect == EFFECT_HEAL || effect == EFFECT_SPEED || effect == EFFECT_CHECKPOINT || effect == EFFECT_MAX)
			{//押し出しをしない
				return true;
			}
			D3DXVECTOR3 thisLast = GetLastPos();				//前回の位置の取得
			D3DXVECTOR3 parentPos = GetParent()->GetPos();		//親の取得

			D3DXVECTOR3 dist = thisPos - pos;					//距離を計算する
			float fHeight = parentPos.y;						//現在の高さ
			dist.y = 0.0f;
			D3DXVec3Normalize(&dist, &dist);					//距離を正規化する
			dist.x *= fRadius + 0.001f;
			dist.z *= fRadius + 0.001f;
			dist.x += pos.x;
			dist.z += pos.z;
			parentPos = dist - GetRelativePos();				//新しい位置を計算する
			parentPos.y = fHeight;								//元の高さを設定する
			GetParent()->SetPos(parentPos);						//親の位置の設定

			return true;				//trueを返す
		}
	}

	return false;						//falseを返す
}

//======================================================
//点と矩形の当たり判定
//======================================================
bool CSphereHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//このヒットボックスの現在位置の取得
	D3DXVECTOR3 thisSize = GetSize();					//このヒットボックスのサイズ取得
	D3DXVECTOR3 thisLastPos = GetLastPos();				//このヒットボックスの前回位置の取得

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y座標が重なった場合

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//計算用のベクトル
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//計算用のマトリックス
		float fResult;											//計算用の変数

		//頂点の相対座標の設定
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//相対座標から絶対座標に変換する
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//各頂点から次の頂点までのベクトルを計算する
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//各頂点からこのヒットボックスの位置までのベクトルを計算する
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//上のベクトルの外積を計算する
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//全部の外積の符号が同じだったら、当たった

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//上から当たった場合

				//新しい位置の計算
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);                                    //前回の位置の設定

				GetParent()->SetPos(thisPos - GetRelativePos());        //親の位置の設定
				SetPos(thisPos);

				return true;            //trueを返す
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//下から当たった場合

				//新しい位置の計算
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);									//前回の位置の設定
				GetParent()->SetPos(thisPos - GetRelativePos());		//親の位置の設定

				return true;			//trueを返す
			}
			else
			{//横から当たった場合

				for (int Count = 0; Count < 4; Count++)
				{//どこから当たったか求める
					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//どこから当たったか分かったら
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//前回の位置から現在の位置までのベクトル
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//前回の位置から頂点までのベクトル
						D3DXVec3Normalize(&N, &P[0]);			//前回の位置から現在の位置までのベクトルを正規化する

						//上のベクトルと矩形の辺のベクトルの外積を計算する
						D3DXVec3Cross(&R[0], &P[1], &V[Count]);
						D3DXVec3Cross(&R[1], &N, &V[Count]);

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;

						if (fResult > 0)
						{
							fResult -= 0.001f;
						}
						else if (fResult < 0)
						{
							fResult += 0.001f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;
						float Dot, Lenght1, Lenght2, Alpha;

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//交点座標
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//頂点からこのヒットボックスの位置までのベクトル
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//頂点から交点までのベクトル

						D3DXVec3Normalize(&N, &VtxtoCross);			//頂点から交点までのベクトルを正規化する

																	//頂点から交点までのベクトルと頂点からこのヒットボックスの位置までのベクトルの内積を計算する
						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//上のベクトルの長さを計算する
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//上のベクトルの長さを計算する

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{ //新しい位置を計算する
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));
							fResult = (Lenght2 * cosf(Alpha));

							//新しい位置の設定
							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{//エラーがあったら、新しい位置を交点座標に設定する
							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());		//親の位置の設定
				SetLastPos(thisPos);									//前回の位置の設定
				SetPos(thisPos);										//現在の位置の設定

				return true;			//trueを返す
			}
		}
	}

	return false;						//falseを返す
}

//======================================================
//スフィアとスフィアの当たり判定
//======================================================
bool CSphereHitbox::SphereSphereHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect)
{
	D3DXVECTOR3 thisPos, thisSize;				//このヒットボックスの前回位置の取得
	thisPos = GetPos();							//このヒットボックスの現在位置の取得
	thisSize = GetSize() / 2.0f;				//このヒットボックスののサイズ取得

	float fDistance, fRadius;
	fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//距離
	fRadius = (size.x / 2.0f) + thisSize.x;				//半径の足し算

	if (pos.y >= thisPos.y - thisSize.y && pos.y + size.y <= thisPos.y + thisSize.y)
	{
		if (fDistance < fRadius)
		{//距離は半径の足し算より小さかったら
			if (effect != CHitbox::EFFECT_FLY)
			{
				D3DXVECTOR3 thisLast = GetLastPos();				//前回の位置の取得
				D3DXVECTOR3 parentPos = GetParent()->GetPos();		//親の取得

				D3DXVECTOR3 dist = thisPos - pos;					//距離を計算する
				float fHeight = parentPos.y;						//現在の高さ
				dist.y = 0.0f;
				D3DXVec3Normalize(&dist, &dist);					//距離を正規化する
				dist.x *= fRadius + 0.001f;
				dist.z *= fRadius + 0.001f;
				dist.x += pos.x;
				dist.z += pos.z;
				parentPos = dist - GetRelativePos();				//新しい位置を計算する
				parentPos.y = fHeight;								//元の高さを設定する
				GetParent()->SetPos(parentPos);						//親の位置の設定
			}
			return true;				//trueを返す
		}
	}

	return false;						//falseを返す
}