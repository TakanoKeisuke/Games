//======================================================
//
//オブジェクトX
//Author:髙野馨將
//
//======================================================
#include "objectX.h"
#include "application.h"
#include "meshfield.h"
#include "input.h"
#include "stage.h"
#include <assert.h>

//======================================================
//オーバーロードされたコンストラクタ
//======================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{

}

//======================================================
//デストラクタ
//======================================================
CObjectX::~CObjectX()
{
	//assert(m_MeshModel == nullptr);
}

//======================================================
//初期化処理
//======================================================
HRESULT CObjectX::Init(void)
{
	//初期化
	m_bModel = false;
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_MeshModel != nullptr)
	{
		m_MeshModel->Release();
		m_MeshModel = nullptr;
	}

	if (m_bModel)
	{
		//マテリアルの破棄
		if (m_BuffMatModel != nullptr)
		{
			m_BuffMatModel->Release();
			m_BuffMatModel = nullptr;
		}
	}

	Flag();
}

//======================================================
//更新処理
//======================================================
void CObjectX::Update(void)
{
	if (m_rotation != nullptr)
	{//回転速度が0ではなかったら
		m_rot += m_rotation;			//回転角度を更新する
	}
	if (m_move != nullptr)
	{//移動量が0ではなかったら
		m_pos += m_move;				//移動量を更新する
	}
}

//======================================================
//描画処理
//======================================================
void CObjectX::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;	
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;			
	//マテリアルデータへのポインタ
	D3DXMATERIAL * pMat;			

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//メッシュの情報取得
	std::vector<CMeshField*> pMesh = CStage::GetMesh();

	for (int nCnt = 0; nCnt < CStage::m_nMaxMesh; nCnt++)
	{
		if (m_pos.y >= pMesh[nCnt]->GetPos().y)
		{
			//平面投影
			Shadow();
		}
	}
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_MeshModel->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//描画処理
//======================================================
void CObjectX::DrawSphere()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;
	//マテリアルデータへのポインタ
	D3DXMATERIAL * pMat;

	//平面投影
	Shadow();

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_MeshModel->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//平面投影
//======================================================
void CObjectX::Shadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	//ライトの取得
	CLight *pLight = CApplication::GetLight();
	D3DXVECTOR3 vecDir = pLight->GetLight().Direction;
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-vecDir.x, -vecDir.y, -vecDir.z, 0.0f);
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;
	//影のマトリックス
	D3DXMATRIX mtxShadow;
	//平面
	D3DXPLANE planeField;
	//情報
	D3DXVECTOR3 pos, normal;
	DWORD ambient;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);
	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//法線と平面の一点から平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//ライトと平面から影行列
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);
	//ワールドマトリックスを掛け合わせて設定
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);
	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);
	//マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)m_BuffMatModel->GetBufferPointer();
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);

	for (int nCntMat = 0; nCntMat < (int)m_NumMatModel; nCntMat++)
	{
		// マテリアル情報を保存し、色とライトの色を黒に設定
		D3DMATERIAL9 pMatD3D = pMat[nCntMat].MatD3D;
		pMatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pMatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//マテリアルの設定
		pDevice->SetRenderState(D3DRS_AMBIENT, 0xff000000);	//カラー
		pDevice->SetMaterial(&pMatD3D);
		//影の描画
		m_MeshModel->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//======================================================
//生成処理
//======================================================
CObjectX *CObjectX::Create(const D3DXVECTOR3 &pos, int nPriority)
{
	//動的確保
	CObjectX *pObjectX;
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{
		//初期化
		pObjectX->Init();
		pObjectX->SetPos(pos);
	}

	return pObjectX;
}

//======================================================
//テクスチャの読み込み
//======================================================
void CObjectX::LoadModel(const char *aFileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(aFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMatModel,
		NULL,
		&m_NumMatModel,
		&m_MeshModel);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットの数
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = m_MeshModel->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_MeshModel->GetFVF());
	//頂点バッファのロック
	m_MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		//最小値
		if (vtx.x < m_Min.x)
		{
			m_Min.x = vtx.x;
		}
		if (vtx.y < m_Min.y)
		{
			m_Min.y = vtx.y;
		}
		if (vtx.z < m_Min.z)
		{
			m_Min.z = vtx.z;
		}
		//最大値
		if (vtx.x > m_Max.x)
		{
			m_Max.x = vtx.x;
		}
		if (vtx.y > m_Max.y)
		{
			m_Max.y = vtx.y;
		}
		if (vtx.z > m_Max.z)
		{
			m_Max.z = vtx.z;
		}
		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	m_size = m_Max - m_Min;
	m_bModel = true;
}