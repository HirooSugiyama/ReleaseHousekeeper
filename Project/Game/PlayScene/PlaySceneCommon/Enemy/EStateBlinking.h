/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"
#include"../DamageTimer.h"

class EStateBlinking :public EnemyStateBase
{
private:
	//敵点滅インターバル
	static const int ENEMY_BLINKING_INTERVAL;

	//保存用変数
	Enemy* mpEnemy;

	std::unique_ptr<DamageTimer> mpDamageTimer;

public:
	//コンストラクタ
	EStateBlinking();

	//デストラクタ
	~EStateBlinking()override;

	//初期化処理
	 void Initialize(Enemy * pEnemy)override;

	//更新処理
	 void Update()override;

	//State開始時の初期化処理
	 void Reset()override;

private:
	//当たり判定を設定する
	void SetAABBCollider()override {}
};