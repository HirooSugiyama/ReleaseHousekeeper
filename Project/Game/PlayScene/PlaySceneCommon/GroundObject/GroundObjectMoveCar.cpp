/*
動き出す車のモデルを管理するクラス
作成日：2021/08/19
*/

#include"pch.h"

#include "GroundObjectMoveCar.h"

//モデルの拡大率
const DirectX::SimpleMath::Vector3 GroundObjectMoveCar::MOVE_CAR_SCALE(3.f,3.f,3.f);
	//針葉樹モデルのY座標
const float GroundObjectMoveCar::MOVE_CAR_MODEL_POSITION_Y = 1.f;



/*======================
コンストラクタ
======================*/
GroundObjectMoveCar::GroundObjectMoveCar()
	:
	IGroundObject(),
	mpMoveCarModel(nullptr)
{
	mpMoveCarModel = std::make_unique<ObjectModel>();
}

/*======================
デストラクタ
======================*/
GroundObjectMoveCar::~GroundObjectMoveCar()
{
}

/*======================
初期化
======================*/
void GroundObjectMoveCar::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("GreenCar");

	//モデルの設定
	mpMoveCarModel->SetModel(model);
	//拡大率の設定
	mpMoveCarModel->SetScale(MOVE_CAR_SCALE);
}

/*======================
更新処理
======================*/
void GroundObjectMoveCar::Update()
{


}

/*======================
描画処理
======================*/
void GroundObjectMoveCar::Draw()
{
	mpMoveCarModel->Draw();
}

/*====================================
モデルの座標を設定する
引数：モデルの座標
====================================*/
void GroundObjectMoveCar::SetMoveCarModelPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mpMoveCarModel->SetPosition(pos);
}
