//======================================================
//
//motion.h
//Author : 髙野馨將 KAJITA HIROMU
//
//======================================================
#ifndef  _MOTION_H_					//このマクロ定義がされてなかったら
#define  _MOTION_H_					//二重インクルード防止のマクロ定義

#include "main.h"
#include "player.h"

//マクロ定義
#define	MAX_WORDCOUNT	(1024)		//文字の最大数

//モーションクラス
class CMotion
{
public:

	//アニメーションの種類
	enum AnimType
	{
		ANIM_TYPE_PLAYER = 0,					//プレイヤーアニメーション
		ANIM_TYPE_MAX
	};

	struct KEY
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	};

	struct KEY_SET
	{
		int nFrame;
		KEY aKey[CPlayer::MAX_MODEL];
	};

	struct MotionSet
	{
		int nLoopAnim;
		KEY_SET aKeySet[2];
	};

	CMotion();									//コンストラクタ
	~CMotion();									//デストラクタ

	HRESULT Init();								//初期化処理
	void Uninit();								//終了処理
	void Update();								//更新処理

	static CMotion *Create(AnimType type);		//モーションの生成

	static void LoadFile();
	void SetPresentAnim(int nPresentAnim);		//アニメーションの設定処理

private:
	static char* m_pAnimPass[ANIM_TYPE_MAX];	//アニメーションの外部ファイルの相対パス
	static MotionSet m_AnimSet[3];
	AnimType m_type;							//アニメーションの種類

	int m_nNumkey;				//キーの総数
	int m_nCurrentKey;			//現在のキー番号
	int m_nCountMotion;			//モーションカウンター
	int m_nPresentFrame;		//現在のフレーム
	int m_nPresentMotionSet;	//再生されるモーションセットの番号

	bool m_bLoop;				//ループするかしないか
};
#endif