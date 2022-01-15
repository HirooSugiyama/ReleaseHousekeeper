/*
地面上にあるオブジェクトを統括するクラス
作成日：2021/08/19
*/


#include"pch.h"
#include "GroundObjectManager.h"

//前方宣言
#include"../Enemy/EnemyManager.h"

//関数内部を使用
#include"IGroundObject.h"
#include"../Player/Player.h"
#include"../ObjectModel/BoxModel.h"

#include"../Player/PStateWalk.h"

//CSVファイル原点の座標
const DirectX::SimpleMath::Vector2 GroundObjectManager::GOMANAGER_INIT_CSV_POSITION(-19.f, -40.f);
/*======================
コンストラクタ
======================*/
GroundObjectManager::GroundObjectManager(std::string const& filepath)
	:
	mpConifer{},
	mConiferPosition(),
	mpConiferGroup{},
	mConiferGroupPosition(),
	mpMoveCar{},
	mMoveCarPosition(),
	mpShop{},
	mShopPosition(),
	mGroundObject(),
	mGroundObjectMapChip{},
	mSaveInfo{},
	mGroundObjectCollider{},
	mCorresColliderObject{},
	mPlayerShopTouchFlag(false)
{
	//ファイル読み込み処理
	this->LoadMapChip(filepath);

	//針葉樹の配列数を調節する
	this->AdjustmentConiferVector();
	//動く車の配列数を調節する
	this->AdjustmentMoveCarVector();
	//針葉樹の配列数を調節する
	this->AdjustmentConiferGroupVector();
	//ショップの配列数を調節する
	this->AdjustmentShopVector();

	//CSVファイルからある程度のまとまりのオブジェクトを探し出す
	this->SeekLoadMapChipCohesive();

	//情報をもとに当たり判定を作成する
	this->CreateCollider();
}

/*======================
デストラクタ
======================*/
GroundObjectManager::~GroundObjectManager()
{
}

/*======================
初期化
======================*/
void GroundObjectManager::Initialize()
{
	//針葉樹の初期化処理
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Initialize();

		//座標を設定する
		this->ConfigConiferVectorPosition();
	}	
	//動く車の初期化処理
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Initialize();

		//座標を設定する
		this->ConfigMoveCarVectorPosition();
	}
	//針葉樹グループの初期化処理
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Initialize();

		//座標を設定する
		this->ConfigConiferGroupVectorPosition();
	}	
	//ショップの初期化処理
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Initialize();

		//座標を設定する
		this->ConfigShopVectorPosition();
	}	
}

/*======================
更新処理
======================*/
void GroundObjectManager::Update()
{
	//動く車の更新処理
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Update();
	}
}

/*====================
描画処理
======================*/
void GroundObjectManager::Draw()
{
	//針葉樹の描画処理
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i]->Draw();
	}
	//動く車の描画処理
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i]->Draw();
	}
	//針葉樹グループの描画処理
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i]->Draw();
	}
	//ショップの描画処理
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i]->Draw();
	}
}

/*======================================
敵の当たり判定を回す
引数：ファイルのパス
======================================*/
void GroundObjectManager::RoolEnemyManagerChackHit(EnemyManager* pEnemyManager)
{
	//当たり判定の数だけ繰り返す
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{
		pEnemyManager->ChackHitGroundObjectEnemy(&mGroundObjectCollider[i]);
	}
}

/*=====================================
プレイヤーとの当たり判定処理
引数：プレイヤーのポインタ
======================================*/
void GroundObjectManager::ChackHitPlayerGroundObject(Player* pPlayer)
{
	//判定用変数の宣言
	bool hitflag = false;

	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//当たり判定の数だけ行う
	for (int i = 0; i < static_cast<int>(mGroundObjectCollider.size()); i++)
	{	
		//もし当たっていたら処理を行う
		if (pC.Intersect(pPlayer->GetStateWalk()->GetDestinationPlayerCollider(),
			&mGroundObjectCollider[i]))
		{

			hitflag = true;

			//もしショップにぶつかったら
			if (mCorresColliderObject[i] == eGroundObject::SHOP)
			{
				//フラグを建てる
				mPlayerShopTouchFlag = true;
				//ワイプ処理
				ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
				pSTI.SetWipeUseFlag(true);
				pSTI.GetWipe()->SetClose();
			}
			else
			{
				//地上オブジェクトとは当たっていることにする
				pPlayer->GetStateWalk()->SetGroundObjectHitFlag(true);
			}
		}
	}
	//もし現在の入力で移動しても衝突しないならば
	if(hitflag==false)
	{
		//地上オブジェクトとは当たっていないことにする
		pPlayer->GetStateWalk()->SetGroundObjectHitFlag(false);

		//ショップとも当たってないこととする
		mPlayerShopTouchFlag = false;
	}
}

/*======================================
オブジェクト配置用のMapChip読み込み
引数：ファイルのパス
======================================*/
void GroundObjectManager::LoadMapChip(std::string const& filepath)
{
	//ファイル変換
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;
		//変換用変数
		DirectX::SimpleMath::Vector2 pos;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//要素がなかったら
			if (atoi(tileBuf.c_str()) == static_cast<int>(eGroundObject::NONE))
			{
				continue;
			}

			//以下は要素がある場合のみ通る処理
			int tile = atoi(tileBuf.c_str());
			

			//要素を保存
			mGroundObjectMapChip[j][i] = tile;

			//座標を保存
			pos.x = static_cast<float>(j);
			pos.y = static_cast<float>(i);

			//座標をワールド座標に変換
			pos += GOMANAGER_INIT_CSV_POSITION;

			//要素によって処理を変える
			switch (tile)
			{
				case static_cast<int>(eGroundObject::CONIFER):
				{
					mConiferPosition.push_back(pos);

					//確保数を増やす
					mGroundObject.mConiferNum++;

					break;
				}
				case static_cast<int>(eGroundObject::MOVE_CAR):
				{
					mMoveCarPosition.push_back(pos);

					//確保数を増やす
					mGroundObject.mMoveCarNum++;

					break;
				}
				case static_cast<int>(eGroundObject::CONIFER_GROUP):
				{
					mConiferGroupPosition.push_back(pos);

					//確保数を増やす
					mGroundObject.mConiferGroupNum++;

					break;
				}
				case static_cast<int>(eGroundObject::SHOP):
				{
					mShopPosition.push_back(pos);

					//確保数を増やす
					mGroundObject.mShopNum++;

					break;
				}
			}
		}

	}
}

/*======================================
針葉樹の配列数を調節する
======================================*/
void GroundObjectManager::AdjustmentConiferVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpConifer.resize(mGroundObject.mConiferNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		mpConifer[i] = std::make_unique<GroundObjectConifer>();
	}
}

/*======================================
針葉樹の座標を設定する
======================================*/
void GroundObjectManager::ConfigConiferVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 pos= DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConifer.size()); i++)
	{
		pos.x = mConiferPosition[i].x;
		pos.y = mpConifer[i]->GetConiferModelPositionY();
		pos.z = mConiferPosition[i].y;
		mpConifer[i]->
			SetConiferModelPosition(pos);
	}
}

/*======================================
針葉樹グループの配列数を調節する
======================================*/
void GroundObjectManager::AdjustmentConiferGroupVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpConiferGroup.resize(mGroundObject.mConiferGroupNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		mpConiferGroup[i] = std::make_unique<GroundObjectConiferGroup>();
	}
}

/*======================================
針葉樹のグループ座標を設定する
======================================*/
void GroundObjectManager::ConfigConiferGroupVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpConiferGroup.size()); i++)
	{
		pos.x = mConiferGroupPosition[i].x;
		pos.y = mpConiferGroup[i]->GetConiferModelPositionY();
		pos.z = mConiferGroupPosition[i].y;
		mpConiferGroup[i]->
			SetConiferModelPosition(pos);
	}
}

/*======================================
動く車の配列数を調節する
======================================*/
void GroundObjectManager::AdjustmentMoveCarVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpMoveCar.resize(mGroundObject.mMoveCarNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		mpMoveCar[i] = std::make_unique<GroundObjectMoveCar>();
	}
}

/*====================================
動く車の座標を設定する
======================================*/
void GroundObjectManager::ConfigMoveCarVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpMoveCar.size()); i++)
	{
		pos.x = mMoveCarPosition[i].x;
		pos.y = mpMoveCar[i]->GetMoveCarModelPositionY();
		pos.z = mMoveCarPosition[i].y;
		mpMoveCar[i]->
			SetMoveCarModelPosition(pos);
	}
}

/*======================================
ショップの配列数を調節する
======================================*/
void GroundObjectManager::AdjustmentShopVector()
{
	//構造体情報をもとに必要な分だけオブジェクトを準備する
	mpShop.resize(mGroundObject.mShopNum);

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		mpShop[i] = std::make_unique<GroundObjectShop>();
	}
}

/*====================================
ショップの座標を設定する
======================================*/
void GroundObjectManager::ConfigShopVectorPosition()
{
	//変換用変数
	DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero;

	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpShop.size()); i++)
	{
		pos.x = mShopPosition[i].x;
		pos.y = mpShop[i]->GetShopModelPositionY();
		pos.z = mShopPosition[i].y;
		mpShop[i]->SetShopModelPosition(pos);
	}
}

/*================================================================
CSVファイルからある程度のまとまりのオブジェクトを探し出す:private
引数：ファイルのパス
==================================================================*/
void GroundObjectManager::SeekLoadMapChipCohesive()
{
	mSaveInfo.clear();

	//一時保存用構造体を実体化
	SaveColliderInfo colliderInfo
		(eGroundObject::NONE, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2::Zero);

	//Y軸の処理
	for (int y = 0; y < GOMANAGER_CSV_MAX_Y; y++)
	{
		//変換用変数
		int chipX = 0, chipY = 0;

		//X軸の処理
		for (int x = 0; x < GOMANAGER_CSV_MAX_X; x++)
		{
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::NONE))continue;
			if (mGroundObjectMapChip[x][y] == static_cast<int>(eGroundObject::CONIFER_GROUP))continue;
			if (this->OverlapCheck(x, y))continue;	//重複チェック

			//オブジェクトがあったら再帰開始
			chipX = x;
			chipY = y;
			this->Search(chipX, chipY, mGroundObjectMapChip[x][y]);

			eGroundObject object(static_cast<eGroundObject>(mGroundObjectMapChip[x][y]));
			colliderInfo.mObjectType = object;


			colliderInfo.mMinPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y));
			colliderInfo.mMaxPosition = 
				DirectX::SimpleMath::Vector2(static_cast<float>(chipX), static_cast<float>(chipY));
			mSaveInfo.push_back(colliderInfo);
		}
	}
}

/*======================================
情報をもとに当たり判定を作成する:private
=========================================*/
void GroundObjectManager::CreateCollider()
{
	int num = static_cast<int>(mSaveInfo.size());

	//情報の数だけ容量を増やす
	mGroundObjectCollider.resize(num);
	mCorresColliderObject.resize(num);

	//簡略化変数の宣言
	DirectX::SimpleMath::Vector3 basepos, minpos, maxpos, halfScale;


	//情報の数だけ行う
	for (int i = 0; i < num; i++)
	{
		//オブジェクトの種類によって処理を変える
		//拡大率をもとに当たり判定用座標を求める
		switch (mSaveInfo[i].mObjectType)
		{
			case eGroundObject::CONIFER:
			{
				/*==================最小値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMinPosition.x+ GOMANAGER_INIT_CSV_POSITION.x;

				//共通の座標を使用(代表して0番目の定数を使用)
				basepos.y = mpConifer[0]->GetConiferModelPositionY();

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMinPosition.y+ GOMANAGER_INIT_CSV_POSITION.y;

				//拡大率の半分を取得
				halfScale = mpConifer[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//最小値を算出
				minpos = basepos - halfScale;
				/*==================ここまで=================*/

				/*==================最大値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//最大値を算出
				maxpos = basepos + halfScale;

				/*==================ここまで=================*/

				break;
			}
			case eGroundObject::MOVE_CAR:
			{
				/*==================最小値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMinPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//共通の座標を使用(代表して0番目の定数を使用)
				basepos.y = mpMoveCar[0]->GetMoveCarModelPositionY();

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMinPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//拡大率の半分を取得
				halfScale = mpMoveCar[0]->GetMoveCarScale() / static_cast<float>(Utility::SCALE_HALF);

				//最小値を算出
				minpos = basepos - halfScale;
				/*==================ここまで=================*/

				/*==================最大値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//最大値を算出
				maxpos = basepos + halfScale;

				/*==================ここまで=================*/

				break;
			}
			case eGroundObject::SHOP:
			{
				/*==================最小値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMinPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//共通の座標を使用(代表して0番目の定数を使用)
				basepos.y = mpShop[0]->GetShopModelPositionY();

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMinPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//拡大率の半分を取得
				halfScale = mpShop[0]->GetConiferScale() / static_cast<float>(Utility::SCALE_HALF);

				//最小値を算出
				minpos = basepos - halfScale;
				/*==================ここまで=================*/

				/*==================最大値を計算==================*/
				//算出した座標+world座標変換
				basepos.x = mSaveInfo[i].mMaxPosition.x + GOMANAGER_INIT_CSV_POSITION.x;

				//算出した座標+world座標変換
				basepos.z = mSaveInfo[i].mMaxPosition.y + GOMANAGER_INIT_CSV_POSITION.y;

				//最大値を算出
				maxpos = basepos + halfScale;

				/*==================ここまで=================*/

				break;
			}
		}
		//情報を設定する
		mGroundObjectCollider[i].SetCollider(minpos, maxpos);
		mCorresColliderObject[i] = mSaveInfo[i].mObjectType;
	}
}

/*================================================================
オブジェクトのサイズを測定する再帰関数:private
==================================================================*/
void GroundObjectManager::Search(int& chipX, int& chipY, int objectNum)
{
	//横隣が同じオブジェクトなら
	if (mGroundObjectMapChip[chipX + 1][chipY] == objectNum)
	{
		chipX++;
		this->Search(chipX, chipY, objectNum);

	}
	//縦を見る
	if(mGroundObjectMapChip[chipX][chipY + 1] == objectNum)
	{
		chipY++;
		this->Search(chipX, chipY, objectNum);
	}
}
/*================================================================
既に当たり判定にあるかをチェックする関数:private
引数：現在のマップチップ座標
返り値：true[既にある]　false[ない]
==================================================================*/
bool GroundObjectManager::OverlapCheck(int x, int y)
{
	//型変換
	DirectX::SimpleMath::Vector2 pos
		(DirectX::SimpleMath::Vector2(static_cast<float>(x), static_cast<float>(y)));

	//設定した当たり判定の内容を走査する
	for (int i = 0; i < static_cast<int>(mSaveInfo.size()); i++)
	{
		if (mSaveInfo[i].mMinPosition.x<= pos.x && mSaveInfo[i].mMaxPosition.x >= pos.x&&
			mSaveInfo[i].mMinPosition.y <= pos.y && mSaveInfo[i].mMaxPosition.y >= pos.y)
		{
			return true;
		}
	}
	return false;
}
