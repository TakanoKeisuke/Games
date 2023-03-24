//=============================================================================
//
// BoxHitbox.cpp
// Author : ϋόμ] Ricci Alex
//
//=============================================================================
#include "BoxHitbox.h"

//=============================================================================
//RXgN^
//=============================================================================
CBoxHitbox::CBoxHitbox()
{
}

//=============================================================================
//fXgN^
//=============================================================================
CBoxHitbox::~CBoxHitbox()
{
}

//=============================================================================
//ϊ»
//=============================================================================
HRESULT CBoxHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//ξ{NXΜϊ»
		return -1;
	}

	return S_OK;
}

//=============================================================================
//IΉ
//=============================================================================
void CBoxHitbox::Uninit(void)
{
	CHitbox::Uninit();				//IΉ
}

//=============================================================================
//XV
//=============================================================================
void CBoxHitbox::Update(void)
{
	SetPos(GetPos() + D3DXVECTOR3(0.2f, 0.0f, 0.0f));

	std::vector <CHitbox*>* pHbx = GetAllHitbox();				//SΜqbg{bNXΜζΎ

	for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
	{//SΜΆέ·ιqbg{bNXπ»θ·ι

		if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
		{//eͺ―ΆΕΝΘ©Α½η

			HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();				//`ΜζΎ

			switch (shape)
			{
			case CHitbox::SHAPE_SPHERE:
				break;

			case CHitbox::SHAPE_BOX:

			{//ι`Μκ

				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
				{//½Α½κ

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{//GtFNgͺ Α½ηAέθ·ι
						pHbx->data()[nCnt]->SetEffect(GetEffect());
					}
				}

			}

			break;

			case CHitbox::SHAPE_CYLINDER:

			{//~Μκ

				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), D3DXVECTOR3(0.0f,0.0f,0.0f), pHbx->data()[nCnt]->GetSize()))
				{//½Α½κ

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{//GtFNgͺ Α½ηAέθ·ι
						pHbx->data()[nCnt]->SetEffect(GetEffect());
					}
				}
			}

			break;

			default:
				break;
			}
		}
	}
	//XV
	CHitbox::Update();
}

//======================================================
//Ά¬
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	//qbg{bNXΜΆ¬
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}
	//Ά¬Ιg€ξρ
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);

	return pHitbox;
}

//======================================================
//Ά¬
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore)
{
	CBoxHitbox* pHitbox = new CBoxHitbox;				//qbg{bNXΜΆ¬

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}

	//Ά¬Ιg€ξρ
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	//XRAΜέθ
	pHitbox->SetScore(nScore);							

	return pHitbox;
}

//======================================================
//Ά¬
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect)
{
	//qbg{bNXΜΆ¬
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{//ϊ»
		return nullptr;
	}

	//Ά¬Ιg€ξρ
	CreateData(pos,RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//XRAΜέθ
	pHitbox->SetEffect(effect);							//GtFNgΜέθ

	return pHitbox;
}

//======================================================
//Ά¬ΙKvΘξρ
//======================================================
void CBoxHitbox::CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject * pParent,CBoxHitbox* Hitbox)
{
	Hitbox->SetRelativePos(RelativePos);				//ΞΚuΜέθ
	Hitbox->SetPos(pos);								//ΚuΜέθ
	Hitbox->SetLastPos(pos);							//OρΜΚuΜέθ
	Hitbox->SetSize(size);								//TCYΜέθ
	Hitbox->SetType(type);								//νήΜέθ
	Hitbox->SetShape(CHitbox::SHAPE_BOX);				//`Μέθ
	Hitbox->SetParent(pParent);							//eΜέθ
}

//======================================================
//½θ»θΜ
//======================================================
bool CBoxHitbox::BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//±Μqbg{bNXΜΚuΜζΎ
	D3DXVECTOR3 thisSize = GetSize();					//±Μqbg{bNXΜTCYΜζΎ
	D3DXVECTOR3 thisLastPos = GetLastPos();				//±Μqbg{bNXΜOρΜΚuΜζΎ

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//YΐWͺdΘΑ½κ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;		//vZpΜxNg
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;						//vZpΜ}gbNX
		float fResult;												//vZpΜΟ

		//Έ_ΜΞΐWΜέθ
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//βΞΐWΙΟ··ι
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

		//eΈ_©η±ΜCX^XΜΚuάΕΜxNgπvZ·ι
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//γΙvZ΅½xNgΜOΟπvZ·ι
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//SΜOΟΜͺ―ΆΎΑ½η½Α½
			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//γ©η½Α½κ

				thisPos.y = pos.y + size.y;								//γΙ΅o·
				GetParent()->SetPos(thisPos - GetRelativePos());		//eΰ΅o·

				return true;											//trueπΤ·
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y <= pos.y)
			{//Ί©η½Α½κ

				thisPos.y = pos.y - thisSize.y;							//ΊΙ΅o·
				GetParent()->SetPos(thisPos - GetRelativePos());		//eΰ΅o·

				return true;											//trueπΤ·
			}
			else
			{//‘©η½Α½κ
				for (int Count = 0; Count < 4; Count++)
				{//OρΜΚuΖδΧΔAΗ±©η½Α½©ίι

					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//π_ΐWΜvZ
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);			//OρΜΚu©η»έΜΚuάΕΜxNg
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);	//Έ_©ηOρΜΚuάΕΜxNg
						D3DXVec3Normalize(&N, &P[0]);															//OρΜΚu©η»έΜΚuάΕΜxNgπ³K»·ι

						D3DXVec3Cross(&R[0], &P[1], &V[Count]);		//Έ_©ηOρΜΚuάΕΜxNgΖι`ΜΣΜxNgΜOΟ
						D3DXVec3Cross(&R[1], &N, &V[Count]);		//OρΜΚu©η»έΜΚuάΕΜPΚxNgΖι`ΜΣΜxNgΜOΟ

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;					//OρΜΚu©ηπ_άΕΜxNgΜ·³

						if (fResult > 0)
						{
							fResult -= 0.1f;
						}
						else if (fResult < 0)
						{
							fResult += 0.1f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;			//vZpΜxNg
						float Dot, Lenght1, Lenght2, Alpha;					//vZpΜΟ

						//ι
						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));		//π_ΐW
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);					//Έ_©η»έΜΚuάΕΜxNg
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);						//Έ_©ηπ_άΕΜxNg

						D3DXVec3Normalize(&N, &VtxtoCross);			//Έ_©ηπ_άΕΜxNgπ³K»·ι

						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);											//ΰΟπvZ·ι
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//Έ_©ηπ_άΕΜxNgΜ·³
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//Έ_©η»έΜΚuάΕΜxNgΜ·³

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));				//γΜxNgΜΤΜpxπvZ·ι

							fResult = (Lenght2 * cosf(Alpha));

							//V΅’ΐWΜvZ
							thisPos.x = Vtx[Count].x + (N.x * fResult);
							thisPos.z = Vtx[Count].z + (N.z * fResult);
						}
						else
						{//G[ͺN«½ηAV΅’ΐWπφ]Ζ―ΆΙ·ι
							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				if (GetParent() != nullptr)
				{//eΜΚuΜέθ
					GetParent()->SetPos(thisPos - GetRelativePos());
				}

				return true;				//trueπΤ·
			}
		}
	}

	return false;				//falseπΤ·
}