//=============================================================================
//
// player
// Author:ϋόμ]
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include<vector>

//OϋιΎ
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

	static const int MAX_MODEL = 9;								//fΜΕε
	static const int MAX_WORD = 512;

	explicit CPlayer(int nPriority = PRIORITY_3);					//I[o[Ch³κ½RXgN^
	~CPlayer() override;											//fXgN^

	//oΦ
	virtual HRESULT Init(void) override;							//ϊ»
	virtual void CPlayer::Uninit(void) override;					//IΉ
	virtual void Update(void) override;								//XV
	virtual void Draw(void) override;								//`ζ
	void LoadPlayer(void);											//vC[fΜΗέέ
	void Input(void);												//όΝ
	void CollisionObj(void);										//IuWFNgΖ½Α½Μ
	void CollisionStage(void);										//Xe[WΜ½θ»θ
	void Attack(void);												//U
	void BuffPlayer(void);											//vC[Μ­»

	void BuffEffect(PLAYER_TYPE type);								//­»ψΚ
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }				//posΜέθ
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }		//sizeΜέθ
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }			//rotΜέθ
	void SetMove(const D3DXVECTOR3 &move) { m_move = move; }		//moveΜέθ

	const D3DXVECTOR3 GetPos(void) { return m_pos; }				//posΜζΎ
	const D3DXVECTOR3 GetPosOld(void) { return m_posOld; }			//posΜζΎ
	const D3DXVECTOR3 GetSize(void) { return m_size; }				//sizeΜζΎ
	const D3DXVECTOR3 GetMove(void) { return m_move; }				//moveΜζΎ
	const int GetLife(void) { return m_nLife; }						//ΜΝΜζΎ
	bool GetInside(void) { return m_bInside; }						//½θ»θΜζΎ
	bool GetShadow(void) { return m_bShadow; }						//eΜζΎ
	CModel *GetModel(int nCnt) { return m_apModel[nCnt]; }			//fΜζΎ
	CMotion *GetMotion() { return m_pMotion; }						//[VΜζΎ
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//rotΜζΎ
	
	//ΓIoΦ
	static CPlayer *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &size, int nPriority); //Ά¬

private:
	//ΓIoΟ
	static float m_fAcceleration;				//Α¬W
	static float m_fJump;						//WvΝ

	//oΟ
	CModel *m_apModel[MAX_MODEL];				//fΜξρ
	CMotion *m_pMotion;							//[VΜξρ
	CSphereHitbox *m_pHitbox;					//qbg{bNX
	CCylinderHitbox *m_pAttackHitbox;			//UΜqbg{bNX
	D3DXQUATERNION m_quat;						//NH[^jI
	D3DXVECTOR3 m_Vec;							//isϋόxNg
	D3DXVECTOR3	m_pos;							//Κu
	D3DXVECTOR3 m_posOld;						//OρΜΚu
	D3DXVECTOR3	m_Originpos;							//Κu
	D3DXVECTOR3 m_rot;							//ό«
	D3DXVECTOR3 m_size;							//TCY
	D3DXVECTOR3 m_rotDest;						//ΪIΜpx
	D3DXVECTOR3 m_move;							//Ϊ?Κ
	D3DXVECTOR3 m_vecAxis;						//²xNg
	D3DXVECTOR3 m_norVec;						//@όxNg
	D3DXVECTOR3 shadowPos;
	D3DXMATRIX m_mtxWorld;						//[h}gbNX
	D3DXMATRIX m_mtxQuat;						//NH[^jI
	PLAYER_TYPE m_type;							//vC[Μνή

	int m_nLife;								//ΜΝ
	int m_nCntModel;							//fπJEg
	int m_nInvincibleCnt;						//³GΤ
	int m_nBuffTime;							//­»Τ
	int m_nCntGoal;								//S[γtF[h·ιάΕΜΤ
	float m_fCntSE;								//SEΜJEg
	float m_fCT;								//N[^C
	float m_fFriction;							//CW
	float m_fBuffQuantity;						//­»ψΚΜΚ
	float m_fDash;								//_bV¬x
	float m_fSlowFall;							//Ί¬xαΊ
	std::vector<bool> m_bCollisionField;		//nΚΜ½θ»θ
	bool m_bGoal;								//S[΅½©
	bool m_bGimmick;							//M~bNΙζΑΔ’ι©
	bool m_bJumping;							//Wv΅Δ’ι©
	bool m_bCollisionPlanet;					//f―Μ½θ»θ
	bool m_bInside;								//f―ΜΝΝΜΰ€ΙόΑΔ’ι©
	bool m_bModel;								//fΜL³
	bool m_bShadow;								//eΜL³
};

#endif