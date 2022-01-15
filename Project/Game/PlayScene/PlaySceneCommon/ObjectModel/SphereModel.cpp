/*
球の当たり判定を持ったモデルクラス
作成日：2021/06/12
*/

#include"pch.h"
#include"SphereModel.h"

//当たり判定初期値
const float SphereModel::InitCollider = 0.f;

/*===================================
コンストラクタ
===================================*/
SphereModel::SphereModel()
	:
	ObjectModel(),
	mpSphereCollider()
{
	mpSphereCollider = std::make_unique<Sphere>();
	mpSphereCollider->mRadius = InitCollider;
}

/*===================================
デストラクタ
===================================*/
SphereModel::~SphereModel()
{
}

/*===================================
当たり判定の設定
===================================*/
void SphereModel::SetSphereCollider(const DirectX::SimpleMath::Vector3& center, float radius)
{
	mpSphereCollider->mCenter = center;
	mpSphereCollider->mRadius = radius;
}