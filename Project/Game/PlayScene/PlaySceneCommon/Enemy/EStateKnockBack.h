/*
敵行動パターン
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateKnockBack :public EnemyStateBase
{
private:


	//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//拡大率(当たり判定)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;


	//移動速度
	static const float ENEMY_MOVE_SPEED;

	//速度減少率
	static const float ENEMY_MOVE_SPEED_DECREASE;

	//速度最小値
	static const float ENEMY_MIN_VELOCITY;

	//移動ベクトルを小さくする
	static const float ENEMY_MOVE_VELOCITY_SMALL;

	//移動ベクトルを反転させる
	static const float ENEMY_MOVE_VELOCITY_REVERSE;



	//当たり判定
	std::unique_ptr<AABB> mpKnockBackCollider;


	//保存用変数
	Enemy* mpEnemy;

	//移動ベクトル保存用変数
	DirectX::SimpleMath::Vector3 mMoveVec;

public:
	//コンストラクタ
	EStateKnockBack();

	//デストラクタ
	~EStateKnockBack()override;

	//初期化処理
	void Initialize(Enemy* pEnemy)override;

	//更新処理
	void Update()override;

	//State開始時の初期化処理
	void Reset()override;


	//当たり判定のアクセサ
	AABB* GetCollider();	//ヘッダーファイルの都合上CPPで処理を行う

	//移動ベクトルの取得
	void SetMoveVector(DirectX::SimpleMath::Vector3 movevec);

	//ノックバックの速度を0にする
	void NoneKnockBackSpeed(){}


private:
	//当たり判定を設定する
	void SetAABBCollider()override;

	//Vector3のうちの絶対値が最も大きい値を返す関数
	float Vector3Max(DirectX::SimpleMath::Vector3 num);

};