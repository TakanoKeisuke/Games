//=============================================================================
//
// life_gauge.h
// Author:ûüì]
//
//=============================================================================
#ifndef _LIFE_GAUGE_H_
#define _LIFE_GAUGE_H_

#include "object2D.h"

//HPQ[WNX
class CLife_gauge : public CObject2D
{
public:
	explicit CLife_gauge(int nPriority = PRIORITY_4);		//I[o[Ch³ê½RXgN^
	~CLife_gauge() override;									//fXgN^

	//oÖ
	HRESULT Init() override;							//ú»
	void Uninit() override;								//I¹
	void Update() override;								//XV
	void Draw(void) override;							 //`æ

	//ÃIoÖ
	static CLife_gauge *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size); //¶¬

private:
	//oÏ
	LPDIRECT3DTEXTURE9	m_pTexture;				//eNX`ÖÌ|C^
};

#endif