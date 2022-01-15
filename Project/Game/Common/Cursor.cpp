/*
カーソルを管理するクラス
作成日：2021 / 10 / 13
*/
#include"pch.h"

#include"Cursor.h"

//前方宣言
#include"../Common/ObjectTexture.h"

/*=================================
コンストラクタ
===================================*/
Cursor::Cursor()
	:
	mpCursorTexture(nullptr),
	mShiftNum(0.f),
	mSaveInitPosition(DirectX::SimpleMath::Vector2::Zero)
{
	mpCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
Cursor::~Cursor()
{
}

/*===================================
初期化処理
引数：	画像の初期座標、画像拡大率
		移動幅、回転率[default 0.f]
===================================*/
void Cursor::Initialize(
	DirectX::SimpleMath::Vector2 const& initPosition,
	DirectX::SimpleMath::Vector2 const& scale,
	float const& shiftPosition,
	float const& rot)
{
	//初期化処理
	mpCursorTexture->Initialize();

	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto Textute = pRM->GetTexture("StageCursor");

	//画像の設定
	mpCursorTexture->SetTexture(Textute);

	//拡大率の設定
	mpCursorTexture->SetPosition(initPosition);
	mSaveInitPosition = initPosition;

	//拡大率の設定
	mpCursorTexture->SetScale(scale);

	//回転率の設定
	mpCursorTexture->SetRot(rot);

	//移動幅の保存
	mShiftNum = shiftPosition;
}

/*=========================================
描画処理
引数：描画フラグ(trueで描画)(default:true)
===========================================*/
void Cursor::Draw(bool const& flag)
{
	if (!flag)return;

	//画像の描画
	mpCursorTexture->Draw();
}

/*=================================
カーソルを上に移動する
===================================*/
void Cursor::CursorUp()
{
	//上に移動させる
	mpCursorTexture->SetPosition
	(
		mpCursorTexture->GetPosition() - 
		DirectX::SimpleMath::Vector2(0.f, mShiftNum)
	);
}

/*===================================
カーソルを初期位置にリセットする
===================================*/
void Cursor::CursorReset()
{
	//上に移動させる
	mpCursorTexture->SetPosition(mSaveInitPosition);
}

/*===================================
カーソルを一番下にセットする
引数：1画面の最大ステージ数
===================================*/
void Cursor::CursorSetUnder(int const& screenMaxStageNum)
{
	//下に移動させる
	mpCursorTexture->SetPosition
	(
		mSaveInitPosition +
		DirectX::SimpleMath::Vector2(0.f, mShiftNum *(screenMaxStageNum +(Utility::EXCEPTION_NUM)))
	);
}

/*===================================
カーソルを下に移動する
===================================*/
void Cursor::CursorDown()
{
	//下に移動させる
	mpCursorTexture->SetPosition(mpCursorTexture->GetPosition() + DirectX::SimpleMath::Vector2(0.f, mShiftNum));
}