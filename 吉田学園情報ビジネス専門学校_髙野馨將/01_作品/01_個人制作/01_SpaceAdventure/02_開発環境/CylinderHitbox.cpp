//=============================================================================
//
// cylinderHitbox.cpp
// Author : ϋόμ] Ricci Alex
//
//=============================================================================
#include "CylinderHitbox.h"

//======================================================
//RXgN^
//======================================================
CCylinderHitbox::CCylinderHitbox()
{
}

//======================================================
//fXgN^
//======================================================
CCylinderHitbox::~CCylinderHitbox()
{
}

//======================================================
//ϊ»
//======================================================
HRESULT CCylinderHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//ξ{NXΜϊ»
		return -1;
	}

	return S_OK;
}

//======================================================
//IΉ
//======================================================
void CCylinderHitbox::Uninit(void)
{
	//IΉ
	CHitbox::Uninit();
}

//======================================================
//XV
//======================================================
void CCylinderHitbox::Update(void)
{
	if (GetType() == TYPE_PLAYER)
	{//vC[Μqbg{bNXΎΑ½ηA
		std::vector <CHitbox*>* pHbx = GetAllHitbox();			//SΜqbg{bNXπζΎ·ι

		for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
		{//ζΎ΅½qbg{bNXπS»θ·ι

			if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
			{//eͺ―ΆΕΝΘ©Α½η

				HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();			//`ΜζΎ

				switch (shape)
				{
				case CHitbox::SHAPE_SPHERE:
				{//Μκ
				
					if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
					{//½Α½κ

						if (!GetInvincibility())
						{//³GσΤΕΝΘ©Α½η

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//GtFNgͺ Α½ηAGtFNgπέθ·ι
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
				{//ι`Μκ

					if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
					{//½Α½κ

						if (!GetInvincibility())
						{//³GσΤΕΝΘ©Α½η

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//GtFNgͺ Α½ηAGtFNgπέθ·ι
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
				{//V_[Μκ

					if (CylinderCylinderHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize(), pHbx->data()[nCnt]->GetEffect()))
					{//½Α½κ

						if (!GetInvincibility())
						{//³GσΤΕΝΘ©Α½η

							pHbx->data()[nCnt]->SetCollisionState(true);		//½Α½σΤΙ·ι

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//GtFNgͺ Α½ηAGtFNgπέθ·ι
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

	//XV
	CHitbox::Update();
}

//======================================================
//Ά¬
//======================================================
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//qbg{bNXΜΆ¬

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}

	//Ά¬ΙKvΘξρ
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);

	return pHitbox;
}

//======================================================
//Ά¬
//======================================================
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//qbg{bNXΜΆ¬

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}

	//Ά¬ΙKvΘξρ
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//XRAΜέθ

	return pHitbox;
}

//======================================================
//Ά¬
//======================================================
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect)
{
	//qbg{bNXΜΆ¬
	CCylinderHitbox* pHitbox = new CCylinderHitbox;

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}

	//Ά¬ΙKvΘξρ
	CreateData(pos, RelativePos, size, type,pParent, pHitbox);
	pHitbox->SetScore(nScore);							//XRAΜέθ
	pHitbox->SetEffect(effect);							//GtFNgΜέθ

	return pHitbox;
}

//======================================================
//Ά¬ΙKvΘξρ
//======================================================
void CCylinderHitbox::CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CCylinderHitbox *Hitbox)
{
	Hitbox->SetRelativePos(RelativePos);				//ΞΚuΜέθ
	Hitbox->SetPos(pos);								//ΚuΜέθ
	Hitbox->SetLastPos(pos);							//OρΜΚuΜέθ
	Hitbox->SetSize(size);								//TCYΜέθ
	Hitbox->SetType(type);								//νήΜέθ
	Hitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//`Μέθ
	Hitbox->SetParent(pParent);							//eΜέθ
}

//======================================================\
//V_[ΖV_[Μ½θ»θ
//======================================================
bool CCylinderHitbox::CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect)
{
	D3DXVECTOR3 thisPos, thisSize;				//±Μqbg{bNXΜOρΚuΜζΎ
	thisPos = GetPos();							//±Μqbg{bNXΜ»έΚuΜζΎ
	thisSize = GetSize();						//±Μqbg{bNXΜΜTCYζΎ

	float fTop, fBottom;				//ΌΜqbg{bNXΜγ€ΖΊ€

	fTop = pos.y + size.y;				//γ€ΜΐW
	fBottom = pos.y;					//Ί€ΜΐW

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//YΐWͺdΘΑ½κ

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//£
		fRadius = size.x + thisSize.x;				//ΌaΜ«΅Z

		if (fDistance < fRadius)
		{//£ΝΌaΜ«΅Zζθ¬³©Α½η

			D3DXVECTOR3 thisLast = GetLastPos();					//OρΜΚuΜζΎ
			D3DXVECTOR3 parentPos = GetParent()->GetPos();			//eΜζΎ

			if (thisLast.y + thisSize.y <= pos.y)
			{//Ί©η½Α½κ
				thisPos.y = (pos.y - thisSize.y - 0.01f);		//V΅’ΚuΜvZ
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);					//eπ΅o·
				SetLastPos(thisPos);							//OρΜΚuΜέθ
			}
			else if (thisLast.y >= pos.y + size.y)
			{//γ©η½Α½κ
				thisPos.y = (pos.y + size.y + 0.01f);			//V΅’ΚuΜvZ
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);					//eπ΅o·
				SetLastPos(thisPos);							//OρΜΚuΜέθ
			}
			else
			{//‘©η½Α½κ
				D3DXVECTOR3 dist = thisPos - pos;					//£πvZ·ι
				float fHeight = parentPos.y;						//»έΜ³
				dist.y = 0.0f;
				D3DXVec3Normalize(&dist, &dist);					//£π³K»·ι
				dist.x *= fRadius + 0.001f;
				dist.z *= fRadius + 0.001f;
				dist.x += pos.x;
				dist.z += pos.z;
				parentPos = dist - GetRelativePos();				//V΅’ΚuπvZ·ι
				parentPos.y = fHeight;								//³Μ³πέθ·ι
				GetParent()->SetPos(parentPos);						//eΜΚuΜέθ
			}

			return true;				//trueπΤ·
		}
	}

	return false;						//falseπΤ·
}

//======================================================
//_Ζι`Μ½θ»θ
//======================================================
bool CCylinderHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//±Μqbg{bNXΜ»έΚuΜζΎ
	D3DXVECTOR3 thisSize = GetSize();					//±Μqbg{bNXΜTCYζΎ
	D3DXVECTOR3 thisLastPos = GetLastPos();				//±Μqbg{bNXΜOρΚuΜζΎ

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//YΐWͺdΘΑ½κ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//vZpΜxNg
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//vZpΜ}gbNX
		float fResult;											//vZpΜΟ

																//Έ_ΜΞΐWΜέθ
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//ΞΐW©ηβΞΐWΙΟ··ι
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//eΈ_©ηΜΈ_άΕΜxNgπvZ·ι
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//eΈ_©η±Μqbg{bNXΜΚuάΕΜxNgπvZ·ι
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//γΜxNgΜOΟπvZ·ι
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//SΜOΟΜͺ―ΆΎΑ½ηA½Α½

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//γ©η½Α½κ

			 //V΅’ΚuΜvZ
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);                                    //OρΜΚuΜέθ

				GetParent()->SetPos(thisPos - GetRelativePos());        //eΜΚuΜέθ
				SetPos(thisPos);

				return true;            //trueπΤ·
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//Ί©η½Α½κ

				//V΅’ΚuΜvZ
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);									//OρΜΚuΜέθ
				GetParent()->SetPos(thisPos - GetRelativePos());		//eΜΚuΜέθ

				return true;			//trueπΤ·
			}
			else
			{//‘©η½Α½κ

				for (int Count = 0; Count < 4; Count++)
				{//Η±©η½Α½©ίι
					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//Η±©η½Α½©ͺ©Α½η
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//OρΜΚu©η»έΜΚuάΕΜxNg
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//OρΜΚu©ηΈ_άΕΜxNg
						D3DXVec3Normalize(&N, &P[0]);			//OρΜΚu©η»έΜΚuάΕΜxNgπ³K»·ι

						//γΜxNgΖι`ΜΣΜxNgΜOΟπvZ·ι
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

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//π_ΐW
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//Έ_©η±Μqbg{bNXΜΚuάΕΜxNg
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//Έ_©ηπ_άΕΜxNg

						D3DXVec3Normalize(&N, &VtxtoCross);			//Έ_©ηπ_άΕΜxNgπ³K»·ι

						//Έ_©ηπ_άΕΜxNgΖΈ_©η±Μqbg{bNXΜΚuάΕΜxNgΜΰΟπvZ·ι
						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//γΜxNgΜ·³πvZ·ι
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//γΜxNgΜ·³πvZ·ι

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{ //V΅’ΚuπvZ·ι
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));
							fResult = (Lenght2 * cosf(Alpha));

							//V΅’ΚuΜέθ
							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{//G[ͺ Α½ηAV΅’Κuππ_ΐWΙέθ·ι
							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());		//eΜΚuΜέθ
				SetLastPos(thisPos);									//OρΜΚuΜέθ
				SetPos(thisPos);										//»έΜΚuΜέθ

				return true;			//trueπΤ·
			}
		}
	}

	return false;						//falseπΤ·
}


//bool CCylinderHitbox::CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
//{
//	D3DXVECTOR3 thisPos = GetPos();
//	D3DXVECTOR3 thisSize = GetSize();
//
//	if (thisPos.y + thisSize.y >= pos.y && thisPos.y <= pos.y + size.y)
//	{
//		D3DXVECTOR3 Vtx[4] = {};
//		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
//		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
//		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
//		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
//
//		D3DXMATRIX mtxW, mtxRot, MtxTrans;
//		D3DXMatrixIdentity(&mtxW);
//		D3DXMatrixTranslation(&MtxTrans, pos.x, pos.y, pos.z);
//		D3DXMatrixMultiply(&mtxW, &mtxW, &MtxTrans);
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
//		D3DXMatrixMultiply(&mtxW, &mtxW, &mtxRot);
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxW);
//		}
//
//		D3DXVECTOR3 edgeVector[4], ObjVector[4], Cross[4];
//
//		edgeVector[0] = Vtx[1] - Vtx[0];
//		edgeVector[1] = Vtx[2] - Vtx[1];
//		edgeVector[2] = Vtx[3] - Vtx[2];
//		edgeVector[3] = Vtx[0] - Vtx[3];
//
//		D3DXVECTOR3 YVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		D3DXVECTOR3 Normal[4] = {};
//		D3DXVECTOR3 nearPoint[4] = {};
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			/*D3DXVECTOR3 vDis = thisPos - pos;
//			vDis.y = 0.0f;
//			D3DXVec3Normalize(&vDis, &vDis);*/
//			D3DXVECTOR3 normCross = Vec3Null;
//			D3DXVec3Cross(&Normal[nCnt], &edgeVector[nCnt], &YVector);
//			D3DXVec3Normalize(&Normal[nCnt], &Normal[nCnt]);
//			D3DXVec3Cross(&normCross, &edgeVector[nCnt], &Normal[nCnt]);
//
//			if (normCross.y > 0.0f)
//			{
//				Normal[nCnt].x *= -1.0f;
//				Normal[nCnt].y *= -1.0f;
//				Normal[nCnt].z *= -1.0f;
//			}
//
//			nearPoint[nCnt] = thisPos + D3DXVECTOR3(Normal[nCnt].x * thisSize.x /** 0.5f*/, 0.0f, Normal[nCnt].z * thisSize.z /** 0.5f*/);
//		}
//		int nIdx = 0;
//		int nVtxIdx = 0;
//		bool bInt = false;
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			ObjVector[0] = nearPoint[nCnt] - Vtx[0];
//			ObjVector[1] = nearPoint[nCnt] - Vtx[1];
//			ObjVector[2] = nearPoint[nCnt] - Vtx[2];
//			ObjVector[3] = nearPoint[nCnt] - Vtx[3];
//
//			ObjVector[0].y = 0.0f;
//			ObjVector[1].y = 0.0f;
//			ObjVector[2].y = 0.0f;
//			ObjVector[3].y = 0.0f;
//
//			D3DXVec3Cross(&Cross[0], &edgeVector[0], &ObjVector[0]);
//			D3DXVec3Cross(&Cross[1], &edgeVector[1], &ObjVector[1]);
//			D3DXVec3Cross(&Cross[2], &edgeVector[2], &ObjVector[2]);
//			D3DXVec3Cross(&Cross[3], &edgeVector[3], &ObjVector[3]);
//
//			if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[0].y * Cross[3].y >= 0 && Cross[1].y * Cross[2].y >= 0 && Cross[1].y * Cross[3].y >= 0 && Cross[2].y * Cross[3].y >= 0)
//			{
//				nIdx = nCnt;
//				bInt = true;
//				nVtxIdx = nCnt + 2;
//
//				if (nVtxIdx >= 4)
//				{
//					nVtxIdx -= 4;
//				}
//
//				break;
//			}
//		}
//		if (bInt)
//		{
//			D3DXVECTOR3 LastPos = GetLastPos();
//			D3DXVECTOR3 parentPos = GetParent()->GetPos();
//
//			if (LastPos.y >= pos.y + size.y)
//			{
//				//D3DXVECTOR3 diff = Vec3Null;
//				//diff.y = (pos.y + size.y) - thisPos.y;
//				thisPos.y = pos.y + size.y + 0.001f;
//				//SetPos(thisPos);
//				parentPos = thisPos - GetRelativePos();
//				GetParent()->SetPos(parentPos);
//			}
//			else if (LastPos.y + thisSize.y <= pos.y)
//			{
//				//D3DXVECTOR3 diff = Vec3Null;
//				//diff.y = (pos.y - thisSize.y) - thisPos.y;
//				thisPos.y = (pos.y - thisSize.y) - 0.0001f;
//				//SetPos(thisPos);
//				parentPos = thisPos - GetRelativePos();
//				GetParent()->SetPos(parentPos);
//			}
//			else
//			{
//				D3DXVECTOR3 Center = thisPos - Vtx[nVtxIdx];
//				Center.y = 0.0f;
//				D3DXVECTOR3 radius = nearPoint[nIdx] - thisPos;
//				radius.y = 0.0f;
//				D3DXVECTOR3 versRad = Vec3Null;
//				D3DXVec3Normalize(&versRad, &radius);
//
//				D3DXVECTOR3 c[2] = {};
//				D3DXVec3Cross(&c[0], &Center, &edgeVector[nVtxIdx]);
//				D3DXVec3Cross(&c[1], &versRad, &edgeVector[nVtxIdx]);
//				float f1, f2;
//				f1 = D3DXVec3Length(&c[1]);
//				f2 = D3DXVec3Length(&c[0]);
//
//				if (f2 == 0.0f)
//				{
//					return false;
//				}
//
//				float fK = f1 / f2;
//
//				D3DXVECTOR3 edgeNormal = Vec3Null, dir = Vec3Null;
//				D3DXVec3Normalize(&edgeNormal, &edgeVector[nVtxIdx]);
//				dir = thisPos - GetLastPos();
//				dir.y = 0.0f;
//				D3DXVec3Normalize(&dir, &dir);
//				
//				float fAngle, fLength;
//
//				fAngle = acosf(D3DXVec3Dot(&edgeNormal, &dir));
//
//				D3DXVECTOR3 T = D3DXVECTOR3(thisPos.x + (versRad.x * fK), 0.0f, thisPos.z + (versRad.z * fK));
//				D3DXVECTOR3 TVec = nearPoint[nIdx] - T;
//				TVec.y = 0.0f;
//				fLength = D3DXVec3Length(&TVec);
//
//				D3DXVECTOR3 newPos = nearPoint[nIdx] + D3DXVECTOR3(0.001f + Normal[nVtxIdx].x/* * (thisSize.x * 0.25f)*/, 0.0f, 0.001f + Normal[nVtxIdx].z /** (thisSize.z * 0.25f)*/) + D3DXVECTOR3(Normal[nVtxIdx].x * (fLength + 0.001f) * sinf(fAngle), 0.0f, Normal[nVtxIdx].z * (fLength + 0.001f) * sinf(fAngle));
//
//				GetParent()->SetPos(newPos - GetRelativePos());
//
//			}
//
//
//			return true;
//		}
//	}
//
//	return false;
//}
