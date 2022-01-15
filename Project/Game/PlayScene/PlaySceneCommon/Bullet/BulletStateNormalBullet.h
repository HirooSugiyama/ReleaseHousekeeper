/*
基本的な弾の移動処理
作成日：2021/10/16
*/

#pragma once


//基底クラス
#include"BulletStateBase.h"


class BulletStateNormalBullet :public BulletStateBase
{
public:

	//コンストラクタ
	BulletStateNormalBullet();

	//デストラクタ
	~BulletStateNormalBullet()override = default;

	//移動処理
	bool Move()override;
};