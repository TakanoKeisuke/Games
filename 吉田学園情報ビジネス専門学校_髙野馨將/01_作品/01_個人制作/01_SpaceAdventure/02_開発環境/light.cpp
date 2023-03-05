//========================================================
//
//���C�g
//Author:����]��
//
//========================================================
#include "light.h"
#include "application.h"

//======================================================
//�R���X�g���N�^
//======================================================
CLight::CLight()
{
}

//======================================================
//�f�X�g���N�^
//======================================================
CLight::~CLight()
{//���������Ȃ�
}

//====================================
//���C�g�̏���������
//====================================
void CLight::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];				//���C�g�̕����x�N�g��
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g���N���A
		ZeroMemory(&m_aLight[0], sizeof(m_aLight));
		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		//���C�g�̊g�U����ݒ�(�F)
		m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.5f, -1.0f, 0.5f);
		//����������(�傫��1�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		m_aLight[nCntLight].Direction = vecDir[nCntLight];
		//���C�g��ݒ�
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
		//���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//====================================
//���C�g�̏I������
//====================================
void CLight::Uninit(void)
{
}

//====================================
//���C�g�̍X�V����
//====================================
void CLight::Update(void)
{
}