//=============================================================================
//
// f
// Author:ûüì]
//
//=============================================================================
#ifndef _CMODEL_H_
#define _CMODEL_H_

#include "object.h"

//fNX
class CModel
{
public:
	CModel();								//RXgN^
	~CModel();								//fXgN^

	//oÖ
	HRESULT Init(void);		//ú»
	void Uninit(void);		//I¹
	void Update(void);		//XV
	void Draw(void);		//`æ
	void Shadow(void);		//½Êe

	void SetParent(CModel *pModel) { m_pParent = pModel; }				//eÌÝè
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }				//ÊuÌÝè
	void SetShadowPos(const D3DXVECTOR3 &pos) { m_ShadowPos = pos; }	//eÌÊuÌÝè
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }				//pxÌÝè
	void SetId(const int nId) { m_nMatId = nId; }						//ÔÌÝè

	D3DXVECTOR3 GetPos(void) { return m_pos; }							//posÌæ¾
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }					//[h}gbNXÌæ¾
	D3DXVECTOR3 GetShadowPos(void) { return m_Shadow; }					//eÌÊuÌæ¾

	//ÃIoÖ
	void SetMatrix(D3DXMATRIX *mtx) { m_mtxWorld = *mtx; }
	void SetModel(const char *pFileName);
	static CModel *Create(const D3DXVECTOR3 &pos); //¶¬

private:
	//oÏ
	CModel *m_pParent;							//efÖÌ|C^
	D3DXVECTOR3	m_pos;							//fÌÀW
	D3DXVECTOR3	m_ShadowPos;					//eÌÀW
	D3DXVECTOR3	m_Shadow;						//eÌÀW
	D3DXVECTOR3 m_rot;							//ü«
	D3DXMATRIX m_mtxShadow;						//eÌ}gbNX
	D3DXMATRIX m_mtxWorld;						//[h}gbNX
	LPD3DXMESH m_MeshModel;						//bVîñÖÌ|C^
	LPD3DXBUFFER m_BuffMatModel;				//}eAîñÖÌ|C^
	DWORD m_NumMatModel;						//}eAîñÌ
	LPDIRECT3DTEXTURE9 *m_pTexture;				//eNX`|C^
	bool m_bModel;								//fÌL³
	int m_nMatId;								//}eAÌÔ
};

#endif