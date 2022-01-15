/*
敵行動パターン
作成日：2021/08/31
*/


#include"pch.h"
#include "EStateAttack.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"

//攻撃インターバル
const int EStateAttack::ENEMY_ATTACK_INTERVAL = 60;

//敵の攻撃力
const int EStateAttack::ENEMY_ATTACK_POWER = 1;


/*============================
コンストラクタ
============================*/
EStateAttack::EStateAttack()
	:
	EnemyStateBase(),
	mpAttackCollider(nullptr),
	mpEnemy(nullptr),
	mCurrentNum(0),
	mAttackBlockIndexNum(Utility::EXCEPTION_NUM)
{
}

/*============================
デストラクタ
============================*/
EStateAttack::~EStateAttack()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateAttack::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;
}

/*============================
更新処理
============================*/
void EStateAttack::Update()
{
	mCurrentNum++;
}

/*============================
State開始時の初期化処理
============================*/
void EStateAttack::Reset()
{

}

/*=============================================
攻撃するタイミング計測関数
返り値：攻撃するか否か(true：攻撃する)
=============================================*/
bool EStateAttack::AttackTiming()
{

	//攻撃するタイミングが来たら
	if (mCurrentNum >= ENEMY_ATTACK_INTERVAL)
	{
		//値を初期化して
		mCurrentNum = 0;

		return true;
	}

	return false;
}
