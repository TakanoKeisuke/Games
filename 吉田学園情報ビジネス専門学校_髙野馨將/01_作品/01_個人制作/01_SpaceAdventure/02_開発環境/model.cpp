//======================================================
//
//f
//Author:ûüì]
//
//======================================================
#include "model.h"
#include "application.h"
#include "input.h"
#include "game.h"
#include <assert.h>
#include "player.h"

//======================================================
//RXgN^
//======================================================
CModel::CModel()
{
	m_nMatId = -1;
}

//======================================================
//fXgN^
//======================================================
CModel::~CModel()
{
}

//======================================================
//ú»
//======================================================
HRESULT CModel::Init(void)
{
	//ú»
	m_bModel = false;
	m_pTexture = nullptr;
	D3DXMatrixIdentity(&m_mtxShadow);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//======================================================
//I¹
//======================================================
void CModel::Uninit(void)
{
	//bVÌjü
	if (m_MeshModel != nullptr)
	{
		m_MeshModel->Release();
		m_MeshModel = nullptr;
	}

	//}eAÌjü
	if (m_BuffMatModel != nullptr)
	{
		m_BuffMatModel->Release();
		m_BuffMatModel = nullptr;
	}

	//eNX`Ìjü
	for (int nCnt = 0; nCnt < (int)m_NumMatModel; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}

	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//======================================================
//XV
//======================================================
void CModel::Update(void)
{
}

//======================================================
//`æ
//======================================================
void CModel::Draw(void)
{
	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	CPlayer *pPlayer = CGame::GetPlayer();

	//vZp}gbNX
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;

	//»ÝÌ}eAÛ¶p
	D3DMATERIAL9 matDef;

	//}eAf[^ÖÌ|C^
	D3DXMATERIAL *pMat;

	//[h}gbNXÌú»
	D3DXMatrixIdentity(&m_mtxWorld);

	//ü«ð½f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//Êuð½f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//[h}gbNXð|¯í¹ÄÝè
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	
	if (pPlayer != nullptr)
	{
		if (!pPlayer->GetInside())
		{
			//½Êe
			Shadow();
		}
	}

	//[h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//»ÝÌ}eAðÛ
	pDevice->GetMaterial(&matDef);

	//}eAÌ|C^ðæ¾
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//}eAÌÝè
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// eNX`ÌÝè
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//fp[cÌ`æ
		m_MeshModel->DrawSubset(nCntMat);
	}

	//ÛµÄ¢½}eAð³Éß·
	pDevice->SetMaterial(&matDef);

	//eNX`Ìð
	pDevice->SetTexture(0, NULL);
}

//======================================================
//¶¬
//======================================================
CModel *CModel::Create(const D3DXVECTOR3 &pos)
{
	//®ImÛ
	CModel *pModel = new CModel;

	if (pModel != nullptr)
	{
		//ú»
		pModel->Init();
		pModel->m_pos = pos;
	}

	return pModel;
}

//======================================================
//ú»
//======================================================
void CModel::SetModel(const char *pFileName)
{
	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xt@CÌÇÝÝ
	D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMatModel,
		NULL,
		&m_NumMatModel,
		&m_MeshModel);

	// eNX`
	m_pTexture = new LPDIRECT3DTEXTURE9[m_NumMatModel];

	//îñªüÁÄÈ©Á½ç
	assert(m_pTexture != nullptr);

	// obt@Ìæª|C^ðD3DXMATERIALÉLXgµÄæ¾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	// ebVÌ}eAîñðæ¾·é
	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//îñÌú»
		m_pTexture[nCntMat] = nullptr;

		//|SÉ\èt¯éeNX`ÌÇÝÝ
		D3DXCreateTextureFromFile(pDevice,
			pMat[nCntMat].pTextureFilename,
			&m_pTexture[nCntMat]);
	}
}

//======================================================
//½Êe
//======================================================
void CModel::Shadow(void)
{
	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//CgÌæ¾
	CLight *pLight = CApplication::GetLight();
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);

	//»ÝÌ}eAÛ¶p
	D3DMATERIAL9 matDef;

	//vC[
	CPlayer *pPlayer = CGame::GetPlayer();

	//}eAf[^ÖÌ|C^
	D3DXMATERIAL *pMat;

	//½Ê
	D3DXPLANE planeField;

	//îñ
	D3DXVECTOR3 normal;
	DWORD ambient;

	//[h}gbNXÌú»
	D3DXMatrixIdentity(&m_mtxShadow);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//@üÆ½ÊÌê_©ç½Êðì¬
	D3DXPlaneFromPointNormal(&planeField, &m_ShadowPos, &normal);

	//CgÆ½Ê©çesñ
	D3DXMatrixShadow(&m_mtxShadow, &vecLight, &planeField);

	//[h}gbNXð|¯í¹ÄÝè
	D3DXMatrixMultiply(&m_mtxShadow, &m_mtxWorld, &m_mtxShadow);

	//VhE}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxShadow);
	
	//sñÌeÌÊuðÏ··é
	D3DXVec3TransformCoord(&m_Shadow, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &m_mtxShadow);

	//»ÝÌ}eAðÛ
	pDevice->GetMaterial(&matDef);

	//}eAÌ|C^ðæ¾
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		// }eAîñðÛ¶µAFÆCgÌFðÉÝè
		D3DMATERIAL9 pMatD3D = pMat[nCntMat].MatD3D;
		pMatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//}eAÌÝè
		pDevice->SetRenderState(D3DRS_AMBIENT, 0xff000000);	//J[
		pDevice->SetMaterial(&pMatD3D);

		if (pPlayer->GetShadow())
		{
			//eÌ`æ
			m_MeshModel->DrawSubset(nCntMat);
		}
	}

	//ÛµÄ¢½}eAð³Éß·
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	//eNX`Ìð
	pDevice->SetTexture(0, NULL);
}