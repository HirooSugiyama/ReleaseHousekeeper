/*
ひとつのフェーズの始まりのテクスチャを管理するクラス
作成日：2021/09/18
*/
#include"pch.h"

#include"PhaseCursor.h"

//前方宣言
#include"../Common/ObjectTexture.h"


//画像の拡大率
const DirectX::SimpleMath::Vector2 PhaseCursor::PHASECURSOR_TEXTURE_SCALE(1.f,1.f);

/*===================================
コンストラクタ
===================================*/
PhaseCursor::PhaseCursor()
	:
	mpPhaseCursorTexture()
{
	mpPhaseCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
デストラクタ
===================================*/
PhaseCursor::~PhaseCursor()
{
}

/*=================================
初期化処理
===================================*/
void PhaseCursor::Initialize()
{
	//リソースの取得
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("PhaseCursor");

	//画像を設定する
	mpPhaseCursorTexture->SetTexture(texture);

	//初期化処理
	mpPhaseCursorTexture->Initialize();
	mpPhaseCursorTexture->SetScale(PHASECURSOR_TEXTURE_SCALE);
}

/*===================================
更新処理
===================================*/
void PhaseCursor::Update()
{

}

/*===================================
描画処理
===================================*/
void PhaseCursor::Draw()
{
	mpPhaseCursorTexture->Draw();
}

/*===================================
座標の取得
===================================*/
void PhaseCursor::SetPosition(DirectX::SimpleMath::Vector2 const& pos)
{
	mpPhaseCursorTexture->SetPosition(pos);
}




