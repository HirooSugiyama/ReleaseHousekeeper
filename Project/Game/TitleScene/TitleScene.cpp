/*
タイトルシーン
*/

#include "pch.h"

#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "../GameMain.h"
#include "DeviceResources.h"

#include "TitleScene.h"

#include"Game/Common/Cloud.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"

//ロゴの座標
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_LOGO_POSITION(190.f, 160.f);


/*=========================================
コンストラクタ
=========================================*/
TitleScene::TitleScene()
	:
	mpCloud(),
	mBGMID(Utility::EXCEPTION_NUM)
{
	//雲の生成
	mpCloud = std::make_unique<Cloud>();
}

/*=========================================
デストラクタ
=========================================*/
TitleScene::~TitleScene()
{
}

/*=========================================
初期化
=========================================*/
void TitleScene::Initialize()
{
	// リソース関係の初期設定
	//リソースマネージャに画像を保存する
	auto pRM = ResourceManager::GetInstance();
	pRM->SetuseScene(eLoadScene::TITLE);//プレイシーンで使うリソースの指定
	pRM->Initialize(L"Resources/CSV/Resources.csv");

	// テクスチャの読み込み
	mpTexture = pRM->GetTexture("TitleTexture");
	mpLogo = pRM->GetTexture("TitleLogo");
	
	//動く雲の初期化処理
	mpCloud->Initialize();

	//BGMを流す
	this->PlayBGM();
}

/*=========================================
更新
引数	：タイマーのヘルパー関数
戻り値	：次のシーン番号
=========================================*/
eGameScene TitleScene::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	// マウス入力情報を取得する
	auto mouseState = DirectX::Mouse::Get().GetState();

	mpCloud->Update();

	// サウンドの更新
	ADX2::GetInstance().Update();

	if (pKey->Decision()|| pGamePad->Decision())//キー入力が行われたら
	{
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_CHOICE);
		//曲を止める
		this->StopBGM();
		return eGameScene::STAGE_SELECT;//次のシーンへ
	}

	return eGameScene::NONE;
}

/*=========================================
描画
=========================================*/
void TitleScene::Draw()
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
	
	mpCloud->Draw();

	pDxIF.GetSpriteBatch()->Draw(mpLogo.Get(), TITLE_LOGO_POSITION);
	

	pDxIF.GetSpriteBatch()->End();
}

/*=========================================
終了処理
=========================================*/
void TitleScene::Finalize()
{
	// リソース関係の初期化
	auto pRM = ResourceManager::GetInstance();
	pRM->Finalize();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	pDxIF.Destroy();
}

/*========================================
音楽を流す:private
=========================================*/
void TitleScene::PlayBGM()
{
	mBGMID = ADX2::GetInstance().Play(CRI_CUESHEET_0_BGM_TITLE);
}

/*=========================================
音楽を止める:private
=========================================*/
void TitleScene::StopBGM()
{
	ADX2::GetInstance().Stop(mBGMID);
}
