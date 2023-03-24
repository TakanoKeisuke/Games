//=============================================================================
//
// ゲーム処理
// Author:髙野馨將
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

#include "object.h"

//前方宣言
class CTitle;
class CGame;
class CResult;
class CRanking;
class CTutorial;

//モードクラス
class CMode : public CObject
{
public:
	CMode();			//コンストラクタ
	~CMode() override;	//デストラクタ
	//仮想関数
	virtual HRESULT Init() override { return S_OK; }	//初期化
	virtual void Uninit() override {}					//終了
	virtual void Update() override {}					//更新
	virtual void Draw() override {}						//描画
	void SetPos(const D3DXVECTOR3 pos) { pos; }		//位置の設定
	const D3DXVECTOR3 GetPos(void) { return{}; }				//posの取得
	const D3DXVECTOR3 GetSize(void) { return{}; }				//sizeの取得
	
private:
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CRanking *m_pRanking;
};

#endif