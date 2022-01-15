/*
敵行動パターンの基底クラス
作成日：2021/08/31
*/
#pragma once



//列挙型の使用
#include"StateEnemy.h"
#include"AngleEnemy.h"


class Enemy;
class EnemyStateBase
{
protected:
	//コンストラクタ
	EnemyStateBase() = default;

	//デストラクタ
	virtual ~EnemyStateBase() = default;

public:
	//初期化処理
	virtual void Initialize(Enemy* pEnemy) = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw() {}

	//State開始時の初期化処理
	virtual void Reset() = 0;


protected:
	//当たり判定を設定する
	virtual void SetAABBCollider() = 0;

};
