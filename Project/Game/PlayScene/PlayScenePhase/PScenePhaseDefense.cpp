/*
防衛フェーズ
作成日：2021/06/16
*/

#include"pch.h"
#include "PScenePhaseDefense.h"

//所持元
#include"../PlayScene.h"



//情報共有で使用
#include"Game/Interface/SceneInterface/PtoRSceneInterface.h"

//エフェクトの描画で使用
#include"../Effect/EffectManager.h"

//関数の使用
#include"../PlaySceneCommon/Player/Player.h"
#include "../PlaySceneCommon/Player/PlayerActionState.h"
#include"../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/Player/ActionStateBase.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/Score.h"
#include"../PlaySceneCommon/Block/BlockManager.h"
#include"../PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"../PlaySceneCommon/Wall/WallManager.h"
#include"../PlaySceneCommon/GridLine/GridLineManager.h"
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../PlaySceneCommon/Player/ActionStateAttackEnemy.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"
#include"../PlayScenePhase/PScenePhaseEndAnimation.h"
#include"../PlaySceneCommon/Player/ActionStateDefenseHouse.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"
#include"../../UI/UI.h"

#include"Libraries/MyLibraries/CameraBase.h"

//サウンド関係
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"





//カメラ座標
const DirectX::SimpleMath::Vector3 PScenePhaseDefense::PIXED_CAMERA_POSITION(0.0f, 55.0f, 1.0f);

/*=====================
コンストラクタ
=====================*/
PScenePhaseDefense::PScenePhaseDefense()
	:
	PlayScenePhaseBase(),
	mpPlayScene(nullptr),
	mpDangerousLine(nullptr),
	mpSampleBlock(nullptr),
	mRedAssertFlag(false),
	mPhaseCount(1),
	mAllPhaseNum(0),
	mShopOpenFlag(false),
	mDefenseState(eDefenseState::MOVE),
	mMoveCameraSavePosition(DirectX::SimpleMath::Vector3::Zero),
	mWipeFlag(false)
{
	mpDangerousLine = std::make_unique<DangerousLine>();
	mpSampleBlock = std::make_unique<PreparingBlock>();
}

/*=====================
デストラクタ
=====================*/
PScenePhaseDefense::~PScenePhaseDefense()
{
}

/*=============================
初期化処理
引数：プレイシーンのポインタ
===============================*/
void PScenePhaseDefense::Initialize(PlayScene* pPlayScene)
{
	//ポインタの保存
	mpPlayScene = pPlayScene;

	//警告ラインの初期化処理
	mpDangerousLine->Initialize();
	//見本ブロックの初期化処理
	mpSampleBlock->Initialize();

	//ポインタの都合上こちらで初期化
	PlayScenePhaseBase::GetPlayer()->Initialize
	(
		PlayScenePhaseBase::GetBlockManager(),
		PlayScenePhaseBase::GetAdministrator(),
		mpSampleBlock.get(),
		PlayScenePhaseBase::GetUI()
	);

	//ポインタの保存
	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetWeaponManagerPointer(PlayScenePhaseBase::GetWeaponManager());

	PlayScenePhaseBase::GetPlayer()->GetAttackEnemy()->
		SetBulletManagerPointer(PlayScenePhaseBase::GetBulletManager());

	mAllPhaseNum = mpPlayScene->GetMaxPhaseNum();
}

/*=====================
更新処理
=====================*/
void PScenePhaseDefense::Update()
{
	//カメラ情報を保存
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//オブジェクトの更新処理
	this->ObjectUpdate();

	//赤色点滅エフェクトをつけるかどうか
	this->RedAssertSet();

	//カメラ切り替え処理
	this->ChangeCamera();

	//パドルの情報を摘出
	DirectX::SimpleMath::Vector3 playerpos
		= PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition();

	//カメラの更新
	mpPlayScene->GetCameraPointer()->Update(playerpos);

	//フェーズ更新処理
	this->PhaseToUpdate();

	//カメラの位置を保存する
	DirectX::SimpleMath::Vector3 cameraPosition(DirectX::SimpleMath::Vector3::Zero);
	cameraPosition = mpPlayScene->GetCameraPointer()->GetEyePosition();
	pCiIF.SetCameraPosition(cameraPosition);


	//プレイヤーの攻撃判定処理
	//攻撃していなかったら通さない
	if (PlayScenePhaseBase::GetPlayer()->GetActionState() == ePlayerActionState::ATTACK_ENEMY)
	{
		PlayScenePhaseBase::GetEnemyManager()->
			ChackHitNormalAttackPlayerEnemy(PlayScenePhaseBase::GetPlayer());
	}	

	//当たり判定の処理
	this->ColliderUpdate();

}

/*============================
State変更前のリセット処理
=============================*/
void PScenePhaseDefense::Reset()
{
	//敵管理クラスのフェーズを更新する
	PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);
	//天球を変える
	PlayScenePhaseBase::GetAdministrator()->DirectAcceserCelestialSphere()->
		ChangeSphereModelNight();

	//カメラを変更
	mpPlayScene->ChangeMainCamera();

	//カメラ行列を取得
	CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();

	//定点カメラに変更する
	pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
	pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
}

/*==============================
描画処理
================================*/
void PScenePhaseDefense::Draw()
{
	//オブジェクトの描画処理
	this->ObjectDraw();

	/*ここより下にEffectの処理を書かないと表示されない！(描画順の関係)*/
	//UIの描画処理
	PlayScenePhaseBase::GetUI()->Draw();
	//プレイヤーの状態の描画
	PlayScenePhaseBase::GetPlayer()->GetActionStateBase()->Draw();

	//エフェクトの描画処理
	EffectManager* pEM = EffectManager::GetInstance();
	pEM->Draw();
	
}

/*====================================
オブジェクトの更新処理:private
====================================*/
void PScenePhaseDefense::ObjectUpdate()
{
	//プレイヤーの更新処理
	PlayScenePhaseBase::GetPlayer()->Update();

	//ブロックの更新処理
	PlayScenePhaseBase::GetBlockManager()->Update();

	//敵の更新処理
	PlayScenePhaseBase::GetEnemyManager()->Update();

	//弾管理クラスの初期化処理
	PlayScenePhaseBase::GetBulletManager()->Update();

	//もしプレイヤーがダメージを受けていたら処理を通さない
	//攻撃しているときも処理を通さない
	if (PlayScenePhaseBase::GetPlayer()->GetPlayerState() != ePlayerState::DAMAGE &&
		PlayScenePhaseBase::GetPlayer()->GetActionState() != ePlayerActionState::ATTACK_ENEMY) 
	{
		//見本ブロックの更新処理
		mpSampleBlock->Update
		(
			PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition(),
			PlayScenePhaseBase::GetGridLineManager()
		);
	}

	//管理者の更新処理
	PlayScenePhaseBase::GetAdministrator()->Update();

	//UIに情報を渡す
	int scoreNum = PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum();
	int nowNum = PlayScenePhaseBase::GetEnemyManager()->GetBreakEnemyNum();
	int maxNum = PlayScenePhaseBase::GetEnemyManager()->GetMaxEnemyNum();

	PlayScenePhaseBase::GetUI()->SetAllEnemyNum(maxNum);
	PlayScenePhaseBase::GetUI()->SetRemainingEnemyNum(nowNum);
	PlayScenePhaseBase::GetUI()->SetScoreNum(scoreNum);


}
/*====================================
当たり判定の処理:private
====================================*/
void PScenePhaseDefense::ColliderUpdate()
{
	//敵とプレイヤーの当たり判定計測
	PlayScenePhaseBase::GetEnemyManager()->
		ChackHitPlayerEnemy(PlayScenePhaseBase::GetPlayer());

	//拠点と敵の当たり判定計測
	PlayScenePhaseBase::GetEnemyManager()->
		ChackHitProtecterEnemy(PlayScenePhaseBase::GetProtecter());

	//ブロックと敵の当たり判定
	PlayScenePhaseBase::GetBlockManager()->
		RoolEnemyManagerChackHit();

	//地上オブジェクトと敵の当たり判定
	PlayScenePhaseBase::GetGroundObjectManager()->
		RoolEnemyManagerChackHit(PlayScenePhaseBase::GetEnemyManager());

	// ブロックと見本ブロックの当たり判定～ブロックの重なりを防ぐ～
	PlayScenePhaseBase::GetBlockManager()->
		ChackHitSampleBlockBlock(mpSampleBlock.get(), PlayScenePhaseBase::GetPlayer());

	//ブロックとプレイヤーの当たり判定
	PlayScenePhaseBase::GetBlockManager()->
		ChackhitPlayerBlock(PlayScenePhaseBase::GetPlayer());

	//柵と敵の当たり判定を回す
	PlayScenePhaseBase::GetWallManager()->
		RoolEnemyManagerChackHit(PlayScenePhaseBase::GetEnemyManager());

	//判定用ラインと見本ブロックの当たり判定
	PlayScenePhaseBase::GetGridLineManager()->
		ChackHitPreparingBlockGridLine(PlayScenePhaseBase::GetPlayer(), mpSampleBlock.get());

	//プレイヤーと地上オブジェクトの当たり判定
	PlayScenePhaseBase::GetGroundObjectManager()->
		ChackHitPlayerGroundObject(PlayScenePhaseBase::GetPlayer());


	//警告ラインと敵の当たり判定
	mRedAssertFlag = PlayScenePhaseBase::GetEnemyManager()->
		ChackHitDangerousLineEnemy(mpDangerousLine.get());

	//弾と敵の当たり判定
	PlayScenePhaseBase::GetEnemyManager()->
		RoolBulletManagerChackhit(PlayScenePhaseBase::GetBulletManager());

	//ブロックと弾の衝突判定
	PlayScenePhaseBase::GetBulletManager()->
		RoolChackHitBlock(PlayScenePhaseBase::GetBlockManager());

	//弾とプレイヤーの衝突判定
	PlayScenePhaseBase::GetBulletManager()->
		ChackHitBulletPlayer(PlayScenePhaseBase::GetPlayer());

	//プレイヤーと敵の距離判定
	PlayScenePhaseBase::GetEnemyManager()->
		ChackDistanceTargetEnemy(PlayScenePhaseBase::GetPlayer()->GetPlayerModel()->GetPosition(), true);
}

/*====================================
オブジェクトの描画処理:private
====================================*/
void PScenePhaseDefense::ObjectDraw()
{
	//警告ラインの描画処理
	mpDangerousLine->Draw();
}

/*===========================================
赤色点滅エフェクトをつけるかどうか:private
===========================================*/
void PScenePhaseDefense::RedAssertSet()
{
	//もしフラグが立っていたら
	if (mRedAssertFlag)
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(true);
	}
	//立っていなかったら
	else
	{
		PlayScenePhaseBase::GetUI()->RedAssertControl(false);
	}

}

/*===========================================
フェーズ更新処理:private
===========================================*/
void PScenePhaseDefense::PhaseToUpdate()
{
	//簡略化変数の宣言
	int nowtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMainTimer();
	int maxtime = PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->GetMaxTime();
	
	if (nowtime == maxtime)
	{
		//フェーズカウントが最大になったら
		if (mPhaseCount == mAllPhaseNum) 
		{
			//スコアの取得
 			PtoRSceneInterface& pPR = PtoRSceneInterface::GetPtoRIFInstance();
			pPR.SetScoreNum(PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum());
			mpPlayScene->GetEndAnimation()->SetUseAnim(eUseEndAnim::WIN_TIME);
			mpPlayScene->ChangePhaseToEndAnimation();
			mpPlayScene->GetPhase()->Reset();
		}

		//周期カウントを更新
		mPhaseCount++;
		//敵管理クラスのフェーズを更新する
		PlayScenePhaseBase::GetEnemyManager()->SetNowPhaseNum(mPhaseCount);

		//サウンド再生
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_ENEMYSPAWN);

		//タイマーをリセットする
		PlayScenePhaseBase::GetAdministrator()->DirectAcceserTimer()->ResetMainTimer();
	}


	//ショップへの移行処理
	if (PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == false)
	{


		//状態移行処理を行う
		mpPlayScene->ChangePhaseToWeaponShop();
		mpPlayScene->GetPhase()->Reset();

		//フラグを付ける
		mShopOpenFlag = true;
	}
	else if (!PlayScenePhaseBase::GetGroundObjectManager()->GetPlayerShopTouchFlag()&&
		mShopOpenFlag == true)
	{
		//フラグを降ろす
		mShopOpenFlag = false;
	}


	
}

/*===========================================
カメラ視点変更処理:private
===========================================*/
void PScenePhaseDefense::ChangeCamera()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (!pKey->ChangeCamera()|| !pGamePad->ChangeCamera())
	{
		return;
	}

	switch (mDefenseState)
	{
		//移動状態だった場合
		case eDefenseState::MOVE:
		{
			mDefenseState = eDefenseState::PIXED;
			mMoveCameraSavePosition = mpPlayScene->GetCameraPointer()->GetEyePosition();

			//定点カメラに変更する
			mpPlayScene->ChangeFixedCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(PIXED_CAMERA_POSITION);			//座標指定
			mpPlayScene->GetCameraPointer()->CalculationMatrix();

			//カメラ行列を取得
			CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();
			
			//定点カメラに変更する
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());
			break;
		}
		//定点カメラだった場合
		case eDefenseState::PIXED:
		{
			mDefenseState = eDefenseState::MOVE;
			//定点カメラに変更する
			mpPlayScene->ChangeMainCamera();
			mpPlayScene->GetCameraPointer()->SetEyePosition(mMoveCameraSavePosition);			//座標指定
			//カメラ行列を取得
			CameraInfoIF& pPVIf = CameraInfoIF::GetCameraInfoIFInstance();
			
			//定点カメラに変更する
			pPVIf.SetProjection(mpPlayScene->GetCameraPointer()->GetProjectionMatrix());
			pPVIf.SetView(mpPlayScene->GetCameraPointer()->GetViewMatrix());

			break;
		}
	}
}
