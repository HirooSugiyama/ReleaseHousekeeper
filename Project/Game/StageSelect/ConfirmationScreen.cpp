/*
確認画面
作成日：2021/10/21
*/
#include"pch.h"

#include"ConfirmationScreen.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//画像拡大率
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_SCALE(2.f, 2.f);
//初期座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_TEX_INIT_POSITION(250.f, 250.f);

//文字描画
//共通処理
//拡大率
const float ConfirmationScreen::STRING_SCALE = 3.f;
//YES
//座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_YES_POSITION(700.f, 350.f);
//No
//座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_NO_POSITION =
STRING_YES_POSITION + DirectX::SimpleMath::Vector2(0.f, 60.f);


//確認画面用カーソルの基本情報
//拡大率
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_SCALE(2.5f, 2.5f);
//初期座標
const DirectX::SimpleMath::Vector2 ConfirmationScreen::CONFI_CURSOR_INIT_POSITION =
STRING_NO_POSITION + DirectX::SimpleMath::Vector2(-50.f, 20.f);
//移動幅
const float ConfirmationScreen::CONFI_CURSOR_SHIFT = 60.f;


//文字テクスチャ
//拡大率
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_SCALE(1.f, 1.f);
//座標
const  DirectX::SimpleMath::Vector2 ConfirmationScreen::STRING_TEXTURE_POSITION =
CONFI_TEX_INIT_POSITION + DirectX::SimpleMath::Vector2(-250.f, -250.f);
/*===================================
コンストラクタ
===================================*/
ConfirmationScreen::ConfirmationScreen()
	:mpConfirTexture()
	, mpCursor()
	, mSelectFlag(false)	//true:Yes,false:No
	, mpStringTexture()
{
	mpConfirTexture = std::make_unique<ObjectTexture>();
	mpCursor = std::make_unique<Cursor>();
	mpStringTexture = std::make_unique<ObjectTexture>();
}

/*==================================
デストラクタ
===================================*/
ConfirmationScreen::~ConfirmationScreen()
{
}

/*===================================
初期化処理
===================================*/
void ConfirmationScreen::Initialize()
{
	//初期化処理
	mpConfirTexture->Initialize();
	mpStringTexture->Initialize();

	//リソースの取得
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("Confir");

	//画像の設定
	mpConfirTexture->SetTexture(texture);

	//texture = pRM->GetTexture("English");
	texture = pRM->GetTexture("Japanise");
	mpStringTexture->SetTexture(texture);

	//拡大率の設定
	mpConfirTexture->SetScale(CONFI_TEX_SCALE);
	mpStringTexture->SetScale(STRING_TEXTURE_SCALE);

	//座標の設定
	mpConfirTexture->SetPosition(CONFI_TEX_INIT_POSITION);
	mpStringTexture->SetPosition(STRING_TEXTURE_POSITION);

	//カーソルの初期化処理
	mpCursor->Initialize(
		CONFI_CURSOR_INIT_POSITION,
		CONFI_CURSOR_SCALE,
		CONFI_CURSOR_SHIFT);
}

/*=================================
描画処理
===================================*/
void ConfirmationScreen::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//↓が押され、現在の選択肢がNoだった場合
	if ((pKey->SelectOver() || pGamePad->ChangeCursorUp()) && !mSelectFlag)
	{
		//Yesとする
		mSelectFlag = true;

		//カーソルを移動する
		mpCursor->CursorUp();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
	//↑が押され、現在の選択肢がYesだった場合
	else if ((pKey->SelectUnder() || pGamePad->ChangeCursorDown()) && mSelectFlag)
	{
		//Noとする
		mSelectFlag = false;
		//カーソルを移動する
		mpCursor->CursorDown();
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_SELECT);
	}
}

/*==================================
描画処理
引数：点滅フラグ
===================================*/
void ConfirmationScreen::Draw(bool const& blinkingFlag)
{
	//画像の描画
	mpConfirTexture->Draw();
	mpStringTexture->Draw();

	//描画処理
	mpCursor->Draw(true);

	//文字の描画処理
	this->DrawString(blinkingFlag);
}

/*==================================
文字の描画処理:private
引数：点滅フラグ
===================================*/
void ConfirmationScreen::DrawString(bool const& blinkingFlag)
{
	//選択肢がYesの時点滅させる
	if (mSelectFlag)
	{
		if (blinkingFlag)
		{
			//[Yes]の描画
			Utility::DrawString
			(
				L" Yes",
				STRING_YES_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);

		}
		//[No]の描画
		Utility::DrawString
		(
			L" No",
			STRING_NO_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);
	}
	else
	{
		//[Yes]の描画
		Utility::DrawString
		(
			L" Yes",
			STRING_YES_POSITION,
			DirectX::Colors::Black,
			STRING_SCALE
		);

		if (blinkingFlag)
		{
			//[No]の描画
			Utility::DrawString
			(
				L" No",
				STRING_NO_POSITION,
				DirectX::Colors::Black,
				STRING_SCALE
			);
		}
	}
}
