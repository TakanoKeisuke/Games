//=============================================================================
//
// gimmick.h
// Author : ûüì]
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "objectX.h"

//M~bNNX
class CGimmick : public CObjectX
{
public:
	enum GIMMICK_TYPE
	{
		TYPE_NONE = 0,
		TYPE_MOVE_X,
		TYPE_MOVE_Y,
		TYPE_MOVE_Z,
		TYPE_FALL,
		TYPE_FALL_LONG,

		TYPE_MAX
	};
	explicit CGimmick(int nPriority = PRIORITY_3);		//RXgN^
	~CGimmick() override;								//fXgN^

	HRESULT Init(void) override;						//ú»
	void Uninit(void) override;							//I¹
	void Update(void) override;							//XV
	void Draw(void) override;							//`æ
	void TypeEffect(void);								//íÞ²ÆÌ

	bool PushPlayer(void);								//vC[Ìo
	bool GetLanding(void) { return m_bLanding; }		//nµÄ¢é©Ìæ¾
	bool Collision(D3DXVECTOR3 pos);					//½è»è

	void Fall(void);																									//º
	void Respawn(const D3DXVECTOR3 pos,float effect, GIMMICK_TYPE type);												//Ä¶¬
	static CGimmick* Create(const D3DXVECTOR3 pos, const float effect, GIMMICK_TYPE type, const float speed);			//¶¬

private:
	//oÏ
	GIMMICK_TYPE m_type;								//M~bNÌíÞ
	D3DXVECTOR3 OriginPos;								//ÅÌpos
	int m_nFallTime;									//¿éÜÅÔ
	int m_nRespawnTime;									//Ä¶¬Ô
	int m_nInvincibleCnt;
	float m_fHeight;									//TCJ[uÌ
	float m_fSpeed;										//¬x
	float m_fRange;										//ÍÍ
	float m_feffect;									//øÊÊÌÛ¶
	bool m_bCountStart;									//¿éÍ¶ßé©
	bool m_bLanding;									//nµÄ¢é©
	bool m_bRespawn;									//¿½çÄ¶¬·é
};

#endif