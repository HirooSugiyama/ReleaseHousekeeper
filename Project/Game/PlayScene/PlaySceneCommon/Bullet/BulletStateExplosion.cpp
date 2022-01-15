/*
爆発する弾の移動処理
作成日：2021/10/16
*/

#include"pch.h"
#include "BulletStateExplosion.h"

//前方宣言
#include"Bullet.h"

//関数の使用
#include"../ObjectModel/SphereModel.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//重力定数の使用
#include"../../PlaySceneDefence/Gravity.h"

//重力定数
const float BulletStateExplosion::GRAVITY = Gravity::mGravityConstant;

//初期速度
const float BulletStateExplosion::FIRST_VELOCITY = 0.3f;

//最初の高さ
const float BulletStateExplosion::FIRST_HEIGHT = 1.f;


//エフェクトを出現させる座標
const DirectX::SimpleMath::Vector3 BulletStateExplosion::EFFECT_SHIFT_POSITION(0.f, 2.5f, 0.f);

/*==================
コンストラクタ
==================*/
BulletStateExplosion::BulletStateExplosion()
	:
	BulletStateBase(),
	mBulletVelocity(FIRST_VELOCITY),
	mBulletHeight(FIRST_HEIGHT)
{
}

/*======================================
移動処理
返り値：こちらは未使用(別State先で使用)
=======================================*/
bool BulletStateExplosion::Move()
{
	//もし爆発フラグが立っていたら
	if (BulletStateBase::GetBullet()->GetExplosionFlag())
	{
		//エフェクトを発生させる
		//エフェクトマネージャーの取得
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::BOMB);
		effect->SetPosition(BulletStateBase::GetBullet()->GetBulletModel()->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetScale(effect->GetScale());
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		//未使用状態とする
		this->Reset();
		return true;
	}


	mBulletVelocity -= GRAVITY;
	mBulletHeight += mBulletVelocity;

	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//座標へ反映
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	DirectX::SimpleMath::Vector3 pos = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
	pos.y = mBulletHeight;

	BulletStateBase::GetBullet()->GetBulletModel()->SetPosition(pos);
	

	//地面より下に行ったら
	if (pos.y <= 0.f)
	{
		//爆発フラグを建てる
		BulletStateBase::GetBullet()->SetExplosionFlag(true);
		BulletStateBase::GetBullet()->SetDoubleCollider();
	}

	return false;	
}

/*======================================
描画処理
=======================================*/
void BulletStateExplosion::Draw()
{

}

/*======================================
リセット処理
=======================================*/
void BulletStateExplosion::Reset()
{
	mBulletVelocity = FIRST_VELOCITY;
	mBulletHeight = FIRST_HEIGHT;
}