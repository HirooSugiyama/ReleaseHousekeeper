/*
敵行動パターン
作成日：2021/08/31
*/

#include"pch.h"
#include "EStateWalk.h"

//前方宣言
#include"Enemy.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"


//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
const DirectX::SimpleMath::Vector3 EStateWalk::ESTATE_COLLIDER_POSITION(0.f,0.f,1.f);

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EStateWalk::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//移動速度
const float EStateWalk::ENEMY_MOVE_SPEED = 0.03f;

//モデル角度
const float EStateWalk::ESTATE_MODEL_ANGLE_STRAIGHT = 180.f;
const float EStateWalk::ESTATE_MODEL_ANGLE_RIGHT = 270.f;
const float EStateWalk::ESTATE_MODEL_ANGLE_LEFT = 90.f;

/*============================
コンストラクタ
============================*/
EStateWalk::EStateWalk()
	:
	EnemyStateBase(),
	mpWalkCollider(nullptr),
	mpEnemy(nullptr),
	mChaseVelocity(DirectX::SimpleMath::Vector3::Zero)
{
	mpWalkCollider = std::make_unique<AABB>();
}

/*============================
デストラクタ
============================*/
EStateWalk::~EStateWalk()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateWalk::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;
}

/*============================
更新処理
============================*/
void EStateWalk::Update()
{
	//状態に応じて処理を変更する
	switch (mpEnemy->GetEnemyWalkState())
	{
		case eEnemyWalkState::GENERALLY:
		{
			//変換用変数の宣言
			DirectX::SimpleMath::Vector3 vel;

			//敵の今向いている向きに応じて処理を行う
			switch (mpEnemy->GetAngleEnemy())
			{
				case eAngleEnemy::STRAIGHT:
				{
					vel.z = ENEMY_MOVE_SPEED;	//Z方向に動かす
					break;
				}
				case eAngleEnemy::LEFT:
				{
					vel.x = -ENEMY_MOVE_SPEED;	//-X方向に動かす
					break;
				}
				case eAngleEnemy::RIGHT:
				{
					vel.x = ENEMY_MOVE_SPEED;	//X方向に動かす
					break;
				}
			}

			//モデルを移動させる
			mpEnemy->GetBoxModel()->Move(vel);

			break;
		}
		case eEnemyWalkState::CHASING:
		{
			if (mChaseVelocity == DirectX::SimpleMath::Vector3::Zero)
			{
				mpEnemy->SetEnemyWalkState(eEnemyWalkState::GENERALLY);
			}
				
			//モデルを移動させる
			mpEnemy->GetBoxModel()->Move(mChaseVelocity);

			break;
		}
	}

	//当たり判定を更新する
	this->SetAABBCollider();
}

/*============================
State開始時の初期化処理
============================*/
void EStateWalk::Reset()
{

}

/*==========================
当たり判定のアクセサ
============================*/
AABB* EStateWalk::GetCollider()const
{
	return mpWalkCollider.get();
}

/*==============================================
追いかけ用移動速度保存変数の設定
==============================================*/
void EStateWalk::ChaseVelocitySet(DirectX::SimpleMath::Vector3 vel)
{
	mChaseVelocity.x = vel.x*ENEMY_MOVE_SPEED;
	mChaseVelocity.z = vel.z*ENEMY_MOVE_SPEED;
}

/*=====================
向きを変更する
引数：対象の座標
======================*/
void EStateWalk::RotEnemyForTarget(DirectX::SimpleMath::Vector3 targetpos)
{
	//中心点
	DirectX::SimpleMath::Vector3 nierPosition = targetpos;
	//中心点から今のいる位置のベクトル
	DirectX::SimpleMath::Vector3 toVec = nierPosition - mpEnemy->GetBoxModel()->GetPosition();

	//もし、対象が敵より奥にいる状態ならば敵は直進とする
	if (toVec.z <= 0)
	{
		mpEnemy->GetBoxModel()->SetRotationY(180.f);
		mpEnemy->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

		//プレイヤーを追いかけていたら解除する
		if (mpEnemy->GetPlayerChaseFlag())
		{
			mpEnemy->SetPlayerChaseFlag(false);
		}
	}
	else
	{
		//法線ベクトル
		DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;
		//なす角
		float angle = std::acosf(toVec.Dot(vel) / (toVec.Length() * vel.Length()));
		angle = DirectX::XMConvertToDegrees(angle) + ESTATE_MODEL_ANGLE_LEFT;
		//なす角をモデルの角度にする
		mpEnemy->GetBoxModel()->SetRotationY(angle);
	}	
}

/*============================
向きを初期化
============================*/
void EStateWalk::ResetEnemyAngle()
{
	//敵の今向いている向きに応じて処理を行う
	switch (mpEnemy->GetAngleEnemy())
	{
		case eAngleEnemy::STRAIGHT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_STRAIGHT);
			break;
		}
		case eAngleEnemy::LEFT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_LEFT);
			break;
		}
		case eAngleEnemy::RIGHT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_RIGHT);
			break;
		}
	}
}


/*============================
当たり判定を設定する:private
============================*/
void EStateWalk::SetAABBCollider()
{
	//代入用変数の宣言
	DirectX::SimpleMath::Vector3 min, max;

	//借り入れ用変数の宣言
	DirectX::SimpleMath::Vector3 pos, scale;

	//簡略化
	pos = mpEnemy->GetBoxModel()->GetPosition() + ESTATE_COLLIDER_POSITION;
	scale = ESTATE_COLLIDER_SCALE;
	

	//当たり判定の座標を算出
	min = pos - scale;
	max = pos + scale;

	//当たり判定を代入する
	mpWalkCollider->SetCollider(min,max);
}

/*===========================================================
範囲内に収める:private
引数：比較する値、最小値、最大値
返り値：修正後の値
=============================================================*/
float EStateWalk::Clamp(float const& num, float const& minNum, float const& maxNum)const
{
	if (num < minNum)
	{
		return minNum;
	}
	else if (num > maxNum)
	{
		return maxNum;
	}
	else
	{
		return num;
	}
}
