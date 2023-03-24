//=============================================================================
//
// オブジェクト
// Author:髙野馨將
//
//=============================================================================
#include "object.h"

//静的メンバ変数宣言
CObject *CObject::m_pTop[PRIORITY_MAX] = {};		//先頭のオブジェクトへのポインタ
CObject *CObject::m_pCurrent[PRIORITY_MAX] = {};	//現在のオブジェクトへのポインタ
//======================================================
//コンストラクタ
//======================================================
CObject::CObject(int nPriority /*=3*/)
{
	m_bDeath = false;

	//NextとPrevの初期化
	m_pNext, m_pPrev = nullptr;

	//オブジェクトをリストに追加
	if (m_pTop[nPriority] == nullptr)
	{//先頭がnullだったら
	 //Topに情報を入れる
		m_pTop[nPriority] = this;
	}
	else
	{//nullじゃなかったら
		m_pCurrent[nPriority]->m_pNext = this;	//現在のオブジェクトのNextに情報を入れる
		this->m_pPrev = m_pCurrent[nPriority];	//Prevに現在のオブジェクトの情報を入れる
	}

	m_pCurrent[nPriority] = this;	//現在のオブジェクトに情報を入れる
	m_nPriority = nPriority;		//Priorityを保存
}

//======================================================
//デストラクタ
//======================================================
CObject::~CObject()
{
}

//======================================================
//全てのポリゴンの破棄処理
//======================================================
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (!pCurrentObj->m_bDeath)
			{
				pCurrentObj->Uninit();	//TopがnullptrになるまでReleaseを呼ぶ
			}

			pCurrentObj = pObjNext;
		}
	}

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *pCurrentObj = m_pTop[nCnt];

		while (pCurrentObj != nullptr)
		{
			CObject *pObjNext = pCurrentObj->m_pNext;

			if (pCurrentObj->m_bDeath)
			{
				pCurrentObj->Break();
			}

			pCurrentObj = pObjNext;
		}

		m_pTop[nCnt] = nullptr;
		m_pCurrent[nCnt] = nullptr;
	}
}

//======================================================
//更新処理
//======================================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		//Topの情報をポインタ変数に入れる
		CObject *NowPoint = m_pTop[nCnt];

		while (NowPoint)
		{
			//Update()で削除されるとpNextも消えるので、事前に保存しておく
			CObject *pObjectNext = NowPoint->m_pNext;

			if (!NowPoint->m_bDeath)
			{
				//更新処理
				NowPoint->Update();
			}

			//TopにNextの情報を入れる
			NowPoint = pObjectNext;
		}

		while (NowPoint)
		{
			if (NowPoint->m_bDeath)
			{
				NowPoint->Break();
			}
		}
	}
}

//======================================================
//描画処理
//======================================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		//Topの情報をポインタ変数に入れる
		CObject *NowPoint = m_pTop[nCnt];

		while (NowPoint)
		{
			//Update()で削除されるとpNextも消えるので、事前に保存しておく
			CObject *pObjectNext = NowPoint->m_pNext;

			if (!NowPoint->m_bDeath)
			{
				NowPoint->Draw();
			}

			//TopにNextの情報を入れる
			NowPoint = pObjectNext;
		}
	}
}

//======================================================
//破棄処理
//======================================================
void CObject::Break()
{
	//オブジェクトをリストから削除
	if (m_pNext != nullptr)
	{
		if (m_pPrev != nullptr)
		{
			m_pNext->m_pPrev = this->m_pPrev;
			m_pPrev->m_pNext = this->m_pNext;
		}
		else
		{
			m_pNext->m_pPrev = this->m_pPrev;
			m_pTop[m_nPriority] = this->m_pNext;
		}
	}
	else
	{
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = this->m_pNext;
			m_pCurrent[m_nPriority] = this->m_pPrev;
		}
		else
		{
			m_pTop[m_nPriority] = nullptr;
			m_pCurrent[m_nPriority] = nullptr;
		}
	}

	//this->Uninit();
	//オブジェクトを破棄
	delete this;
}

//======================================================
//モードの解放処理
//======================================================
void CObject::ReleaseMode()
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNextの保存
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != OBJTYPE_MODE)
				{
					//終了処理の関数呼び出し
					pObject->Break();
				}

				//pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}

		{
			CObject* pObject = m_pTop[nPriority];

			while (pObject != nullptr)
			{
				//pNextの保存
				CObject* pObjectNext = pObject->m_pNext;

				if (pObject->GetType() != OBJTYPE_MODE)
				{
					pObject->Flag();
				}

				//pObjectにpObjectのpNextを代入
				pObject = pObjectNext;
			}
		}
	}
}