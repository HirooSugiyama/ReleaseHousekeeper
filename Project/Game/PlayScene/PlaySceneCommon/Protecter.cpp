/*
拠点クラス
作成日：2021/05/21
*/

#include<pch.h>
#include"Protecter.h"

//モデルの座標
const float Protecter::PROTECTER_MODEL_POSITION_X = -0.51f;
const float Protecter::PROTECTER_MODEL_POSITION_Y = 0.7f;
const float Protecter::PROTECTER_MODEL_POSITION_Z = 16.f;
//モデルの拡大率
	//見た目用
const float Protecter::PROTECTER_MODEL_SCALE_X = 30.0f;
const float Protecter::PROTECTER_MODEL_SCALE_Y = 10.5f;
const float Protecter::PROTECTER_MODEL_SCALE_Z = 5.5f;

//モデル生成ミスの角度調整
const float Protecter::PROTECTER_DEBUG_SHIFT_ANGLE = 180.f;


/*==============
コンストラクタ
==============*/
Protecter::Protecter()
	:
	mpProtecterModel(nullptr),
	mDamageFlag(false)
{

	mpProtecterModel = std::make_unique<BoxModel>();
}

/*===================================
デストラクタ
===================================*/
Protecter::~Protecter()
{
}

/*==============
初期化
==============*/
void Protecter::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("House");
	mpProtecterModel->SetModel(model);


	DirectX::SimpleMath::Vector3 pos, scale;
	pos.x = PROTECTER_MODEL_POSITION_X;
	pos.y = PROTECTER_MODEL_POSITION_Y;
	pos.z = PROTECTER_MODEL_POSITION_Z;

	mpProtecterModel->SetPosition(pos);
	mpProtecterModel->SetScale(scale);
	mpProtecterModel->SetScale(DirectX::SimpleMath::Vector3::One);
	mpProtecterModel->SetRotationY(PROTECTER_DEBUG_SHIFT_ANGLE);

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpProtecterModel->ReturnHalfSize
	(
		DirectX::SimpleMath::Vector3
		(
			PROTECTER_MODEL_SCALE_X,
			PROTECTER_MODEL_SCALE_Y,
			PROTECTER_MODEL_SCALE_Z
		)
	);
	//設定
	mpProtecterModel->SetAABBCollider(pos - halfsize, pos + halfsize);
}

/*==============
描画
==============*/
void Protecter::Draw()
{
	mpProtecterModel->Draw();
}

/*==========================
ぼろ屋に切り替え
==========================*/
void Protecter::ChangeOldHouse()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("OldHouseSet");
	mpProtecterModel->SetModel(model);
}

