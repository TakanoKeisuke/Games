//=============================================================================
//
// sphereHitbox.cpp
// Author : ����]��
//
//=============================================================================
#include "SphereHitbox.h"

//======================================================
//�R���X�g���N�^
//======================================================
CSphereHitbox::CSphereHitbox()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CSphereHitbox::~CSphereHitbox()
{
}

//======================================================
//����������
//======================================================
HRESULT CSphereHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	return S_OK;
}

//======================================================
//�I������
//======================================================
void CSphereHitbox::Uninit(void)
{
	//�I������
	CHitbox::Uninit();
}

//======================================================
//�X�V����
//======================================================
void CSphereHitbox::Update(void)
{
	if (GetType() == TYPE_PLAYER)
	{//�v���C���[�̃q�b�g�{�b�N�X��������A
		std::vector <CHitbox*>* pHbx = GetAllHitbox();			//�S���̃q�b�g�{�b�N�X���擾����

		for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
		{//�擾�����q�b�g�{�b�N�X��S�����肷��

			if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
			{//�e�������ł͂Ȃ�������

				HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();			//�`�̎擾

				switch (shape)
				{
				case CHitbox::SHAPE_SPHERE:

				{//�X�t�B�A�̏ꍇ

					if (SphereSphereHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize(), pHbx->data()[nCnt]->GetEffect()))
					{//���������ꍇ

						if (!GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							pHbx->data()[nCnt]->SetCollisionState(true);		//����������Ԃɂ���

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
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
				{//��`�̏ꍇ

					if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
					{//���������ꍇ

						if (!GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
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
				{//�V�����_�[�̏ꍇ

					if (SphereCylinderHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize(), pHbx->data()[nCnt]->GetEffect()))
					{//���������ꍇ

						if (!GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							pHbx->data()[nCnt]->SetCollisionState(true);		//����������Ԃɂ���

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
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

	//�X�V
	CHitbox::Update();
}

//======================================================
//��������
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CSphereHitbox* pHitbox = new CSphereHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	//�����ɕK�v�ȏ��
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);

	return pHitbox;
}

//======================================================
//��������
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent)
{
	CSphereHitbox* pHitbox = new CSphereHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	//�����ɕK�v�ȏ��
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�

	return pHitbox;
}

//======================================================
//��������
//======================================================
CSphereHitbox* CSphereHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect)
{
	//�q�b�g�{�b�N�X�̐���
	CSphereHitbox* pHitbox = new CSphereHitbox;

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	//�����ɕK�v�ȏ��
	CreateData(pos, RelativePos, size, type, pParent, pHitbox);
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�
	pHitbox->SetEffect(effect);							//�G�t�F�N�g�̐ݒ�

	return pHitbox;
}

//======================================================
//�����ɕK�v�ȏ��
//======================================================
void CSphereHitbox::CreateData(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, CSphereHitbox *Hitbox)
{
	Hitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	Hitbox->SetPos(pos);								//�ʒu�̐ݒ�
	Hitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	Hitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	Hitbox->SetType(type);								//��ނ̐ݒ�
	Hitbox->SetShape(CHitbox::SHAPE_SPHERE);			//�`�̐ݒ�
	Hitbox->SetParent(pParent);							//�e�̐ݒ�
}

//======================================================
//�X�t�B�A�ƃV�����_�[�̓����蔻��
//======================================================
bool CSphereHitbox::SphereCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect)
{
	D3DXVECTOR3 thisPos, thisSize;				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	thisPos = GetPos();							//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	thisSize = GetSize();						//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	float fTop, fBottom;				//���̃q�b�g�{�b�N�X�̏㑤�Ɖ���

	fTop = pos.y + size.y;				//�㑤�̍��W
	fBottom = pos.y;					//�����̍��W

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//Y���W���d�Ȃ����ꍇ

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//����
		fRadius = size.x + thisSize.x;				//���a�̑����Z

		if (fDistance < fRadius)
		{//�����͔��a�̑����Z��菬��������
			if (effect == EFFECT_GOAL || effect == EFFECT_JUMP || effect == EFFECT_HEAL || effect == EFFECT_SPEED || effect == EFFECT_CHECKPOINT || effect == EFFECT_MAX)
			{//�����o�������Ȃ�
				return true;
			}
			D3DXVECTOR3 thisLast = GetLastPos();				//�O��̈ʒu�̎擾
			D3DXVECTOR3 parentPos = GetParent()->GetPos();		//�e�̎擾

			D3DXVECTOR3 dist = thisPos - pos;					//�������v�Z����
			float fHeight = parentPos.y;						//���݂̍���
			dist.y = 0.0f;
			D3DXVec3Normalize(&dist, &dist);					//�����𐳋K������
			dist.x *= fRadius + 0.001f;
			dist.z *= fRadius + 0.001f;
			dist.x += pos.x;
			dist.z += pos.z;
			parentPos = dist - GetRelativePos();				//�V�����ʒu���v�Z����
			parentPos.y = fHeight;								//���̍�����ݒ肷��
			GetParent()->SetPos(parentPos);						//�e�̈ʒu�̐ݒ�

			return true;				//true��Ԃ�
		}
	}

	return false;						//false��Ԃ�
}

//======================================================
//�_�Ƌ�`�̓����蔻��
//======================================================
bool CSphereHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	D3DXVECTOR3 thisSize = GetSize();					//���̃q�b�g�{�b�N�X�̃T�C�Y�擾
	D3DXVECTOR3 thisLastPos = GetLastPos();				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y���W���d�Ȃ����ꍇ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//�v�Z�p�̃x�N�g��
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//�v�Z�p�̃}�g���b�N�X
		float fResult;											//�v�Z�p�̕ϐ�

		//���_�̑��΍��W�̐ݒ�
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//���΍��W�����΍��W�ɕϊ�����
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

		//�e���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g�����v�Z����
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//��̃x�N�g���̊O�ς��v�Z����
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//�S���̊O�ς̕�����������������A��������

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				//�V�����ʒu�̌v�Z
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);                                    //�O��̈ʒu�̐ݒ�

				GetParent()->SetPos(thisPos - GetRelativePos());        //�e�̈ʒu�̐ݒ�
				SetPos(thisPos);

				return true;            //true��Ԃ�
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//�����瓖�������ꍇ

				//�V�����ʒu�̌v�Z
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�

				return true;			//true��Ԃ�
			}
			else
			{//�����瓖�������ꍇ

				for (int Count = 0; Count < 4; Count++)
				{//�ǂ����瓖�����������߂�
					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//�ǂ����瓖������������������
						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g��
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//�O��̈ʒu���璸�_�܂ł̃x�N�g��
						D3DXVec3Normalize(&N, &P[0]);			//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g���𐳋K������

						//��̃x�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O�ς��v�Z����
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

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//��_���W
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g��
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//���_�����_�܂ł̃x�N�g��

						D3DXVec3Normalize(&N, &VtxtoCross);			//���_�����_�܂ł̃x�N�g���𐳋K������

																	//���_�����_�܂ł̃x�N�g���ƒ��_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g���̓��ς��v�Z����
						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//��̃x�N�g���̒������v�Z����
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//��̃x�N�g���̒������v�Z����

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{ //�V�����ʒu���v�Z����
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));
							fResult = (Lenght2 * cosf(Alpha));

							//�V�����ʒu�̐ݒ�
							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{//�G���[����������A�V�����ʒu����_���W�ɐݒ肷��
							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				SetPos(thisPos);										//���݂̈ʒu�̐ݒ�

				return true;			//true��Ԃ�
			}
		}
	}

	return false;						//false��Ԃ�
}

//======================================================
//�X�t�B�A�ƃX�t�B�A�̓����蔻��
//======================================================
bool CSphereHitbox::SphereSphereHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, INTERACTION_EFFECT effect)
{
	D3DXVECTOR3 thisPos, thisSize;				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	thisPos = GetPos();							//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	thisSize = GetSize() / 2.0f;				//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	float fDistance, fRadius;
	fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//����
	fRadius = (size.x / 2.0f) + thisSize.x;				//���a�̑����Z

	if (pos.y >= thisPos.y - thisSize.y && pos.y + size.y <= thisPos.y + thisSize.y)
	{
		if (fDistance < fRadius)
		{//�����͔��a�̑����Z��菬����������
			if (effect != CHitbox::EFFECT_FLY)
			{
				D3DXVECTOR3 thisLast = GetLastPos();				//�O��̈ʒu�̎擾
				D3DXVECTOR3 parentPos = GetParent()->GetPos();		//�e�̎擾

				D3DXVECTOR3 dist = thisPos - pos;					//�������v�Z����
				float fHeight = parentPos.y;						//���݂̍���
				dist.y = 0.0f;
				D3DXVec3Normalize(&dist, &dist);					//�����𐳋K������
				dist.x *= fRadius + 0.001f;
				dist.z *= fRadius + 0.001f;
				dist.x += pos.x;
				dist.z += pos.z;
				parentPos = dist - GetRelativePos();				//�V�����ʒu���v�Z����
				parentPos.y = fHeight;								//���̍�����ݒ肷��
				GetParent()->SetPos(parentPos);						//�e�̈ʒu�̐ݒ�
			}
			return true;				//true��Ԃ�
		}
	}

	return false;						//false��Ԃ�
}