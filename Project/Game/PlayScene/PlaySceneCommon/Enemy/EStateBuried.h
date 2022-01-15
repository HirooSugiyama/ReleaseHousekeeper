/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateBuried :public EnemyStateBase
{
private:

	//影を拡大描画
	static const DirectX::SimpleMath::Vector2 ENEMY_SHADOW_SCLAE_UP;
	//影の高さを調節
	static const float ENEMY_SHADOW_SHIFT_POSITIONY;

	//保存用変数
	Enemy* mpEnemy;

public:

	//コンストラクタ
	EStateBuried();

	//デストラクタ
	~EStateBuried()override;

	//初期化処理
	 void Initialize(Enemy * pEnemy)override;

	//更新処理
	 void Update()override {};

	//State開始時の初期化処理
	 void Reset()override {};

	 //描画処理
	 void Draw()override;

	 //次の処理へ動かす関数
	 void ChangeNextState();


private:
	//当たり判定を設定する
	void SetAABBCollider()override {};
};