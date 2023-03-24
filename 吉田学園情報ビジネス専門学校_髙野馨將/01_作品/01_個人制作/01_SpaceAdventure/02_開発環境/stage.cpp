//=============================================================================
//
// ステージ処理
// Author:髙野馨將
//
//=============================================================================
#include <string>
#include "application.h"
//#include "bg.h"
//#include "enemy.h"
#include "stage.h"
#include "input.h"
//#include "number.h"
#include "player.h"
#include "renderer.h"
//#include "score.h"
#include "fade.h"
#include "sphere.h"
#include "mesh_sphere.h"
#include "planet.h"
#include "goal.h"
#include "spike.h"
#include "heal.h"
#include "ring.h"
#include "life_gauge.h"
#include "buff.h"
#include "hitbox.h"
#include "gimmick.h"
#include "secret_item.h"
#include "ItemFrame.h"
#include "checkpoint.h"

//静的メンバ変数宣言
std::vector<CMeshField*> CStage::m_pMesh = {};
std::vector<CRing*> CStage::m_pRing = {};
std::vector<CPlanet*> CStage::m_pPlanet = {};
std::vector<CSecret_item*> CStage::m_pSecret = {};
std::vector<CSpike*> CStage::m_pSpike = {};
std::vector<CHeal*> CStage::m_pHeal = {};
std::vector<CBuff*> CStage::m_pBuff = {};
std::vector<CGimmick*> CStage::m_pGimmick = {};
std::vector<CCheckpoint*> CStage::m_pCheck = {};
std::vector<CGoal*> CStage::m_pGoal = {};
CPlayer *CStage::m_pPlayer = nullptr;
CSphere *CStage::m_pSphere = nullptr;
CMesh_sphere *CStage::m_pMesh_sphere = nullptr;
CLife_gauge *CStage::m_pLife = nullptr;
int CStage::m_nMaxMesh = 0;
int CStage::m_nMaxRing = 0;
int CStage::m_nMaxHeal = 0;
int CStage::m_nMaxPlanet = 0;
int CStage::m_nMaxSecret = 0;
int CStage::m_nMaxSpike = 0;
int CStage::m_nMaxGimmick = 0;
int CStage::m_nMaxBuff = 0;
int CStage::m_nMaxCheck = 0;
int CStage::m_nMaxGoal = 0;
//=====================================
// デフォルトコンストラクタ
//=====================================
CStage::CStage()
{
}

//=====================================
// デストラクタ
//=====================================
CStage::~CStage()
{
}

//=====================================
// 初期化処理
//=====================================
HRESULT CStage::Init(void)
{
	//最大数の初期化
	m_nMaxMesh = 0;
	m_nMaxRing = 0;
	m_nMaxHeal = 0;
	m_nMaxPlanet = 0;
	m_nMaxSecret = 0;
	m_nMaxSpike = 0;
	m_nMaxGimmick = 0;
	m_nMaxBuff = 0;
	m_nMaxCheck = 0;

	//ステージ読み込み処理
	Load();

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CStage::Uninit(void)
{
	for (int nCnt = 0;nCnt < m_nMaxMesh;nCnt++)
	{
		//メッシュフィールドの破棄処理
		if (m_pMesh[nCnt] != nullptr)
		{
			m_pMesh[nCnt]->Uninit();
			m_pMesh[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxRing; nCnt++)
	{
		//移動用の破棄処理
		if (m_pRing[nCnt] != nullptr)
		{
			m_pRing[nCnt]->Uninit();
			m_pRing[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxHeal; nCnt++)
	{
		//回復の破棄処理
		if (m_pHeal[nCnt] != nullptr)
		{
			m_pHeal[nCnt]->Uninit();
			m_pHeal[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxSpike; nCnt++)
	{
		//棘の破棄処理
		if (m_pSpike[nCnt] != nullptr)
		{
			m_pSpike[nCnt]->Uninit();
			m_pSpike[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxPlanet; nCnt++)
	{
		//惑星の破棄処理
		if (m_pPlanet[nCnt] != nullptr)
		{
			m_pPlanet[nCnt]->Uninit();
			m_pPlanet[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxGimmick; nCnt++)
	{
		//ギミックの破棄処理
		if (m_pGimmick[nCnt] != nullptr)
		{
			m_pGimmick[nCnt]->Uninit();
			m_pGimmick[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxBuff; nCnt++)
	{
		//強化アイテムの破棄処理
		if (m_pBuff[nCnt] != nullptr)
		{
			m_pBuff[nCnt]->Uninit();
			m_pBuff[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxSecret; nCnt++)
	{
		//隠しアイテムの破棄処理
		if (m_pSecret[nCnt] != nullptr)
		{
			m_pSecret[nCnt]->Uninit();
			m_pSecret[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nMaxCheck; nCnt++)
	{
		//チェックポイントの破棄処理
		if (m_pCheck[nCnt] != nullptr)
		{
			m_pCheck[nCnt]->Uninit();
			m_pCheck[nCnt] = nullptr;
		}
	}
	for (int nCnt = 0; nCnt < m_nMaxGoal; nCnt++)
	{
		//ゴールの破棄処理
		if (m_pGoal[nCnt] != nullptr)
		{
			m_pGoal[nCnt]->Uninit();
			m_pGoal[nCnt] = nullptr;
		}
	}
}

//=====================================
// 更新処理
//=====================================
void CStage::Update(void)
{
}

//=====================================
//モデル設定処理
//=====================================
void CStage::SetModelType(int count, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXVECTOR2 block, CMeshField::MESH_TYPE meshtype, MODEL_TYPE type, GIMMICK_TYPE gimmick)
{
	switch (type)
	{
	case CStage::MODEL_SPIKE:
	{	//棘
		if (gimmick == GIMMICK_MOVE_X)
		{//X方向に移動する
			m_pSpike[m_nMaxSpike - 1] = CSpike::Create(pos, CGimmick::TYPE_MOVE_X, count);
		}
		else if (gimmick == GIMMICK_MOVE_Y)
		{//Y方向に移動する
			m_pSpike[m_nMaxSpike - 1] = CSpike::Create(pos, CGimmick::TYPE_MOVE_Y, count);
		}
		else if (gimmick == GIMMICK_MOVE_Z)
		{//Z方向に移動する
			m_pSpike[m_nMaxSpike - 1] = CSpike::Create(pos, CGimmick::TYPE_MOVE_Z, count);
		}
		else
		{//移動しない
			m_pSpike[m_nMaxSpike - 1] = CSpike::Create(pos, CGimmick::TYPE_NONE, count);
		}
	}
	break;

	case CStage::MODEL_RING:
	{
		//移動
		m_pRing[m_nMaxRing - 1] = CRing::Create(pos, size,rot);
	}
	break;

	case CStage::MODEL_HEAL:
	{
		//回復アイテム
		m_pHeal[m_nMaxHeal - 1] = CHeal::Create(pos);
	}
	break;

	case CStage::MODEL_SECRET:
	{
		//隠しアイテム
		m_pSecret[m_nMaxSecret - 1] = CSecret_item::Create(pos, count);
	}
	break;

	case CStage::MODEL_PLANET:
	{
		//ステージ
		m_pPlanet[m_nMaxPlanet - 1] = CPlanet::Create(pos, size, rot);
		m_pPlanet[m_nMaxPlanet - 1]->LoadTexture("data\\TEXTURE\\block001.jpg");
	}
	break;

	case CStage::MODEL_MESH:
	{
		//メッシュフィールド
		m_pMesh[m_nMaxMesh -1] = CMeshField::Create(pos, size, rot, block, meshtype, 3);
	}
	break;

	case CStage::MODEL_GOAL:
	{
		//ゴール
		m_pGoal[m_nMaxGoal - 1] = CGoal::Create(pos, size);
	}
	break;

	case CStage::MODEL_CHECK:
	{
		//チェックポイント
		m_pCheck[m_nMaxCheck -1] = CCheckpoint::Create(pos);
	}
	break;

	default:
		break;
	}
}

//=====================================
//アイテム設定処理
//=====================================
void CStage::SetItemType(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	switch (type)
	{
	case CStage::ITEM_SPEED:
	{
		//スピード強化アイテム
		m_pBuff[m_nMaxBuff - 1] = CBuff::Create(pos, CHitbox::EFFECT_SPEED);
	}
	break;

	case CStage::ITEM_JUMP:
	{
		//ジャンプ力強化アイテム
		m_pBuff[m_nMaxBuff - 1] = CBuff::Create(pos, CHitbox::EFFECT_JUMP);
	}
	break;

	default:
		break;
	}
}

//=====================================
//ギミック設定処理
//=====================================
void CStage::SetGimmickType(const D3DXVECTOR3 pos, const float range, const float speed, GIMMICK_TYPE type)
{
	switch (type)
	{
	case CStage::GIMMICK_MOVE_X:
	{
		//X方向に動くギミック
		m_pGimmick[m_nMaxGimmick - 1] = CGimmick::Create(pos, range, CGimmick::TYPE_MOVE_X, speed);
	}
	break;

	case CStage::GIMMICK_MOVE_Y:
	{
		//Y方向に動くギミック
		m_pGimmick[m_nMaxGimmick - 1] = CGimmick::Create(pos, range, CGimmick::TYPE_MOVE_Y, speed);
	}
	break;

	case  CStage::GIMMICK_MOVE_Z:
	{
		//Z方向に動くギミック
		m_pGimmick[m_nMaxGimmick - 1] = CGimmick::Create(pos, range, CGimmick::TYPE_MOVE_Z, speed);
	}
	break;

	case  CStage::GIMMICK_FALL:
	{
		//一定時間で落ちるギミック
		m_pGimmick[m_nMaxGimmick - 1] = CGimmick::Create(pos, range, CGimmick::TYPE_FALL, speed);
	}
	break;

	case  CStage::GIMMICK_FALL_LONG:
	{
		//一定時間で落ちるギミック
		m_pGimmick[m_nMaxGimmick - 1] = CGimmick::Create(pos, range, CGimmick::TYPE_FALL_LONG, speed);
	}
	break;

	default:
		break;
	}
}

//=====================================
// 生成処理
//=====================================
CStage* CStage::Create(void)
{
	CStage* pStage = new CStage;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}

//=====================================
//読み込み処理
//=====================================
void CStage::Load()
{
	char aText[2000];					//文字列を格納する配列

	FILE *pFile; //ファイルポインタを宣言

	pFile = fopen("data\\TEXT\\stage.txt", "r");

	aText[0] = '\0';	//文字列なし

	if (pFile != nullptr)
	{//ファイルが開けた場合
	 //ファイルに入力したデータを書き出す処理
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);    //ファイルから文字列を読み込む(読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
				continue;
			}

			if (strcmp(&aText[0], "MODELSET") == 0)
			{
				D3DXVECTOR3 pos, rot, size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR2 block = D3DXVECTOR2(0.0f, 0.0f);
				int Ind, count,type,gimmick = 0;

				while (strcmp(&aText[0], "END_MODELSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "TYPE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);			// = を読み込む
						fscanf(pFile, "%d", &Ind);
						switch (Ind)
						{
						case CStage::MODEL_SPIKE:
							m_nMaxSpike++;
							m_pSpike.resize(m_nMaxSpike);
							break;

						case CStage::MODEL_RING:
							m_nMaxRing++;
							m_pRing.resize(m_nMaxRing);
							break;

						case CStage::MODEL_HEAL:
							m_nMaxHeal++;
							m_pHeal.resize(m_nMaxHeal);
							break;

						case CStage::MODEL_SECRET:
							m_nMaxSecret++;
							m_pSecret.resize(m_nMaxSecret);
							break;

						case CStage::MODEL_PLANET:
							m_nMaxPlanet++;
							m_pPlanet.resize(m_nMaxPlanet);
							break;

						case CStage::MODEL_MESH:
							m_nMaxMesh++;
							m_pMesh.resize(m_nMaxMesh);
							break;

						case CStage::MODEL_CHECK:
							m_nMaxCheck++;
							m_pCheck.resize(m_nMaxCheck);
							break;

						case CStage::MODEL_GOAL:
							m_nMaxGoal++;
							m_pGoal.resize(m_nMaxGoal);
							break;

						default:
							break;
						}

					}
					else if (strcmp(&aText[0], "COUNT") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);			// = を読み込む
						fscanf(pFile, "%d", &count);
					}
					else if (strcmp(&aText[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(&aText[0], "SIZE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &size.x);
						fscanf(pFile, "%f", &size.y);
						fscanf(pFile, "%f", &size.z);
					}
					else if (strcmp(&aText[0], "ROT") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &rot.x);
						fscanf(pFile, "%f", &rot.y);
						fscanf(pFile, "%f", &rot.z);
					}
					else if (strcmp(&aText[0], "BLOCK") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &block.x);
						fscanf(pFile, "%f", &block.y);
					}
					else if (strcmp(&aText[0], "MESH_TYPE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%d", &type);
					}
					else if (strcmp(&aText[0], "SPIKE_TYPE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%d", &gimmick);
					}
				}
				//モデルパーツの生成
				SetModelType(count, pos, size, rot, block,(CMeshField::MESH_TYPE)type, (MODEL_TYPE)Ind,(GIMMICK_TYPE)gimmick);
			}
			else if (strcmp(&aText[0], "GIMMICKSET") == 0)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				int Ind = 0;
				float range,speed = 0.0f;

				while (strcmp(&aText[0], "END_GIMMICKSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "TYPE") == 0)
					{//ギミックの種類を番号で決める
						fscanf(pFile, "%s", &aText[0]);			// = を読み込む
						fscanf(pFile, "%d", &Ind);
						m_nMaxGimmick++;
						m_pGimmick.resize(m_nMaxGimmick);
					}
					else if (strcmp(&aText[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(&aText[0], "RANGE") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &range);
					}
					else if (strcmp(&aText[0], "SPEED") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &speed);
					}
				}
				//モデルパーツの生成
				SetGimmickType(pos, range, speed, (GIMMICK_TYPE)Ind);
			}
			else if (strcmp(&aText[0], "ITEMSET") == 0)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				int Ind = 0;

				while (strcmp(&aText[0], "END_ITEMSET") != 0)
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORD, pFile);        //一行ごと読み込む
						continue;
					}

					if (strcmp(&aText[0], "TYPE") == 0)
					{//ギミックの種類を番号で決める
						fscanf(pFile, "%s", &aText[0]);			// = を読み込む
						fscanf(pFile, "%d", &Ind);
						m_nMaxBuff++;
						m_pBuff.resize(m_nMaxBuff);
					}
					else if (strcmp(&aText[0], "POS") == 0)
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
				}
				//モデルパーツの生成
				SetItemType(pos, (ITEM_TYPE)Ind);
			}
		}
	}
}