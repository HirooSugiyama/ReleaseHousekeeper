/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

//前方宣言
struct AABB;	//衝突判定用

class EStateAttack :public EnemyStateBase
{
private:

	//攻撃インターバル
	static const int ENEMY_ATTACK_INTERVAL;

	//敵の攻撃力
	static const int ENEMY_ATTACK_POWER;


	//当たり判定保存用変数
	AABB* mpAttackCollider;

	//保存用変数
	Enemy* mpEnemy;

	//計測変数
	int mCurrentNum;

	//攻撃中の壁番号
	int mAttackBlockIndexNum;

public:

	//コンストラクタ
	EStateAttack();

	//デストラクタ
	~EStateAttack()override;

	//初期化処理
	 void Initialize(Enemy * pEnemy)override;

	//更新処理
	 void Update()override;

	//State開始時の初期化処理
	 void Reset()override;

	 //当たり判定のアクセサ
	 AABB* GetCollider() { return mpAttackCollider; }

	 //外部から当たり判定情報を丸々もらう
	 void SetCollider(AABB* pAABB) { mpAttackCollider = pAABB; }


	 //攻撃するタイミング計測関数
	 bool AttackTiming();

	 //攻撃力を返す
	 int GetAttackPower() { return ENEMY_ATTACK_POWER; }

	 //攻撃中の壁番号を保存する
	 void SetAttackBlockNum(int i) { mAttackBlockIndexNum = i; }
	 int GetAttackBlockNum() { return mAttackBlockIndexNum; }
	 //攻撃中の壁番号を初期化する
	 void ResetAttackBlockNum() { mAttackBlockIndexNum = Utility::EXCEPTION_NUM; }


private:
	//当たり判定を設定する
	void SetAABBCollider()override {}
};