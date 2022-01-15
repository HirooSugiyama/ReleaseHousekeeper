/*
敵行動パターン
作成日：2021/11/04
*/

#include"pch.h"
#include "EStateBlinking.h"

//前方宣言
#include"Enemy.h"

#include"../ObjectModel/BoxModel.h"

//プレイヤー点滅インターバル
const int EStateBlinking::ENEMY_BLINKING_INTERVAL = 10;

/*============================
コンストラクタ
============================*/
EStateBlinking::EStateBlinking()
	:
	EnemyStateBase(),
	mpEnemy(nullptr)
{
	mpDamageTimer = std::make_unique<DamageTimer>();
}

/*============================
デストラクタ
============================*/
EStateBlinking::~EStateBlinking()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateBlinking::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;
}

/*===========================
更新処理
============================*/
void EStateBlinking::Update()
{
	//点滅処理を持ち主に送る
	bool flag = mpDamageTimer->RegularIntervalTimer(ENEMY_BLINKING_INTERVAL);
	mpEnemy->GetBoxModel()->SetDrawFlag(flag);

	//時間が来たら
	if (mpDamageTimer->Update())
	{
		mpEnemy->GetBoxModel()->SetDrawFlag(true);
		//時間が来たら立ち状態に戻す
		mpEnemy->ChangeStateWalk();
	}
}

/*============================
State開始時の初期化処理
============================*/
void EStateBlinking::Reset()
{

}