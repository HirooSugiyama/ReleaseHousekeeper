/*
敵行動パターン
作成日：2021/08/31
*/


#include"pch.h"
#include "EStateKnockBack.h"

//前方宣言
#include"Enemy.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"


//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
const DirectX::SimpleMath::Vector3 EStateKnockBack::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EStateKnockBack::ESTATE_COLLIDER_SCALE(0.525f, 0.125f, 0.125f);

//移動速度
const float EStateKnockBack::ENEMY_MOVE_SPEED = 0.5f;

//速度減少率
const float EStateKnockBack::ENEMY_MOVE_SPEED_DECREASE = 0.7f;

//速度最小値
const float EStateKnockBack::ENEMY_MIN_VELOCITY = 0.0001f;

//移動ベクトルを小さくする
const float EStateKnockBack::ENEMY_MOVE_VELOCITY_SMALL = 0.5f;

//移動ベクトルを反転させる
const float EStateKnockBack::ENEMY_MOVE_VELOCITY_REVERSE = -1.f;

/*============================
コンストラクタ
============================*/
EStateKnockBack::EStateKnockBack()
	:
	EnemyStateBase(),
	mpKnockBackCollider(nullptr),
	mpEnemy(nullptr),
	mMoveVec()
{
	mpKnockBackCollider = std::make_unique<AABB>();
}

/*============================
デストラクタ
============================*/
EStateKnockBack::~EStateKnockBack()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateKnockBack::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;
}

/*============================
更新処理
============================*/
void EStateKnockBack::Update()
{
	//変換用変数の宣言
	DirectX::SimpleMath::Vector3 vel;

	vel -= mMoveVec;

	//速度を減少させる
	mMoveVec *= ENEMY_MOVE_SPEED_DECREASE;

	//モデルを移動させる
	mpEnemy->GetBoxModel()->Move(vel);

	//当たり判定を更新する
	this->SetAABBCollider();


	//もし速度が0に近づいたら
	if (this->Vector3Max(mMoveVec) <= ENEMY_MIN_VELOCITY)
	{
		//このStateをリセットして
		this->Reset();

		//歩き状態へ
		mpEnemy->ChangeStateBlinking();
	}
}

/*==========================
State開始時の初期化処理
============================*/
void EStateKnockBack::Reset()
{
	//速度の初期化
	mMoveVec = DirectX::SimpleMath::Vector3::Zero;
}

/*============================
当たり判定のアクセサ
============================*/
AABB* EStateKnockBack::GetCollider()
{
	return mpKnockBackCollider.get();
}

/*=======================
移動ベクトル保存用変数
引数：移動ベクトル
=========================*/
void EStateKnockBack::SetMoveVector(DirectX::SimpleMath::Vector3 movevec)
{
	mMoveVec = movevec;
	mMoveVec.Normalize();
	mMoveVec *= ENEMY_MOVE_VELOCITY_REVERSE;
	mMoveVec *= ENEMY_MOVE_VELOCITY_SMALL;
}

/*============================
当たり判定を設定する:private
============================*/
void EStateKnockBack::SetAABBCollider()
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
	mpKnockBackCollider->SetCollider(min, max);
}

/*====================================================
Vector3のうちの最も大きい値を返す関数:private
引数：Vector3型の値
返り値：引数内の最大値
====================================================*/
float EStateKnockBack::Vector3Max(DirectX::SimpleMath::Vector3 num)
{
	//初期値としてXの値を入れる
	float returnnum = std::fabs(num.x);

	//Yのほうが大きければ
	if (returnnum < std::fabs(num.y))
	{
		//Yを入れる
		returnnum = num.y;
	}
	//Zのほうが大きければ
	if (returnnum < std::fabs(num.z))
	{
		//Zを入れる
		returnnum = num.z;
	}

	//最大値を返す
	return returnnum;
}
