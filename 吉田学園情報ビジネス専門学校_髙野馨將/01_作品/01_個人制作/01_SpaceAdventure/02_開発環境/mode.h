//=============================================================================
//
// Q[
// Author:ûüì]
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

#include "object.h"

//Oûé¾
class CTitle;
class CGame;
class CResult;
class CRanking;
class CTutorial;

//[hNX
class CMode : public CObject
{
public:
	CMode();			//RXgN^
	~CMode() override;	//fXgN^
	//¼zÖ
	virtual HRESULT Init() override { return S_OK; }	//ú»
	virtual void Uninit() override {}					//I¹
	virtual void Update() override {}					//XV
	virtual void Draw() override {}						//`æ
	void SetPos(const D3DXVECTOR3 pos) { pos; }		//ÊuÌÝè
	const D3DXVECTOR3 GetPos(void) { return{}; }				//posÌæ¾
	const D3DXVECTOR3 GetSize(void) { return{}; }				//sizeÌæ¾
	
private:
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CRanking *m_pRanking;
};

#endif