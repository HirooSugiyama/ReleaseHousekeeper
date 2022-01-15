/*
ステージ選択シーン
*/

#include "pch.h"

#include "../GameMain.h"
#include "DeviceResources.h"

#include "StageSelectScene.h"


//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"






//番号の縦移動
const int StageSelectScene::SELECTNUM_VERTICAL_SHIFT = 5;

//カーソルの拡大率
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_SCALE(0.6f,0.5f);
//初期座標						  
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_INIT_POSITION(150.f,20.f);
//移動量							
const DirectX::SimpleMath::Vector2 StageSelectScene::CURSOR_VELOCITY(530.f, 150.f);
//タグの初期座標
const DirectX::SimpleMath::Vector2 StageSelectScene::TAG_INIT_POSITION(113.f, 142.f);
//幅
const float StageSelectScene::TAG_SHIFT = 100.f;
//確認画面用カーソルの基本情報
//拡大率
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_SCALE(2.5f, 2.5f);
//初期座標
const DirectX::SimpleMath::Vector2 StageSelectScene::SELECT_CURSOR_INIT_POSITION(30.f, 137.f);
//移動幅
const float StageSelectScene::SELECT_CURSOR_SHIFT = 98.f;

//題の位置
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_POSITION(450.f,15.f);
const DirectX::SimpleMath::Vector2 StageSelectScene::NAME_SCALE(2.f, 2.f);


/*=========================================
コンストラクタ
=========================================*/
StageSelectScene::StageSelectScene()
	:
	mSelectNum(1),
	mpCursor(),
	mpStageInfo(),
	mpTag(),
	mpConfirScreen(),
	mpTextureBlinking(),
	mSelectFlag(false),
	mBGMID(Utility::EXCEPTION_NUM),
	mpCloud(nullptr),
	mpStageSelectNameTexture(nullptr)
{
	mpCursor = std::make_unique<Cursor>();
	mpStageInfo = std::make_unique<StageInfomation>();
	mpConfirScreen = std::make_unique<ConfirmationScreen>();
	mpTextureBlinking = std::make_unique<Blinking>();
	mpCloud = std::make_unique<Cloud>();
	mpStageSelectNameTexture = std::make_unique<ObjectTexture>();

	for (int i = 0; i< SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i] = std::make_unique<StageNumberTag>();
	}
}
/*========================================
デストラクタ
=========================================*/
StageSelectScene::~StageSelectScene()
{

}

/*=========================================
初期化
=========================================*/
void StageSelectScene::Initialize()
{
	// リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	pRM->SetuseScene(eLoadScene::STAGE_SELECT);//プレイシーンで使うリソースの指定
	pRM->Initialize(L"Resources/CSV/Resources.csv");

	// テクスチャの読み込み
	mpTexture = pRM->GetTexture("StageSelect");

	mpStageSelectNameTexture->SetTexture(pRM->GetTexture("StageSelectName"));
	mpStageSelectNameTexture->Initialize();
	mpStageSelectNameTexture->SetPosition(NAME_POSITION);
	mpStageSelectNameTexture->SetScale(NAME_SCALE);

	//カーソルの初期化処理
	mpCursor->Initialize(
		SELECT_CURSOR_INIT_POSITION,
		SELECT_CURSOR_SCALE,
		SELECT_CURSOR_SHIFT);

	//ステージ各種情報の初期化処理
	mpStageInfo->Initialize();

	for (int i = 0;  i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->Initialize();
	}

	//ステージ番号を保存する
	this->SetNumberTag();

	//確認画面の初期化処理
	mpConfirScreen->Initialize();

	//曲を流す
	this->PlayBGM();

	//雲の初期化処理
	mpCloud->Initialize();
}

/*=========================================
更新
引数	：タイマーのヘルパー関数
戻り値	：次のシーン番号
=========================================*/
eGameScene StageSelectScene::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//ステージ選択
	this->StageSelect();

	//点滅処理
	mpTextureBlinking->Update();

	//雲の更新処理
	mpCloud->Update();

	//選択画面なら
	if (mSelectFlag)
	{
		//確認画面の更新処理
		mpConfirScreen->Update();
	}


	if (pKey->Decision()|| pGamePad->Decision())		//決定
	{	
		//確認画面ならば
		if (mSelectFlag)
		{
			if (mpConfirScreen->GetSelectFlag())
			{
				//プレイシーンへ
				//ステージ選択画面からの情報共有管理クラスの取得
				StoPSceneInterface& pStoP = StoPSceneInterface::GetStoPIFInstance();

				pStoP.SetStageCSV(this->SetFileName());
				//ステージ番号も同時に保存しておく
				pStoP.SetStageNumber(std::to_string(mSelectNum));

				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
				//曲を止める
				this->StopBGM();

				ScreenTransitionInterface& pSTI = ScreenTransitionInterface::GetScreenTransitionInstance();
				pSTI.SetFadeUseFlag(true);
				pSTI.GetFade()->SetClose();

				return eGameScene::PLAY;	//直接プレイシーンへ
			}
			else
			{
				mSelectFlag = false;
			}
			
		}
		else
		{

			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
			mSelectFlag = true;
		}		
	}

	return eGameScene::NONE;
}

/*=======================================
描画
=========================================*/
void StageSelectScene::Draw()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

	//描画開始
	pDxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		pDxIF.GetCommonStates()->NonPremultiplied()
	);
	
	DirectX::SimpleMath::Vector2 pos{ 0.f,0.f };

	pDxIF.GetSpriteBatch()->Draw(mpTexture.Get(), pos);

	//雲の描画処理
	mpCloud->Draw();

	//題の描画
	mpStageSelectNameTexture->Draw();
	

	//選択画面ではないなら
	if (!mSelectFlag)
	{
		//カーソルの描画
		mpCursor->Draw();

		//ステージ情報の描画
		mpStageInfo->Draw(mSelectNum);

		//ステージ番号を仮保存
		int stageScreenNum = mSelectNum;
		//もし2画面目以降のステージなら
		if (stageScreenNum >= static_cast<int>(eSelectNum::_7))
		{
			//1画面分値を減らす
			stageScreenNum -= static_cast<int>(eSelectNum::_6);
		}

		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//選択しているステージのみ点滅させる
			if (stageScreenNum - 1 == i)
			{
				mpTag[i]->Draw(mpTextureBlinking->GetBlinkingFlag());
			}
			else
			{
				//それ以外は通常描画
				mpTag[i]->Draw();
			}

		}
	}
	else
	{
		//カーソルの描画
		mpCursor->Draw();

		//ステージ情報の描画
		mpStageInfo->Draw(mSelectNum);
		//各ステージ番号の描画
		for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
		{
			//それ以外は通常描画
			mpTag[i]->Draw();
		}
		
		mpConfirScreen->Draw(mpTextureBlinking->GetBlinkingFlag());
	}

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
終了処理
=========================================*/
void StageSelectScene::Finalize()
{
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	pDxIF.Destroy();
}


/*=========================================
モード選択:private
=========================================*/
void StageSelectScene::StageSelect()
{
	//選択画面でないなら処理を行う
	if (!mSelectFlag)
	{
		//カーソルを上げる
		this->CursorUp();

		//カーソルを下げる
		this->CursorDown();
	}
}


/*=========================================
ファイル名算出:private
=========================================*/
std::string StageSelectScene::SetFileName()
{
	std::string filetop = "Resources/CSV/PlayScene",
		filemiddle = "none",
		filebottom=".csv",
		filename="none";

	filemiddle = std::to_string(mSelectNum);
	
	filename = filetop + filemiddle + filebottom;
	return filename;
}

/*=========================================
カーソルをあげる:private
=========================================*/
void StageSelectScene::CursorUp()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->SelectOver()|| pGamePad->ChangeCursorUp())
	{
		//最大ステージ数ではないなら処理を通す
		if (mSelectNum-1 != static_cast<int>(eSelectNum::NONE))
		{
			//画像を上へ
			mpCursor->CursorUp();
			mSelectNum--;
			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
		}
		//7番になったらカーソル位置をリセットする
		if (mSelectNum == static_cast<int>(eSelectNum::_7))
		{
			mpCursor->CursorReset();
			//ステージ番号を保存する
			this->SetNumberTag();
		}
		//6番になったら指定の位置にカーソルをセットする
		if (mSelectNum == static_cast<int>(eSelectNum::_6))
		{
			mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
			//ステージ番号を保存する
			this->SetNumberTag();
		}
	}	
}

/*=========================================
カーソルをさげる:private
=========================================*/
void StageSelectScene::CursorDown()
{

	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	if (pKey->SelectUnder()|| pGamePad->ChangeCursorDown())
	{
		//最小ステージ数ではないなら処理を通す
		if (mSelectNum+1 != static_cast<int>(eSelectNum::NUM))
		{
			//画像を下へ
			mpCursor->CursorDown();
			mSelectNum++;
			ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
		}
		//7番になったらカーソル位置をリセットする
		if (mSelectNum == static_cast<int>(eSelectNum::_7))
		{
			mpCursor->CursorReset();
			//ステージ番号を保存する
			this->SetNumberTag();
		}
		//6番になったら指定の位置にカーソルをセットする
		if (mSelectNum == static_cast<int>(eSelectNum::_6))
		{
			mpCursor->CursorSetUnder(static_cast<int>(eSelectNum::_6));
			//ステージ番号を保存する
			this->SetNumberTag();
		}
	}	
}

/*========================================
番号を設定する:private
=========================================*/
void StageSelectScene::SetNumberTag()
{
	int index = 0;
	int stagenum = 0;
	//リセットする
	for (int i = 0; i < SCREEN_STEGE_MAX_NUM; i++)
	{
		mpTag[i]->SetStageNum(Utility::EXCEPTION_NUM);
	}
	
	//上半分なら
	if (mSelectNum <= static_cast<int>(eSelectNum::_6))
	{
		index = 0;
		stagenum = static_cast<int>(eSelectNum::_1);
	}
	else 
	{
		index = 0;
		stagenum = static_cast<int>(eSelectNum::_7);
	}

	//リセットする
	for (index; index < SCREEN_STEGE_MAX_NUM; index++,stagenum++)
	{
		mpTag[index]->SetStageNum(stagenum);

		mpTag[index]->SetPosition(TAG_INIT_POSITION+ DirectX::SimpleMath::Vector2(0.f,(index *TAG_SHIFT)));
		if (stagenum > static_cast<int>(eSelectNum::_8))
		{
			break;
		}
	}

}

/*=========================================
音楽を流す:private
=========================================*/
void StageSelectScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_STAGESELECT);
}

/*=========================================
音楽を止める:private
=========================================*/
void StageSelectScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
