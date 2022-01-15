/*
敵行動パターン
作成日：2021/08/31
*/

#include"pch.h"
#include"EStateRotation.h"

//前方宣言
#include"Enemy.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"
#include"EStateAttack.h"
#include"EStateWalk.h"


//敵モデル座標からの当たり判定の差の距離(当たり判定の座標)
const DirectX::SimpleMath::Vector3 EStateRotation::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//拡大率(当たり判定)
const DirectX::SimpleMath::Vector3 EStateRotation::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//回転スピード
const float EStateRotation::ESTATE_ROT_SPEED = 1.5f;


//敵の現在の向きを表す
const int EStateRotation::ESTATE_ENEMY_ROT_STRAIGHT = 180;
const int EStateRotation::ESTATE_ENEMY_ROT_LEFT = 90;
const int EStateRotation::ESTATE_ENEMY_ROT_RIGHT = 270;


//直角
const float EStateRotation::RIGHT_ANGLE = 90.f;

//座標のずらす幅
const int EStateRotation::ESTATE_ENEMY_SHIFT_POSITION_RANGE = 1;

/*============================
コンストラクタ
============================*/
EStateRotation::EStateRotation()
	:
	EnemyStateBase(),
	mpRotationCollider(nullptr),
	mpEnemy(nullptr),
	mSaveRotation(),
	mChangeAfterAngle(eChangeAfterAngle::NONE)
{
	mpRotationCollider = std::make_unique<AABB>();
}

/*============================
デストラクタ
============================*/
EStateRotation::~EStateRotation()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateRotation::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;
}


/*============================
State開始時の初期化処理
============================*/
void EStateRotation::Reset()
{
}

/*============================
当たり判定のアクセサ
============================*/
AABB* EStateRotation::GetCollider()const
{
	return mpRotationCollider.get();
}

/*===================================
モデルを反転させる:private
====================================*/
void EStateRotation::ReverseRotEnemyModel()
{
	//現在のモデルの向きを取得
	this->CalculationEnemyAngle();

	//現在の敵のモデルの向きに応じて処理を変更する
	switch (mpEnemy->GetAngleEnemy())
	{
		//万が一直進する敵がいたら
		case eAngleEnemy::STRAIGHT:
		{
			//何もしない
			break;
		}
		//もともとの向きが左向きなら
		case eAngleEnemy::LEFT:
		{
			//右向きにする
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_RIGHT);
			break;
		}
		//もともとの向きが右向きなら
		case eAngleEnemy::RIGHT:
		{
			//左向きにする
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_LEFT);
			break;
		}
	}

	//改めて現在のモデルの向きを取得
	this->CalculationEnemyAngle();
}

/*===================================
90度回転させる:private
====================================*/
bool EStateRotation::RotationRightAngle()
{
	//直角になっていなかったら
	if (mSaveRotation < RIGHT_ANGLE)
	{
		//測定用変数を設定する
		mSaveRotation += ESTATE_ROT_SPEED;		
	}
	//直角になったら
	else
	{
		//初期値に戻す
		mSaveRotation = 0;

		return true;
	}
	return false;
}

/*====================================
更新処理:private
====================================*/
void EStateRotation::Update()
{
	//変更したい向きに応じて処理を通す
	switch (mChangeAfterAngle)
	{
		//例外
		case eChangeAfterAngle::NONE:
		{
			mpEnemy->ChangeStateWalk();
			break;
		}
		//左に回転させたい場合
		case eChangeAfterAngle::LEFT_ROTATION:
		{
			//回転角度管理用変数を更新させる
			bool flag=this->RotationRightAngle();
			//まだ回転中なら
			if (!flag)
			{
				//簡略化変数の宣言
				float rot = mpEnemy->GetBoxModel()->GetRotAngleY();

				//モデル角度を変更する
				mpEnemy->GetBoxModel()->SetRotationY(rot + ESTATE_ROT_SPEED);

				mpEnemy->SetAngleEnemy(eAngleEnemy::LEFT);
			}
			//指定の角度回転し終わったら
			else
			{
				//向きを算出
				this->CalculationEnemyAngle();


				//歩き状態とする
				mpEnemy->ChangeStateWalk();
			}

			break;
		}
		//右に回転させたい場合
		case eChangeAfterAngle::RIGHT_ROTATION:
		{
			//回転角度管理用変数を更新させる
			bool flag=this->RotationRightAngle();
			//まだ回転中なら
			if (!flag)
			{
				//簡略化変数の宣言
				float rot = mpEnemy->GetBoxModel()->GetRotAngleY();

				//モデル角度を変更する
				mpEnemy->GetBoxModel()->SetRotationY(rot - ESTATE_ROT_SPEED);

				mpEnemy->SetAngleEnemy(eAngleEnemy::RIGHT);
			}
			//指定の角度回転し終わったら
			else
			{
				//向きを算出
				this->CalculationEnemyAngle();

				//歩き状態とする
				mpEnemy->ChangeStateWalk();
			}
			break;
		}
		//正面に向けたい場合
		case eChangeAfterAngle::STRAIGHT:
		{
			//モデル角度を変更する(正面に向ける)
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_STRAIGHT);

			//状態を攻撃状態にする
			mpEnemy->ChangeStateAttack();

			//当たり判定を設定する
			mpEnemy->GetStateAttack()->SetCollider(mpRotationCollider.get());

			break;
		}
	}
	//当たり判定を更新する
	this->SetAABBCollider();
}


/*====================================
今の敵の向きを算出する:private
====================================*/
void EStateRotation::CalculationEnemyAngle()
{
	//現在のモデルの向きを取得
	int rot = static_cast<int>(mpEnemy->GetBoxModel()->GetRotAngleY());	//比べる先がintなのであらかじめ変換

	switch (rot)
	{
		case ESTATE_ENEMY_ROT_STRAIGHT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::STRAIGHT);
			break;
		}
		case ESTATE_ENEMY_ROT_LEFT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::LEFT);
			break;
		}
		case ESTATE_ENEMY_ROT_RIGHT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::RIGHT);
			break;
		}
	}
}

/*============================
当たり判定を設定する:private
============================*/
void EStateRotation::SetAABBCollider()
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
	mpRotationCollider->SetCollider(min, max);
}