/*
ステージ選択タグ
作成日：2021/10/21
*/
#include"pch.h"

#include"StageNumberTag.h"

//画像拡大率
const DirectX::SimpleMath::Vector2 StageNumberTag::TEX_SCALE(1.7f,2.2f);

//画像描画位置から数字描画位置を算出するための定数
const DirectX::SimpleMath::Vector2 StageNumberTag::NUM_SHIFT(60.f,-20.f);

/*=================================
コンストラクタ
===================================*/
StageNumberTag::StageNumberTag()
	:
	mpBackGround(nullptr),
	mDrawStageString(),
	mDrawPosition()
{
	mpBackGround = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
StageNumberTag::~StageNumberTag()
{
}

/*===================================
初期化処理
===================================*/
void StageNumberTag::Initialize()
{
	//初期化処理
	mpBackGround->Initialize();

	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("StageTag");

	//画像の設定
	mpBackGround->SetTexture(texture);
	//拡大率の設定
	mpBackGround->SetScale(TEX_SCALE);

}

/*===================================
描画処理
引数：描画フラグ(false 描画しない)
===================================*/
void StageNumberTag::Draw(bool const& flag)
{
	//例外数字なら処理を行わない
	if (mDrawStageString == -1)
	{
		return;
	}
	if (!flag)
	{
		return;
	}

	//背景の描画
	mpBackGround->Draw();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	wchar_t buf[32];

	swprintf_s(buf, 32, L" Stage%d", mDrawStageString);
	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf, 
		mDrawPosition+ NUM_SHIFT,
		DirectX::Colors::Black,
		0, 
		DirectX::SimpleMath::Vector2::Zero,
		Utility::STRING_SIZE_MEDIUM
	);
}

/*===================================
描画位置の指定
引数：座標
===================================*/
void StageNumberTag::SetPosition(DirectX::SimpleMath::Vector2 const& pos)
{
	mDrawPosition = pos;
	mpBackGround->SetPosition(pos);
}




