/*
敵クラス
*/

#include<pch.h>
#include "Enemy.h"

//前方宣言
#include"../../../Common/ObjectTexture.h"




//リソースの取得
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"






//定数

//モデルの拡大率
//見た目用
const DirectX::SimpleMath::Vector3 Enemy::ENEMY_SCALE(0.5f, 0.5f, 0.5f);

	//移動速度
const float Enemy::ENEMY_MOVE_SPEED = 0.01f;


//モデルに合わせて当たり判定用の拡大率を定める
//プレイヤーはZ方向とY方向に長いので当たり判定をZ方向とY方向に伸ばす
const float Enemy::ENEMY_COLLIDER_EXTEND_Y = 3.f;
const float Enemy::ENEMY_COLLIDER_EXTEND_Z = 4.f;


//モデル生成時ミスの修正
const float Enemy::ENMEY_MODELMISS_FIX_ROT = 180.f;

//モデル描画範囲指定
const float Enemy::ENEMY_MDEL_DROW_AREA = -70.f;



//ブロック番号例外数字
const int Enemy::ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM = -1;

//敵モデルを強制的に横に向ける(向き反転する際に使用)
const float Enemy::ENEMY_MODEL_FORCED_BESIDE = 270.f;


//敵のHP
const int Enemy::ENEMY_HP = 20;

//敵の最大反転回数
const int Enemy::ENEMY_REVERSE_MAX_NUM = 2;

//エフェクト表示座標
const DirectX::SimpleMath::Vector3 Enemy::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);


//ダメージ値の描画座標
const DirectX::SimpleMath::Vector3 Enemy::FLOATNUMBER_DISTANCE_POSITION(0.f, 4.5f, 0.f);

/*===================================
コンストラクタ
===================================*/
Enemy::Enemy()
	: 
	mpEnemyModel(),
	mEnemyUseFlag(false),
	mMovePhaseNumber(),
	mpEnemyMoveState(nullptr),
	mStateEnemy(eStateEnemy::WALK),
	mpRotation(nullptr),
	mpWalk(nullptr),
	mpKnockBack(nullptr),
	mpAppearance(nullptr),
	mpAttack(nullptr),
	mpBuried(nullptr),
	mEnemyModelAngle(eAngleEnemy::STRAIGHT),
	mEnemyDamage(0),
	mEffectFlag(false),
	mpEnemyShadow(nullptr),
	mReverseNum(0),
	mEffectAddressFlag(nullptr),
	mEnemyGroundObjectHitFlag(false),
	mBoomerangHitFlag(false),
	mSaveBulletNumber(Utility::EXCEPTION_NUM),
	mpFloatNumber(nullptr),
	mWalkState(eEnemyWalkState::GENERALLY),
	mSaveScarecrowNumber(Utility::EXCEPTION_NUM),
	mPlayerChaseFlag(false)
{
	mpEnemyModel = std::make_unique<BoxModel>();

	mpRotation = std::make_unique<EStateRotation>();
	mpWalk = std::make_unique<EStateWalk>();
	mpKnockBack = std::make_unique<EStateKnockBack>();
	mpAppearance = std::make_unique<EStateAppearance>();
	mpAttack = std::make_unique<EStateAttack>();
	mpBuried = std::make_unique<EStateBuried>();
	mpBlinking = std::make_unique<EStateBlinking>();

	mpEnemyShadow = std::make_unique<Shadow>();
	mpFloatNumber = std::make_unique<FloatNumber3D>();
}

/*===================================
デストラクタ
===================================*/
Enemy::~Enemy()
{
}

/*=================================
初期化
引数：初期座標,カメラのポインタ
===================================*/
void Enemy::Initialize(DirectX::SimpleMath::Vector3 const& pos, CameraBase* camera)
{
	//座標はモデル設定時保存

	//モデルを設定する
	this->SetEnemyModel(pos.y);

	//モデルを表示する
	mpEnemyModel->SetDrawFlag(true);

	mpEnemyModel->SetPosition(pos);
	mpEnemyModel->SetScale(ENEMY_SCALE);
	mpEnemyModel->SetRotationY(ENMEY_MODELMISS_FIX_ROT);	//モデル生成時ミスの修正

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpEnemyModel->ReturnHalfSize(ENEMY_SCALE);
	//モデルの形に合わせてサイズ調整
	halfsize.y *= ENEMY_COLLIDER_EXTEND_Y;
	halfsize.z *= ENEMY_COLLIDER_EXTEND_Z;

	//設定
	mpEnemyModel->SetAABBCollider(pos - halfsize, pos + halfsize);

	//使用中にする
	mEnemyUseFlag = true;


	//影の初期化処理
	mpEnemyShadow->WrapInitialize();
	//影の拡大率を決める
	mpEnemyShadow->SetScale(DirectX::SimpleMath::Vector2(ENEMY_SCALE.x, ENEMY_SCALE.z));	//XZ平面

	//それぞれの状態の初期化
	mpRotation->Initialize(this);
	mpWalk->Initialize(this);
	mpKnockBack->Initialize(this);
	mpAppearance->Initialize(this);
	mpAttack->Initialize(this);
	mpBuried->Initialize(this);
	mpBlinking->Initialize(this);


	//最初の状態は待機処理
	this->ChangeStateBuried();

	mpFloatNumber->Initialize(camera);
}

/*===================================
更新
===================================*/
void Enemy::Update()
{
	//使用中の時のみ通す
	if (mEnemyUseFlag) 
	{
		//Stateで管理された移動処理を行う
		mpEnemyMoveState->Update();

		/*当たり判定の更新*/
		//ここでは保存してないためモデルから呼び出す。
		DirectX::SimpleMath::Vector3 modelpos, modelscale;
		modelpos = mpEnemyModel->GetPosition();
		modelscale = mpEnemyModel->GetScale();
		//拡大率の半分の値を生成
		DirectX::SimpleMath::Vector3 halfsize = mpEnemyModel->ReturnHalfSize(modelscale);
		//設定
		mpEnemyModel->SetAABBCollider(modelpos - halfsize, modelpos + halfsize);


		//もし、壁に2回ぶつかったら(塞がれていることに気づいたら)
		if (mReverseNum == ENEMY_REVERSE_MAX_NUM&&!mEnemyGroundObjectHitFlag)
		{
			//初期化して
			mReverseNum = 0;

			//回転する方向を正面に設定する
			this->GetStateRotation()->SetChangeAfterAngle(eChangeAfterAngle::STRAIGHT);
		
			//状態を回転に切り替える
			this->ChangeStateRotation();
		}
	}

	if (mEffectAddressFlag!=nullptr&&*mEffectAddressFlag==false)
	{
		mEffectFlag = false;
	}

	mpFloatNumber->Update();
}

/*===================================
描画
===================================*/
void Enemy::Draw()
{
	if (!mEnemyUseFlag)
	{
		return;
	}

	//モデルが指定範囲に入っていたら描画する
	if (mpEnemyModel->GetPosition().z >= ENEMY_MDEL_DROW_AREA)
	{
		//影の描画
		mpEnemyShadow->Draw(mpEnemyModel->GetPosition());

		//モデルの描画
		mpEnemyModel->Draw();

		//State先の描画
		mpEnemyMoveState->Draw();
	}

	mpFloatNumber->Draw();
}

/*===================================
終了処理
===================================*/
void Enemy::Finalize()
{
	mpEnemyModel.reset();
}

/*==================================
自身を削除(ポインタなどは消滅しない)
===================================*/
void Enemy::SelfDestroy()
{
	//描画中であれば
	if (mpEnemyModel->GetDrawFlag())
	{
		mpEnemyModel->SetDrawFlag(false);

		//当たり判定を初期値に
		mpEnemyModel->SetAABBCollider
		(
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Vector3::Zero
		);

		//未使用状態にする
		mEnemyUseFlag = false;

	}
}

/*==================================
歩き状態の際の当たり判定のアクセサ
返り値：当たり判定
===================================*/
AABB* Enemy::GetWalkCollider()const
{
	return mpWalk.get()->GetCollider();
}

/*===================================
回転状態の際の当たり判定のアクセサ
返り値：当たり判定
===================================*/
AABB* Enemy::GetRotationCollider()const
{
	return mpRotation.get()->GetCollider();;
}

/*===================================
モデルを設定する:private
引数：敵の高さ
===================================*/
void Enemy::SetEnemyModel(float const& posy)
{
	posy;
	//リソースマネージャの準備
	//高さに合わせたモデルを設定する
	auto pRM = ResourceManager::GetInstance();
	
	//敵種に合わせたモデルを設定する
	auto model = pRM->GetCmoModel("Enemy2");

	//設定する
	mpEnemyModel->SetModel(model);
}


/*===================================
移動処理
===================================*/
void Enemy::Move()
{
	DirectX::SimpleMath::Vector3 vel;
	vel.z = ENEMY_MOVE_SPEED;

	mpEnemyModel->Move(vel);
}

/*=================================
ダメージを与える処理
引数：ダメージ値
返り値：撃破したかどうか(true：撃破)
===================================*/
bool Enemy::Damage(int const& damagenum)
{
	//ダメージを与える
	mEnemyDamage += damagenum;

	if (mEnemyDamage >= ENEMY_HP)
	{
		//未使用状態にする
		this->SelfDestroy();
		//エフェクトマネージャーの取得
		auto pEM = EffectManager::GetInstance();

		auto effect = pEM->GetEffect(eEffectType::DISAPPEAR);
		effect->SetPosition(mpEnemyModel->GetPosition() + EFFECT_SHIFT_POSITION);
		effect->SetSpriteFlag(true);
		effect->SetLoopFlag(false);
		return true;
	}
	return false;
}

/*=================================
エフェクトを作成する
引数；ダメージ値
===================================*/
void Enemy::CreateNumberEffect(int damageNum)
{
	mpFloatNumber->Create
	(
		damageNum,
		mpEnemyModel->GetPosition()+
		FLOATNUMBER_DISTANCE_POSITION
	);
}

/*=================================
エフェクトをリセットする
===================================*/
void Enemy::ResetNumberEffect()
{
	mpFloatNumber->Reset();
}
