//======================================================
//
//motion.cpp
//Author : 髙野馨將 KAJITA HIROMU
//
//======================================================
#include "motion.h"
#include "model.h"
#include "game.h"
#include <stdio.h>

//アニメーション情報のテキストファイルの相対パス
char* CMotion::m_pAnimPass[ANIM_TYPE_MAX] =
{
	{ "data\\TEXT\\motion.txt" },
};

//静的メンバ変数宣言
CMotion::MotionSet CMotion::m_AnimSet[] = {};

//======================================================
//コンストラクタ
//======================================================
CMotion::CMotion()
{
}

//======================================================
//デストラクタ
//======================================================
CMotion::~CMotion()
{
}

//======================================================
//初期化処理
//======================================================
HRESULT CMotion::Init()
{
	m_nPresentMotionSet = 0;	//再生されるモーションセットの番号
	m_nPresentFrame = 0;		//現在のフレーム	

	m_nNumkey = 2;				//キーの総数
	m_nCurrentKey = 0;			//現在のキー番号
	m_nCountMotion = 0;			//モーションカウンター
	m_bLoop = true;

	return S_OK;
}

//======================================================
//終了処理
//======================================================
void CMotion::Uninit()
{
}

//======================================================
//更新処理
//======================================================
void CMotion::Update()
{
	for (int nCntModel = 0; nCntModel < CPlayer::MAX_MODEL; nCntModel++)
	{
		//プレイヤーの情報を取得
		CPlayer *pPlayer = CGame::GetPlayer();
		if (pPlayer != nullptr)
		{
			CModel *pModel[CPlayer::MAX_MODEL] = {};
			pModel[nCntModel] = pPlayer->GetModel(nCntModel);

			if (m_bLoop)
			{
				if (pModel[nCntModel] != nullptr)
				{
					D3DXVECTOR3 NowPointPos;
					D3DXVECTOR3 NowPointRot;

					// 目的のキー
					int nDestKey = m_nCurrentKey + 1;

					if (nDestKey >= m_nNumkey)
					{
						nDestKey = 0;
					}

					//差分
					D3DXVECTOR3 SubPos = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosX - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosX,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosY - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosY,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fPosZ - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosZ);

					//相対値の計算
					float ratio = (float)m_nCountMotion / (float)m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].nFrame;

					//現在地の設定
					NowPointPos = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosX + (SubPos.x * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosY + (SubPos.y * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fPosZ + (SubPos.z * ratio));

					//向き
					D3DXVECTOR3 SubRot = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotX - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotX,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotY - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotY,
						m_AnimSet[m_nPresentMotionSet].aKeySet[nDestKey].aKey[nCntModel].fRotZ - m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotZ);

					//現在の向きの設定
					NowPointRot = D3DXVECTOR3(m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotX + (SubRot.x * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotY + (SubRot.y * ratio),
						m_AnimSet[m_nPresentMotionSet].aKeySet[m_nCurrentKey].aKey[nCntModel].fRotZ + (SubRot.z * ratio));

					//現在の位置
					pModel[nCntModel]->SetPos(D3DXVECTOR3(NowPointPos.x, NowPointPos.y + 10.0f, NowPointPos.z + 5.0f));
					pModel[nCntModel]->SetRot(NowPointRot);
				}
			}
		}
	}

	//カウンターを進める
	m_nCountMotion++;

	//現在の再生フレームに達したら
	if (m_nCountMotion >= 60)
	{
		m_nCurrentKey++;		//現在のキー番号を進める
		m_nCountMotion = 0;		//モーションカウンターの初期化
	}

	//現在のキー番号がキーの総数に達したら
	if (m_nCurrentKey >= m_nNumkey)
	{
		m_nPresentMotionSet++;
		m_nCurrentKey = 0;
	}

	//次のモーション
	m_nPresentFrame++;		//現在フレームを更新する

	int nextAnim = m_AnimSet[m_nPresentMotionSet].nLoopAnim;

	if (m_nPresentFrame > m_AnimSet[m_nPresentMotionSet].aKeySet[m_nNumkey - 1].nFrame)
	{//アニメーションのモーションセット最大フレームを越えた場合
		if (nextAnim == 0)
		{
			m_nPresentMotionSet = m_nPresentMotionSet;
		}
		else if (nextAnim == 1)
		{
			m_bLoop = false;
		}

		m_nPresentFrame = 0;				//フレームを0に戻す
	}
}

//======================================================
//生成処理
//======================================================
CMotion * CMotion::Create(AnimType type)
{
	//アニメーターを生成する
	CMotion* pMotion = new CMotion;

	if (FAILED(pMotion->Init()))
	{//初期化処理
		return nullptr;
	}

	pMotion->m_type = type;					//種類の設定

	//生成したアニメーターを返す
	return pMotion;
}

//======================================================
//ファイル読み込み
//======================================================
void CMotion::LoadFile()
{
	int nCntMotion = -1;		//現在のアニメーションカウンターを初期化する
	int nCntKeySet = -1;		//現在のキーセットを初期化する
	int nCntKey = -1;			//現在のキーを初期化する
	char aText[2000] = {};		//文字列を格納する配列

	//ファイルポインタを宣言
	FILE *pFile;

	//ファイル読み込み
	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		while (strncmp(&aText[0], "SCRIPT", strlen("SCRIPT")) != 0)
		{//テキストの最初の行を読み込むまで繰り返す
			fgets(aText, MAX_WORDCOUNT, pFile);		//一行ごと読み込む
		}

		while (strncmp(&aText[0], "END_SCRIPT", strlen("END_SCRIPT")) != 0)
		{//テキストの最後の行を読み込むまで繰り返す
			fscanf(pFile, "%s", &aText[0]);	//ファイルから文字列を読み込む(	読み込み開始)

			if (strncmp(&aText[0], "#", strlen("#")) == 0)
			{
				fgets(aText, MAX_WORDCOUNT, pFile);		//一行ごと読み込む
				continue;
			}

			if (strcmp(&aText[0], "MOTIONSET") == 0)
			{
				nCntMotion++;			//モーションセットのカウンターをインクリメントする
				nCntKeySet = -1;		//キーセットを元に戻す

				while ((strcmp(&aText[0], "END_MOTIONSET") != 0))
				{
					fscanf(pFile, "%s", &aText[0]);

					if (strncmp(&aText[0], "#", strlen("#")) == 0)
					{
						fgets(aText, MAX_WORDCOUNT, pFile);		//一行ごと読み込む
						continue;
					}

					else if (strcmp(&aText[0], "LOOP") == 0)
					{
						int LOOP = 0;
						fscanf(pFile, "%s %d", &aText[0], &LOOP);

						m_AnimSet[nCntMotion].nLoopAnim = LOOP;	//次のアニメーションを設定する
					}

					else if (strcmp(&aText[0], "KEYSET") == 0)
					{
						nCntKeySet++;								//キーセットをインクリメントする
						nCntKey = -1;								//キーカウンターを元に戻す

						while ((strcmp(&aText[0], "END_KEYSET") != 0))
						{
							fscanf(pFile, "%s", &aText[0]);

							if (strncmp(&aText[0], "#", strlen("#")) == 0)
							{
								fgets(aText, MAX_WORDCOUNT, pFile);		//一行ごと読み込む
								continue;
							}

							else if (strcmp(&aText[0], "FRAME") == 0)
							{
								int nFrames = 0;
								fscanf(pFile, "%s %d", &aText[0], &nFrames);

								m_AnimSet[nCntMotion].aKeySet[nCntKeySet].nFrame = nFrames;		//フレーム数の設定処理
							}

							else if (strcmp(&aText[0], "KEY") == 0)
							{
								//キーカウンターをインクリメントする
								nCntKey++;

								while ((strcmp(&aText[0], "END_KEY") != 0))
								{
									fscanf(pFile, "%s", &aText[0]);

									if (strcmp(&aText[0], "POS") == 0)
									{
										fscanf(pFile, "%s %f %f %f", &aText[0], &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosX, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosY, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fPosZ);
									}

									else if (strcmp(&aText[0], "ROT") == 0)
									{
										fscanf(pFile, "%s %f %f %f", &aText[0], &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotX, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotY, &m_AnimSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].fRotZ);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

//======================================================
//アニメーションの設定
//======================================================
void CMotion::SetPresentAnim(int nPresentAnim)
{
	if (m_nPresentMotionSet != nPresentAnim)
	{
		m_nPresentMotionSet = nPresentAnim;
		m_nPresentFrame = 0;
	}
}