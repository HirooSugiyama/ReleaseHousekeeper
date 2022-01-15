/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateWalk :public EnemyStateBase
{
private:

	//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//移動速度
	static const float ENEMY_MOVE_SPEED;

	//モデル角度
	static const float ESTATE_MODEL_ANGLE_STRAIGHT;
	static const float ESTATE_MODEL_ANGLE_RIGHT;
	static const float ESTATE_MODEL_ANGLE_LEFT;

	//当たり判定
	std::unique_ptr<AABB> mpWalkCollider;

	//保存用変数
	Enemy* mpEnemy;

	//追いかけ用移動速度保存変数
	DirectX::SimpleMath::Vector3 mChaseVelocity;


public:
	//コンストラクタ
	EStateWalk();

	//デストラクタ
	~EStateWalk()override;

	//初期化処理
	 void Initialize(Enemy * pEnemy)override;

	//更新処理
	 void Update()override;

	//State開始時の初期化処理
	 void Reset()override;


	 //当たり判定のアクセサ
	 AABB* GetCollider()const;	//ヘッダーファイルの都合上CPPで処理を行う

	//追いかけ用移動速度保存変数の設定
	 void ChaseVelocitySet(DirectX::SimpleMath::Vector3 vel);
	 void ResetChaseVelocity() { mChaseVelocity = DirectX::SimpleMath::Vector3::Zero; }

	 //向きを変更する
	 void RotEnemyForTarget(DirectX::SimpleMath::Vector3 targetpos);
	 //向きを初期化
	 void ResetEnemyAngle();

private:
	//当たり判定を設定する
	void SetAABBCollider()override;

	//範囲内に収める
	float Clamp(float const& num, float const& minNum, float const& maxNum)const;

};