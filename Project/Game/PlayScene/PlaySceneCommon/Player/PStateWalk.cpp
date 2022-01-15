/*
プレイヤーの状態分けステートパターン：移動状態
作成日：2021/06/15
*/
#include"pch.h"

#include "PStateWalk.h"

//返り値からの関数の取得で使用。
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"

//移動速度の取得に使用
#include"../ObjectMove.h"

//ここで定義する。
const float MoveSpeed::MOVE_VELOCITY_X = 0.18f;
const float MoveSpeed::MOVE_VELOCITY_Y = 0.18f;
const float MoveSpeed::MOVE_VELOCITY_Z = 0.18f;


//ブロックの範囲
const float PStateWalk::MAX_POSITION_X = 19.f;
const float PStateWalk::MAX_POSITION_Z = 11.f;
const float PStateWalk::MIN_POSITION_Z = -40.f;

//スプライトの数
const int PStateWalk::WALKPLAYER_SPRITE_NUM = 5;

//スプライトのサイクル(この時間周期でスプライトが回る)
const int PStateWalk::WALKPLAYER_SPRITE_CYCLE = 4;


//プレイヤーの移動量(X)
const float PStateWalk::PLAYER_MOVE_VELOCITY_X = MoveSpeed::MOVE_VELOCITY_X;
//プレイヤーの移動量(Y)					
const float PStateWalk::PLAYER_MOVE_VELOCITY_Y = MoveSpeed::MOVE_VELOCITY_Y;
//プレイヤーの移動量(Z)					 
const float PStateWalk::PLAYER_MOVE_VELOCITY_Z = MoveSpeed::MOVE_VELOCITY_Z;


//移動量の増加量
const float PStateWalk::PLAYER_MOVE_INCREASE_VELOCITY=0.005f;

//左
const int PStateWalk::PLAYER_CHARACTER_ANGLE_L = 90;
//右	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_R = -90;
//上	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_U = 0;
//下	
const int PStateWalk::PLAYER_CHARACTER_ANGLE_D = 180;
//左上
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LU = 45;
//右上
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RU = -PLAYER_CHARACTER_ANGLE_LU;
//左下
const int PStateWalk::PLAYER_CHARACTER_ANGLE_LD = 135;
//右下
const int PStateWalk::PLAYER_CHARACTER_ANGLE_RD = -PLAYER_CHARACTER_ANGLE_LD;




/*========================
コンストラクタ
=========================*/
PStateWalk::PStateWalk()
	:
	PlayerStateBase(),
	mpPlayer(nullptr),
	mpWalkSpriteModel(),
	mActualPlayerVelocityX(0.0f),
	mActualPlayerVelocityY(0.0f),
	mActualPlayerVelocityZ(0.0f),
	mpDestinationPlayerCollider(),
	mGroundObjectHitFlag(false),
	mBlockHitFlag(false)
{
	mpWalkSpriteModel = std::make_unique<ObjectSpriteModel>(WALKPLAYER_SPRITE_NUM);

	mpDestinationPlayerCollider = std::make_unique<AABB>();

	//モデル設定処理
	this->SetSpriteModel();
}

/*=========================
初期化処理
引数：プレイヤーのポインタ
=========================*/
void PStateWalk::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;

	//スプライトモデルの周期の指定
	mpWalkSpriteModel->SetConstTimer(WALKPLAYER_SPRITE_CYCLE);
}
/*=========================
更新処理
=========================*/
void PStateWalk::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::WALK)
	{
		mpPlayer->SetState(ePlayerState::WALK);
	}

	//スプライトのタイミングでモデルを差し替える処理
	this->ReplacementSpriteModel();
	//移動量増加処理
	this->ConstantAcceleration();

	//移動できるか判断する
	this->AllObjectHit();

}

/*=========================
描画処理
=========================*/
void PStateWalk::Draw()
{
	//スプライトモデルの情報設定
	this->SetSpriteModelPosition();


	mpWalkSpriteModel->Draw();
}

/*=====================================
移動ベクトルを算出を設定する
返り値：移動ベクトル
======================================*/
DirectX::SimpleMath::Vector3 PStateWalk::CalculationMoveVelocity()
{
	//返り値用変数の宣言
	DirectX::SimpleMath::Vector3 returnpos = DirectX::SimpleMath::Vector3::Zero;

	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward()|| pGamePad->MoveUp())	//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			returnpos.z = -mActualPlayerVelocityZ;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			returnpos.x = -mActualPlayerVelocityX;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			returnpos.z = mActualPlayerVelocityZ;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			returnpos.x = mActualPlayerVelocityX;
			side = true;
		}
	}

	//同時押しの処理(コントローラーは現実的に不可能なので処理は無し)
	//双方向への入力は移動量0とする。
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		returnpos.x = 0;
	}


	if(pKey->WalkForward() && pKey->WalkBack())
	{
		returnpos.z = 0;
	}

	//斜め方向の移動処理
	if (whith && side && returnpos.x != 0 || returnpos.z != 0)
	{

		//斜めに移動する際は縦横とは長さが異なる（少し長い）ので、それの追加の計算。
		//ベクトルの長さを取得
		float vl = sqrtf((returnpos.x * returnpos.x) + (returnpos.z * returnpos.z));

		//単位ベクトル（長さが１のベクトル）を計算
		returnpos.x /= vl;
		returnpos.z /= vl;

		//移動ベクトルを目的の大きさ（移動量）にスケーリング
		returnpos.x *= mActualPlayerVelocityX;
		returnpos.z *= mActualPlayerVelocityZ;
	}

	return returnpos;
}


/*==================================================================
移動後のプレイヤーの当たり判定を返す(移動はしない)
===================================================================*/
AABB* PStateWalk::GetDestinationPlayerCollider()
{
	////算出用当たり判定の宣言
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	
	//プレイヤーの座標を保存
	modelpos = mpPlayer->GetPlayerModel()->GetPosition();
	
	//プレイヤーの拡大率を保存
	modelscale = mpPlayer->GetPlayerModel()->GetScale();
	
	//現在のキー入力での移動量を算出用変数に追加
	modelpos += mpPlayer->GetStateWalk()->CalculationMoveVelocity();
	
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpPlayer->GetPlayerModel()->ReturnHalfSize(modelscale);
	halfsize.y *= mpPlayer->GetPlayerColliderExtendY();
	
	//入力をもとに次の当たり判定を算出
	mpDestinationPlayerCollider->SetCollider(modelpos - halfsize, modelpos + halfsize);

	//当たり判定を返す
	return mpDestinationPlayerCollider.get();
}






/*=====================================
モデルを設定する:private
======================================*/
void PStateWalk::SetSpriteModel()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();

	std::string addfilekey= "none";
	std::string filekey= "none";

	for (int i = 0; i < WALKPLAYER_SPRITE_NUM; i++)
	{
		//要素数をstring変換
		addfilekey =std::to_string(i);
		//キーの作成
		filekey = "Player" + addfilekey;
		//キーを元にモデル情報を取得
		auto model = pRM->GetCmoModel(filekey);
		mpWalkSpriteModel->SetSpriteModel(i, model);
	}
}

/*=====================================
State開始時の初期化処理:private
======================================*/
void PStateWalk::SetSpriteModelPosition()
{
	//簡略化
	DirectX::SimpleMath::Vector3 pos= DirectX::SimpleMath::Vector3::Zero, scale= DirectX::SimpleMath::Vector3::Zero;
	pos = mpPlayer->GetPlayerModel()->GetPosition();
	scale = mpPlayer->GetPlayerModel()->GetScale();


	mpWalkSpriteModel->SetPosition(pos);
	mpWalkSpriteModel->SetScale(scale);
	
	//※当たり判定は通常モデルの方で処理
}

/*==================================================================
スプライトのタイミングでモデルを差し替える処理:private
===================================================================*/
void PStateWalk::ReplacementSpriteModel()
{
	mpWalkSpriteModel->SpriteUpdate();
}

/*=====================================
移動量を加速度的に増加させる:private
=======================================*/
void PStateWalk::ConstantAcceleration()
{
	//もし加速度が最大値ではなかったら、加速度を少し増やす。
	/*X*/
	if (mActualPlayerVelocityX < PLAYER_MOVE_VELOCITY_X)
	{
		mActualPlayerVelocityX += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	/*Y*/
	if (mActualPlayerVelocityY < PLAYER_MOVE_VELOCITY_Y)
	{
		mActualPlayerVelocityY += PLAYER_MOVE_INCREASE_VELOCITY;
	}
	/*Z*/
	if (mActualPlayerVelocityZ < PLAYER_MOVE_VELOCITY_Z)
	{
		mActualPlayerVelocityZ += PLAYER_MOVE_INCREASE_VELOCITY;
	}


}

/*===========================================================================
全てのオブジェクトに当たっていない場合のみ処理を通す関数:private
============================================================================*/
void PStateWalk::AllObjectHit()
{
	//どのオブジェクトとも当たっていなかったら
	if (mBlockHitFlag == false&&
		mGroundObjectHitFlag == false)
	{
		//移動処理
		this->Move();

		//当たり判定を更新する
		mpPlayer->UpdateCollider();
	}
}

/*=====================================
移動処理:private
======================================*/
void PStateWalk::Move()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	DirectX::SimpleMath::Vector3 vel;
	int rot = -1;//Modelの傾き

	bool side = false;
	bool whith = false;

	if (pKey->WalkForward() || pGamePad->MoveUp())	//キー入力が行われたら
	{		
		if (mpPlayer->GetPlayerModel()->GetPosition().z >= MIN_POSITION_Z)
		{
			vel.z = -mActualPlayerVelocityZ;
			rot = PLAYER_CHARACTER_ANGLE_U;
			whith = true;
		}
	}
	if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x >= -MAX_POSITION_X)
		{
			vel.x = -mActualPlayerVelocityX;
			rot = PLAYER_CHARACTER_ANGLE_L;
			side = true;
		}
	}
	if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().z < MAX_POSITION_Z)
		{
			vel.z = mActualPlayerVelocityZ;
			rot = PLAYER_CHARACTER_ANGLE_D;
			whith = true;
		}
	}
	if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
	{
		if (mpPlayer->GetPlayerModel()->GetPosition().x <= MAX_POSITION_X)
		{
			vel.x = mActualPlayerVelocityX;
			rot = PLAYER_CHARACTER_ANGLE_R;
			side = true;
		}
	}

	//同時押しの処理(コントローラーは現実的に不可能なので処理は無し)
	//双方向への入力は移動量0とする。
	if (pKey->WalkRight() && pKey->WalkLeft())
	{
		vel.x = 0;
	}


	if (pKey->WalkForward() && pKey->WalkBack())
	{
		vel.z = 0;
	}


	//斜め方向の移動処理
	if (whith && side && vel.x != 0 || vel.z != 0)
	{

		//斜めに移動する際は縦横とは長さが異なる（少し長い）ので、それの追加の計算。
		//ベクトルの長さを取得
		float vl = sqrtf((vel.x * vel.x) + (vel.z * vel.z));

		//単位ベクトルを計算
		vel.x /= vl;
		vel.z /= vl;

		//移動ベクトルを目的の大きさ（移動量）にスケーリング
		vel.x *= mActualPlayerVelocityX;
		vel.z *= mActualPlayerVelocityZ;

		if (pKey->WalkForward() || pGamePad->MoveUp())	//キー入力が行われたら
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_LU;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_RU;
			}
		}
		if (pKey->WalkBack() || pGamePad->MoveDown())//キー入力が行われたら
		{
			if (pKey->WalkLeft() || pGamePad->MoveLeft()) //キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_LD;
			}
			if (pKey->WalkRight() || pGamePad->MoveRight())//キー入力が行われたら
			{
				rot = PLAYER_CHARACTER_ANGLE_RD;
			}
		}
	}

	//X方向もしくはY方向に入力があったら
	if (vel.x != 0 || vel.z != 0) {
		mpPlayer->GetPlayerModel()->Move(vel);								//モデルを移動させる。
		mpPlayer->GetPlayerModel()->SetRotationY(static_cast<float>(rot));	//傾きを変更させる

		mpWalkSpriteModel->SetRotationY(static_cast<float>(rot));
		//degreeには関数内で変換
	}

	//一切処理がなかったら立ち状態へ移行
	if (vel == DirectX::SimpleMath::Vector3::Zero) {
		mpPlayer->ChangeStateStand();

		//加速度をすべて初期化する
		this->AllActualPlayerVelocityInit();
	}
}

/*=====================================
使用する加速度をすべて初期化:private
======================================*/
void PStateWalk::AllActualPlayerVelocityInit()
{
	mActualPlayerVelocityX=0.f;
	mActualPlayerVelocityY=0.f;
	mActualPlayerVelocityZ=0.f;
}
