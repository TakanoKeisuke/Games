//========================================================
//
//e
//Author:ûüì]
//
//========================================================
#ifndef _SHADOW_H_				//±Ì}Nè`ª³êÄ¢È©Á½ç
#define _SHADOW_H_				//ñdCN[hh~Ì}Nè`

#include "object3d.h"

//eNX
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = PRIORITY_3);			//I[o[Ch³ê½RXgN^
	~CShadow() override;									//fXgN^

	//oÖ
	HRESULT Init(void); //ú»
	void Uninit(void); //I¹
	void Update(void); //XV
	void Draw(void); //`æ
	const D3DXVECTOR3 GetPos(void) { return{}; }				//posÌæ¾
	const D3DXVECTOR3 GetSize(void) { return{}; }				//sizeÌæ¾
	//ÃIoÖ
	static CShadow *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, int nPriority); //¶¬

private:
	//oÏ
	bool m_bTexture;							//eNX`ÌL³
};

#endif