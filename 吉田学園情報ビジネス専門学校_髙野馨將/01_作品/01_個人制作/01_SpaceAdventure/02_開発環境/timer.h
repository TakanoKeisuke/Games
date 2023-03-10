//=============================================================================
//
// timer.h
// Author:ϋόμ]
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "object2D.h"

//OϋιΎ
class CNumber;

//^C}[NX
class CTimer : public CObject2D
{
public:
	const static int MAX_TIMER = 3;

	explicit CTimer(int nPriority = PRIORITY_4);		//I[o[Ch³κ½RXgN^
	~CTimer() override;									//fXgN^

	//oΦ
	HRESULT Init() override;							//ϊ»
	void Uninit() override;								//IΉ
	void Update() override;								//XV
	void Draw(void) override;							//`ζ

	void SetTimer(int nTimer);									//^C}[Μέθ
	void SubTimer(int nValue) { SetTimer(m_nTimer - nValue); }  //^C}[ΜΑZ
	int GetTimer(void) { return m_nTimer; }						//^C}[ΜζΎ
	//ΓIoΦ
	static CTimer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);		//Ά¬

private:
	//oΟ
	CNumber *m_apNumber[MAX_TIMER];				//Number^Μzρ
	int m_nTimer;								//^C}[Μl
	int m_nCntTimer;							//^C}[ΜJEg
};

#endif