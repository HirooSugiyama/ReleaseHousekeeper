/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateRotation :public EnemyStateBase
{
private:


	//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//回転スピード
	static const float ESTATE_ROT_SPEED;

	//直角
	static const float RIGHT_ANGLE;


	//敵の現在の向きを表す
	static const int ESTATE_ENEMY_ROT_STRAIGHT;
	static const int ESTATE_ENEMY_ROT_LEFT;
	static const int ESTATE_ENEMY_ROT_RIGHT;

	//座標のずらす幅
	static const int ESTATE_ENEMY_SHIFT_POSITION_RANGE;

	//当たり判定
	std::unique_ptr<AABB> mpRotationCollider;


	//保存用変数
	Enemy* mpEnemy;


	//現在の回転角
	float mSaveRotation;


	//回転させたい向きを保存する変数
	eChangeAfterAngle mChangeAfterAngle;


public:
	//コンストラクタ
	EStateRotation();

	//デストラクタ
	~EStateRotation()override;

	//初期化処理
	void Initialize(Enemy* pEnemy)override;

	//更新処理
	void Update()override;

	//State開始時の初期化処理
	void Reset()override;

	//当たり判定のアクセサ
	AABB* GetCollider()const;	//ヘッダーファイルの都合上CPPで処理を行う



	//回転させたい方向を保存する
	void SetChangeAfterAngle(eChangeAfterAngle const& angle) { mChangeAfterAngle = angle; }

	//モデルの向きを反転させる
	void ReverseRotEnemyModel();


private:


	//90度回転させる
	bool RotationRightAngle();

	//今の敵の向きを算出する
	void CalculationEnemyAngle();

	//当たり判定を設定する
	void SetAABBCollider()override;
};