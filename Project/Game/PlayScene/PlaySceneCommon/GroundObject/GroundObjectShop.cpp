/*
針葉樹のモデルを管理するクラス
作成日：2021/08/19
*/

#include"pch.h"

#include "GroundObjectShop.h"


//ショップモデルの拡大率
const DirectX::SimpleMath::Vector3 GroundObjectShop::SHOP_SCALE(4.f, 4.f, 4.f);
//ショップモデルのY座標
const float GroundObjectShop::SHOP_MODEL_POSITION_Y = 1.f;


/*======================
コンストラクタ
======================*/
GroundObjectShop::GroundObjectShop()
	:
	IGroundObject(),
	mpShopModel(nullptr)
{
	mpShopModel = std::make_unique<ObjectModel>();
}

/*======================
デストラクタ
======================*/
GroundObjectShop::~GroundObjectShop()
{

}

/*======================
初期化
======================*/
void GroundObjectShop::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Shop");

	//モデルの設定
	mpShopModel->SetModel(model);
	//拡大率の設定
	mpShopModel->SetScale(SHOP_SCALE);
}

/*======================
描画処理
======================*/
void GroundObjectShop::Draw()
{
	mpShopModel->Draw();
}

/*====================================
モデルの座標を設定する
引数：モデルの座標
====================================*/
void GroundObjectShop::SetShopModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpShopModel->SetPosition(pos);
}
