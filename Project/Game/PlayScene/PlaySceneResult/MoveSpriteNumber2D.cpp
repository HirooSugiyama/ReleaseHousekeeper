/*
新規実行ファイル

*/
#include"pch.h"

#include"MoveSpriteNumber2D.h"

/*===================================
コンストラクタ
===================================*/
MoveSpriteNumber2D::MoveSpriteNumber2D()
	:
	mpMoveNumber(),
	mpSpriteNumber2D(),
	mDrawPosition()
{
	mpMoveNumber = std::make_unique<MoveNumber>();
	mpSpriteNumber2D = std::make_unique<SpriteNumber2D>();
}

/*===================================
デストラクタ
===================================*/
MoveSpriteNumber2D::~MoveSpriteNumber2D()
{
}

/*===================================
初期化処理
引数：	画像パス
		最初の値
		移動速度(秒)
		最大値
===================================*/
void MoveSpriteNumber2D::Initialize(std::string const& textureKey,
									int const& firstNum,
									float const& moveSecondSpeed,
									int const& maxNum)
{

	//画像クラスの初期化処理
	mpSpriteNumber2D->SetTextureKey(textureKey);
	mpSpriteNumber2D->Initialize();

	//移動処理の初期化処理
	mpMoveNumber->Initialize(firstNum, moveSecondSpeed, maxNum);
}

/*=================================
更新処理
引数：タイマー
返り値：現在の値
===================================*/
int MoveSpriteNumber2D::Update(DX::StepTimer const& timer)
{
	mpMoveNumber->Update(timer);

	return mpMoveNumber->GetMoveNum();
}

/*===================================
描画処理
===================================*/
void MoveSpriteNumber2D::Draw()
{
	//画像描画
	mpSpriteNumber2D->Create(mpMoveNumber->GetMoveNum(), mDrawPosition);
	mpSpriteNumber2D->Draw();
}
