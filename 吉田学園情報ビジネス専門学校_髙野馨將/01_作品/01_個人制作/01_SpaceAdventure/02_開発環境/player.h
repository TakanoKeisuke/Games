//=============================================================================
//
// player
// Author:ûüì]
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include<vector>

//Oûé¾
class CModel;
class CBoxHitbox;
class CCylinderHitbox;
class CSphereHitbox;
class CMotion;
class CShadow;

//vC[NX
class CPlayer : public CObject
{
public:
	enum PLAYER_TYPE
	{
		TYPE_NONE = 0,
		TYPE_SPEED,
		TYPE_JUMP,
		TYPE_FLY,

		TYPE_MAX
	};

	static const int MAX_MODEL = 9;								//fÌÅå
	static const int MAX_WORD = 512;

	explicit CPlayer(int nPriority = PRIORITY_3);					//I[o[Ch³ê½RXgN^
	~CPlayer() override;											//fXgN^

	//oÖ
	virtual HRESULT Init(void) override;							//ú»
	virtual void CPlayer::Uninit(void) override;					//I¹
	virtual void Update(void) override;								//XV
	virtual void Draw(void) override;								//`æ
	void LoadPlayer(void);											//vC[fÌÇÝÝ
	void Input(void);												//üÍ
	void CollisionObj(void);										//IuWFNgÆ½Á½Ì
	void CollisionStage(void);										//Xe[WÌ½è»è
	void CollisionGimmick(void);									//eÆM~bNÌ½è»è
	void Attack(void);												//U
	void BuffPlayer(void);											//vC[Ì­»

	void BuffEffect(PLAYER_TYPE type);								//­»øÊ
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//posÌÝè
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//sizeÌÝè
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }			//rotÌÝè
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }		//moveÌÝè

	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//posÌæ¾
	const D3DXVECTOR3 GetPosOld(void) { return m_posOld; }			//posÌæ¾
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//sizeÌæ¾
	const D3DXVECTOR3 GetMove(void) { return m_move; }				//moveÌæ¾
	const int GetLife(void) { return m_nLife; }						//ÌÍÌæ¾
	bool GetInside(void) { return m_bInside; }						//½è»èÌæ¾
	bool GetShadow(void) { return m_bShadow; }						//eÌæ¾
	CModel *GetModel(int nCnt) { return m_apModel[nCnt]; }			//fÌæ¾
	CMotion *GetMotion() { return m_pMotion; }						//[VÌæ¾
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//rotÌæ¾
	
	//ÃIoÖ
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority); //¶¬

private:
	//ÃIoÏ
	static float m_fAcceleration;				//Á¬W
	static float m_fJump;						//WvÍ
	static int m_nGoalCnt;						//S[©çtF[hÌÔ

	//oÏ
	CModel *m_apModel[MAX_MODEL];				//fÌîñ
	CMotion *m_pMotion;							//[VÌîñ
	CSphereHitbox *m_pHitbox;					//qbg{bNX
	CCylinderHitbox *m_pAttackHitbox;			//UÌqbg{bNX
	D3DXQUATERNION m_quat;						//NH[^jI
	D3DXVECTOR3 m_Vec;							//isûüxNg
	D3DXVECTOR3	m_pos;							//Êu
	D3DXVECTOR3 m_posOld;						//OñÌÊu
	D3DXVECTOR3	m_Originpos;							//Êu
	D3DXVECTOR3 m_rot;							//ü«
	D3DXVECTOR3 m_size;							//TCY
	D3DXVECTOR3 m_rotDest;						//ÚIÌpx
	D3DXVECTOR3 m_move;							//Ú®Ê
	D3DXVECTOR3 m_vecAxis;						//²xNg
	D3DXVECTOR3 m_norVec;						//@üxNg
	D3DXMATRIX m_mtxWorld;						//[h}gbNX
	D3DXMATRIX m_mtxQuat;						//NH[^jI
	PLAYER_TYPE m_type;							//vC[ÌíÞ

	int m_nLife;								//ÌÍ
	int m_nCntModel;							//fðJEg
	int m_nInvincibleCnt;						//³GÔ
	int m_nBuffTime;							//­»Ô
	int m_nCntGoal;								//S[ãtF[h·éÜÅÌÔ
	float m_fCntSE;								//SEÌJEg
	float m_fCT;								//N[^C
	float m_fFriction;							//CW
	float m_fBuffQuantity;						//­»øÊÌÊ
	float m_fDash;								//_bV¬x
	float m_fSlowFall;							//º¬xáº
	std::vector<bool> m_bCollisionField;		//nÊÌ½è»è
	bool m_bGoal;								//S[µ½©
	bool m_bGimmick;							//M~bNÉæÁÄ¢é©
	bool m_bJumping;							//WvµÄ¢é©
	bool m_bCollisionPlanet;					//f¯Ì½è»è
	bool m_bInside;								//f¯ÌÍÍÌà¤ÉüÁÄ¢é©
	bool m_bModel;								//fÌL³
	bool m_bShadow;								//eÌL³
};

#endif