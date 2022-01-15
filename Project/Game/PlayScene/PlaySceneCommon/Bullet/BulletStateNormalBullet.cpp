/*
基本的な弾の移動処理
作成日：2021/10/16
*/

#include"pch.h"
#include "BulletStateNormalBullet.h"

//前方宣言
#include"Bullet.h"

//関数の使用
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"

/*==================
コンストラクタ
==================*/
BulletStateNormalBullet::BulletStateNormalBullet()
	:
	BulletStateBase()
{
}

/*=======================================
移動処理
返り値：こちらは未使用(別State先で使用)
=======================================*/
bool BulletStateNormalBullet::Move()
{
	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//座標へ反映
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	return false;
}
