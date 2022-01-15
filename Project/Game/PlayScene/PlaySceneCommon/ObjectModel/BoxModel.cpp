/*
AABBの当たり判定を持ったモデルクラス
作成日：2021/06/12
*/

#include"pch.h"
#include"BoxModel.h"

//定数
//初期化値
const DirectX::SimpleMath::Vector3 BoxModel::InitCollider(-10.f, -10.f, -10.f);

/*===================================
コンストラクタ
===================================*/
BoxModel::BoxModel()
	:
	ObjectModel(),
	mpAABBCollider()
{
	mpAABBCollider = std::make_unique<AABB>();
	mpAABBCollider->mMin = InitCollider;
	mpAABBCollider->mMax = InitCollider;
}

/*===================================
デストラクタ
===================================*/
BoxModel::~BoxModel()
{
}


/*==================================================
拡大率の半分を返す(最小値、最大値の算出に使用)
引数：拡大率
返り値：拡大率の半分の値
====================================================*/
DirectX::SimpleMath::Vector3 BoxModel::ReturnHalfSize(DirectX::SimpleMath::Vector3 const& scale)
{
	DirectX::SimpleMath::Vector3 returnsize;

	returnsize.x = scale.x / Utility::SCALE_HALF;
	returnsize.y = scale.y / Utility::SCALE_HALF;
	returnsize.z = scale.z / Utility::SCALE_HALF;
	return returnsize;
}

/*=========================================
情報のセッター
引数：min(最小値)、max(最大値)
=========================================*/
void BoxModel::SetAABBCollider(DirectX::SimpleMath::Vector3 const& min,
	DirectX::SimpleMath::Vector3 const& max)
{
	mpAABBCollider->mMin = min;
	mpAABBCollider->mMax = max;
}
