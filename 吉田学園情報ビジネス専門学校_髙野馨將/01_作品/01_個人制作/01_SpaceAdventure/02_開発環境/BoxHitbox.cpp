//=============================================================================
//
// BoxHitbox.cpp
// Author : ����]�� Ricci Alex
//
//=============================================================================
#include "BoxHitbox.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBoxHitbox::CBoxHitbox()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBoxHitbox::~CBoxHitbox()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CBoxHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CBoxHitbox::Uninit(void)
{
	CHitbox::Uninit();				//�I������
}

//=============================================================================
//�X�V����
//=============================================================================
void CBoxHitbox::Update(void)
{
	SetPos(GetPos() + D3DXVECTOR3(0.2f, 0.0f, 0.0f));

	std::vector <CHitbox*>* pHbx = GetAllHitbox();				//�S���̃q�b�g�{�b�N�X�̎擾����

	for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
	{//�S���̑��݂���q�b�g�{�b�N�X�𔻒肷��

		if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
		{//�e�������ł͂Ȃ�������

			HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();				//�`�̎擾

			switch (shape)
			{
			case CHitbox::SHAPE_SPHERE:
				break;

			case CHitbox::SHAPE_BOX:

			{//��`�̏ꍇ

				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
				{//���������ꍇ

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{//�G�t�F�N�g����������A�ݒ肷��
						pHbx->data()[nCnt]->SetEffect(GetEffect());
					}
				}

			}

			break;

			case CHitbox::SHAPE_CYLINDER:

			{//�~���̏ꍇ

				if (BoxBoxHit(pHbx->data()[nCnt]->GetPos(), D3DXVECTOR3(0.0f,0.0f,0.0f), pHbx->data()[nCnt]->GetSize()))
				{//���������ꍇ

					if (GetEffect() != EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() == EFFECT_MAX)
					{//�G�t�F�N�g����������A�ݒ肷��
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
	//�X�V����
	CHitbox::Update();
}

//======================================================
//��������
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	//�q�b�g�{�b�N�X�̐���
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}
	//�����Ɏg�����
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);

	return pHitbox;
}

//======================================================
//��������
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore)
{
	CBoxHitbox* pHitbox = new CBoxHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	//�����Ɏg�����
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	//�X�R�A�̐ݒ�
	pHitbox->SetScore(nScore);							

	return pHitbox;
}

//======================================================
//��������
//======================================================
CBoxHitbox* CBoxHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect)
{
	//�q�b�g�{�b�N�X�̐���
	CBoxHitbox* pHitbox = new CBoxHitbox;

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	//�����Ɏg�����
	CreateData(pos,RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�
	pHitbox->SetEffect(effect);							//�G�t�F�N�g�̐ݒ�

	return pHitbox;
}

//======================================================
//�����ɕK�v�ȏ��
//======================================================
void CBoxHitbox::CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject * pParent,CBoxHitbox* Hitbox)
{
	Hitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	Hitbox->SetPos(pos);								//�ʒu�̐ݒ�
	Hitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	Hitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	Hitbox->SetType(type);								//��ނ̐ݒ�
	Hitbox->SetShape(CHitbox::SHAPE_BOX);				//�`�̐ݒ�
	Hitbox->SetParent(pParent);							//�e�̐ݒ�
}

//======================================================
//�����蔻��̏���
//======================================================
bool CBoxHitbox::BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//���̃q�b�g�{�b�N�X�̈ʒu�̎擾
	D3DXVECTOR3 thisSize = GetSize();					//���̃q�b�g�{�b�N�X�̃T�C�Y�̎擾
	D3DXVECTOR3 thisLastPos = GetLastPos();				//���̃q�b�g�{�b�N�X�̑O��̈ʒu�̎擾

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y���W���d�Ȃ����ꍇ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;		//�v�Z�p�̃x�N�g��
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;						//�v�Z�p�̃}�g���b�N�X
		float fResult;												//�v�Z�p�̕ϐ�

		//���_�̑��΍��W�̐ݒ�
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//��΍��W�ɕϊ�����
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//�e���_���玟�̒��_�܂ł̃x�N�g�����v�Z����
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//�e���_���炱�̃C���X�^���X�̈ʒu�܂ł̃x�N�g�����v�Z����
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//��Ɍv�Z�����x�N�g���̊O�ς��v�Z����
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//�S���̊O�ς̕����������������瓖������
			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				thisPos.y = pos.y + size.y;								//��ɉ����o��
				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�������o��

				return true;											//true��Ԃ�
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y <= pos.y)
			{//�����瓖�������ꍇ

				thisPos.y = pos.y - thisSize.y;							//���ɉ����o��
				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�������o��

				return true;											//true��Ԃ�
			}
			else
			{//�����瓖�������ꍇ
				for (int Count = 0; Count < 4; Count++)
				{//�O��̈ʒu�Ɣ�ׂāA�ǂ����瓖�����������߂�

					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//��_���W�̌v�Z
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);			//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g��
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);	//���_����O��̈ʒu�܂ł̃x�N�g��
						D3DXVec3Normalize(&N, &P[0]);															//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g���𐳋K������

						D3DXVec3Cross(&R[0], &P[1], &V[Count]);		//���_����O��̈ʒu�܂ł̃x�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O��
						D3DXVec3Cross(&R[1], &N, &V[Count]);		//�O��̈ʒu���猻�݂̈ʒu�܂ł̒P�ʃx�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O��

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;					//�O��̈ʒu�����_�܂ł̃x�N�g���̒���

						if (fResult > 0)
						{
							fResult -= 0.1f;
						}
						else if (fResult < 0)
						{
							fResult += 0.1f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;			//�v�Z�p�̃x�N�g��
						float Dot, Lenght1, Lenght2, Alpha;					//�v�Z�p�̕ϐ�

						//���鏈��
						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));		//��_���W
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);					//���_���猻�݂̈ʒu�܂ł̃x�N�g��
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);						//���_�����_�܂ł̃x�N�g��

						D3DXVec3Normalize(&N, &VtxtoCross);			//���_�����_�܂ł̃x�N�g���𐳋K������

						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);											//���ς��v�Z����
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//���_�����_�܂ł̃x�N�g���̒���
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//���_���猻�݂̈ʒu�܂ł̃x�N�g���̒���

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));				//��̃x�N�g���̊Ԃ̊p�x���v�Z����

							fResult = (Lenght2 * cosf(Alpha));

							//�V�������W�̌v�Z
							thisPos.x = Vtx[Count].x + (N.x * fResult);
							thisPos.z = Vtx[Count].z + (N.z * fResult);
						}
						else
						{//�G���[���N������A�V�������W�����]�Ɠ����ɂ���
							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				if (GetParent() != nullptr)
				{//�e�̈ʒu�̐ݒ�
					GetParent()->SetPos(thisPos - GetRelativePos());
				}

				return true;				//true��Ԃ�
			}
		}
	}

	return false;				//false��Ԃ�
}