/*
敵管理クラス
*/

#include<pch.h>

#include "EnemyManager.h"


//前方宣言
#include"../../Effect/Effect.h"

//当たり判定
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"

//当たり判定の際に関数を使用
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"EStateKnockBack.h"
#include"../../PlaySceneDefence/DangerousLine.h"

//列挙型の使用
#include "EnemyStateBase.h"
#include"../Player/ActionStateAttackEnemy.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"

//関数の使用
#include"EStateWalk.h"
#include"EStateAppearance.h"
#include"EStateRotation.h"
#include"EStateAttack.h"
#include"EStateBuried.h"

#include"../Bullet/BulletManager.h"


//初期サイズ
const int EnemyManager::ENEMY_INIT_SIZE = 100;

//未使用の敵の出現座標
const DirectX::SimpleMath::Vector3 EnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//初期拡大率
const DirectX::SimpleMath::Vector3 EnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);


//敵の攻撃力
const int EnemyManager::ENEMY_ATTACK_NUM = 1;


//敵が乱数出向く向きの数
const int EnemyManager::ENEMY_RAND_ANGLE_NUM = 2;


//スコア値
const int EnemyManager::ENEMY_SCORE = 100;

//エフェクトの出現させる座標
const DirectX::SimpleMath::Vector3 EnemyManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

//敵のプレイヤー捕捉範囲
const float EnemyManager::ENEMY_CAPTURE_RANGE = 5.f;

/*===================================
コンストラクタ
===================================*/
EnemyManager::EnemyManager()
	:
	mpEnemy{},
	mEnemyAppearanceInterval(0),
	mpEnemyCall(nullptr),
	mpAdministrator(nullptr),
	mMaxEnemySpawnPositionZ(0),
	mLoadEnemyFileName("none"),
	mNowPhaseNum(0),
	mMaxPhaseNum(0),
	mEnemyBlockHitFlag{},
	mNowEnemyBreakNum()
{
	//サイズをメモリ確保用最大数に設定する
	mpEnemy.resize(ENEMY_INIT_SIZE);

	//呼び出しクラスを定義
	mpEnemyCall = std::make_unique<EnemyCall>();


	//敵のメモリ確保
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		mpEnemy[i] = std::make_unique<Enemy>();
	}

	//敵の数の分衝突フラグを作成する
	mEnemyBlockHitFlag.resize(static_cast<int>(mpEnemy.size()));

}

/*=================================
デストラクタ
===================================*/
EnemyManager::~EnemyManager()
{
}
/*=========================================================
初期化処理
引数：カメラへのポインタ、管理者クラスのポインタ
=========================================================*/
void EnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator)
{
	//敵の読み込み
	this->LoadFile(mLoadEnemyFileName, camera);

	//ポインタ保存
	mpAdministrator = pAdministrator;
}

/*===================================
更新処理
===================================*/
void EnemyManager::Update()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//使用中のみ
		if (mpEnemy[i]->GetEnemyUseFlag()) 
		{

			//指定されたフェーズ番号より小さい番号を持つの敵のみ処理を通す
			if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
			{
				//もし待機状態の敵がいたら
				if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)
				{
					//次の処理へ送る
					mpEnemy[i]->GetStateBuried()->ChangeNextState();
				}

				mpEnemy[i]->Update();
			}	
		}
	}
}

/*=================================
描画処理
===================================*/
void EnemyManager::Draw()
{

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		if (mpEnemy[i]->GetEnemyUseFlag()) 
		{
			//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
			if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
			{
				mpEnemy[i]->Draw();
			}		
		}
	}
	
}

/*=================================
終了処理
===================================*/
void EnemyManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		if (mpEnemy[i] != nullptr) 
		{
			mpEnemy[i]->Finalize();
		}	
	}
}

/*==================================================
敵の回数分だけ当たり判定を回す処理
引数：弾管理クラスのポインタ
====================================================*/
void EnemyManager::RoolBulletManagerChackhit(BulletManager* pBulletManager)
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用中ではないなら通さない。
		if (!mpEnemy[i]->GetEnemyUseFlag())continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//当たり判定の処理を通す
		int breaknum = pBulletManager->ChackHitBulletEnemy(mpEnemy[i].get());
		
		//撃破した数だけ増加させる
		mNowEnemyBreakNum += breaknum;

		//スコア増加
		mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE * breaknum);
	}
}


/*====================================================================================================
ブロックと敵の衝突判定関数
引数	：pBlock(使用するブロックのポインタ)
		：blockNum(ブロックの配列番号)
========================================================================================================*/
void EnemyManager::ChackHitBlocklEnemy(Block* pBlock, int const& blockNum)
{
	//簡略化用変数の宣言
	bool colliderFlag = false;
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用中ではないなら通さない。
		if (!(mpEnemy[i]->GetEnemyUseFlag())) continue;

		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;


		//攻撃状態の場合 
		if (mpEnemy[i]->GetStateEnemy()== eStateEnemy::ATTACK)
		{
			//攻撃用の当たり判定で衝突判定を取る
			colliderFlag = pC.Intersect(
				mpEnemy[i]->GetStateAttack()->GetCollider(),
				pBlock->GetBoxModel()->GetAABBCollider());

			//当たっていたら
			if (colliderFlag)
			{
				//壁番号が保存されてなかったら
				if (mpEnemy[i]->GetStateAttack()->GetAttackBlockNum() == Utility::EXCEPTION_NUM)
				{
					//番号を保存する
					mpEnemy[i]->GetStateAttack()->SetAttackBlockNum(blockNum);
				}

				//攻撃するタイミングではなかったら
				if (!mpEnemy[i]->GetStateAttack()->AttackTiming())continue;

				//ブロックにダメージを与える
				bool blockHP = pBlock->BlockDamage(mpEnemy[i]->GetStateAttack()->GetAttackPower());

				//エフェクトを設定する
				this->SetEnemyEffect(eEffectType::CLAW, pBlock->GetBoxModel()->GetPosition(), i);

				//もしブロックのHPがなかったら
				if (blockHP)
				{
					//ブロックを破壊する
					pBlock->SelfDestroy();

					//エフェクトの設定
					this->SetEnemyEffect(eEffectType::DESTROY,
						pBlock->GetBoxModel()->GetPosition(), i);


					int blockindex = mpEnemy[i]->GetStateAttack()->GetAttackBlockNum();

					//同じ壁番号を持つすべての敵に処理を行う
					for (int j = 0; j < static_cast<int>(mpEnemy.size()); j++)
					{
						if (mpEnemy[j]->GetStateEnemy() != eStateEnemy::ATTACK)continue;

						//使用中ではないなら通さない。
						if (!(mpEnemy[j]->GetEnemyUseFlag()))continue;


						//フェーズがまだ来てなければ処理を行わない
						//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
						if (mpEnemy[j]->GetMovePhaseNumber() > mNowPhaseNum ||
							mpEnemy[j]->GetMovePhaseNumber() == 0)continue;


						if (mpEnemy[j]->GetStateAttack()->GetAttackBlockNum() == blockindex)
						{
							//壁番号をリセットして
							mpEnemy[j]->GetStateAttack()->ResetAttackBlockNum();

							//向きを正面として
							mpEnemy[j]->SetAngleEnemy(eAngleEnemy::STRAIGHT);

							//動きを歩き状態とする
							mpEnemy[j]->ChangeStateWalk();
						}

					}
				}
			}
		}
		//攻撃状態以外の場合
		else
		{
			//敵行動Stateの当たり判定で衝突判定を取る
			colliderFlag = pC.Intersect(
				mpEnemy[i]->GetWalkCollider(), pBlock->GetBoxModel()->GetAABBCollider());

			//当たっていたら処理をする
			if (colliderFlag)
			{
				//敵が当たったフラグを設定する(全ての壁との衝突判定後、降ろす。)
				mEnemyBlockHitFlag[i] = true;

				//正面移動に切り替える
				mpEnemy[i]->GetStateWalk()->ResetChaseVelocity();
				mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

				//もし敵が横移動していなかったら
				if (mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::STRAIGHT)
				{
					//回転に切り替える
					mpEnemy[i]->ChangeStateRotation();
					//乱数でどっちを向くかを決める
					srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
					bool angleflag = static_cast<bool>(rand() % ENEMY_RAND_ANGLE_NUM);
					//横移動させる
					if (angleflag)
					{
						mpEnemy[i]->GetStateRotation()->SetChangeAfterAngle(eChangeAfterAngle::RIGHT_ROTATION);
					}
					else
					{
						mpEnemy[i]->GetStateRotation()->SetChangeAfterAngle(eChangeAfterAngle::LEFT_ROTATION);
					}
				}
			}
		}

		
	}
}

/*==================================================
敵の回転処理
====================================================*/
void EnemyManager::RotationEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		if (!mEnemyBlockHitFlag[i])						//このフレームでどのブロックにもぶつかっておらず
		{
			if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::WALK)				//歩き状態で
			{

				if (!mpEnemy[i]->GetEnemyGroundObjectHitFlag()&&			//地上オブジェクトに当たっておらず
					(mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::LEFT ||				//横移動している敵がいたら
					mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::RIGHT))
				{
					//現在のモデルの向きを取得
					eAngleEnemy rot = mpEnemy[i]->GetAngleEnemy();


					switch (rot)
					{
						case eAngleEnemy::STRAIGHT:
						{
							break;
						}
						//左を向いていたら
						case eAngleEnemy::LEFT:
						{
							//左回転させる
							mpEnemy[i]->GetStateRotation()->
								SetChangeAfterAngle(eChangeAfterAngle::LEFT_ROTATION);

							break;
						}
						//右を向いていたら
						case eAngleEnemy::RIGHT:
						{
							//右回転させる
							mpEnemy[i]->GetStateRotation()->
								SetChangeAfterAngle(eChangeAfterAngle::RIGHT_ROTATION);

							break;
						}
					}

					//回転に切り替える
					mpEnemy[i]->ChangeStateRotation();
				}
				//ひとつでも地上オブジェクトと当たっていたら
				else if(mpEnemy[i]->GetEnemyGroundObjectHitFlag())	
				{
					switch (mpEnemy[i]->GetAngleEnemy())
					{
						case eAngleEnemy::STRAIGHT:	//正面を向いていたら
						{
							//回転に切り替える
							mpEnemy[i]->ChangeStateRotation();
							//乱数でどっちを向くかを決める
							srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
							bool angleflag = static_cast<bool>(rand() % ENEMY_RAND_ANGLE_NUM);
							//横移動させる
							if (angleflag)
							{
								mpEnemy[i]->GetStateRotation()->
									SetChangeAfterAngle(eChangeAfterAngle::RIGHT_ROTATION);
							}
							else
							{
								mpEnemy[i]->GetStateRotation()->
									SetChangeAfterAngle(eChangeAfterAngle::LEFT_ROTATION);
							}
							break;
						}
						case eAngleEnemy::RIGHT:
						case eAngleEnemy::LEFT:
						{

							break;
						}


					}
				}
			}
		}
	}
}

/*==================================================
プレイヤーと敵の衝突判定関数
引数：プレイヤーのポインタ
====================================================*/
void EnemyManager::ChackHitPlayerEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BLINKING)continue;

		//プレイヤーがダメージ状態なら処理をしない
		if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) continue;


		//当たっていたら処理をする
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(), pPlayer->GetPlayerModel()->GetAABBCollider()))
		{
			//プレイヤーにダメージを与える
			pPlayer->ChangeStateDamage();
		}
	}
}

/*===================================================
プレイヤー攻撃時のプレイヤーと敵の衝突判定関数
引数：プレイヤーのポインタ
====================================================*/
void EnemyManager::ChackHitNormalAttackPlayerEnemy(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;


		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BLINKING||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::KNOCK_BACK)continue;



		//選択肢にnullが入る可能性があるためチェックする
		if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)break;

		//もしプレイヤーが弱攻撃状態でないならば通らない
		if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)continue;

		//もしエフェクト稼働中なら処理を通さない
		if (mpEnemy[i]->GetEffectFlag())continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpEnemy[i]->GetBoxModel()->GetAABBCollider()))
		{

			//現在の敵の状態をノックバック状態とする
			mpEnemy[i]->GetStateKnockBack()->Reset();//連続攻撃対応用		

			//弱攻撃のダメージを与える
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge=mpEnemy[i]->Damage(damageNum);

			//もし敵を倒していたら
			if (breakjuge)
			{
				//撃破数追加
				mNowEnemyBreakNum++;
				
				//スコアを増やして
				mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE);
			}
			//倒してなかったらダメージ値を表示する
			else
			{
				//エフェクトをリセットして
				mpEnemy[i]->ResetNumberEffect();

 				mpEnemy[i]->CreateNumberEffect(mpEnemy[i]->GetEnemyDamage());
			}
			
			//エフェクトを設定する
			this->SetEnemyEffect(eEffectType::SLASH, mpEnemy[i]->GetBoxModel()->GetPosition(),i,true);

			//ノックバックの方向を算出する
			DirectX::SimpleMath::Vector3 knockBackVelocity =
				pPlayer->GetAttackEnemy()->GetHand()->GetColliderPosition() - pPlayer->GetPlayerModel()->GetPosition();

			mpEnemy[i]->GetStateKnockBack()->SetMoveVector(knockBackVelocity);
			mpEnemy[i]->ChangeStateKnockBack();

			//追いかけ状態とする
			mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::CHASING);
			mpEnemy[i]->SetPlayerChaseFlag(true);
		}
	}
}

/*==================================================
拠点と敵の衝突判定関数
引数：拠点のポインタ
====================================================*/
void EnemyManager::ChackHitProtecterEnemy(Protecter* pProtecter)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//敵の数だけ処理を回す
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),
			pProtecter->GetProtecterModel()->GetAABBCollider()))
		{
			//敵を破壊する
			mpEnemy[i]->SelfDestroy();


			//家の耐久値を減らす
			pProtecter->SetDamageFlag(true);
		}
	}
}

/*======================================================================
地上オブジェクトと敵の当たり判定
引数：地上オブジェクト管理クラス内の当たり判定ひとつのポインタ
=======================================================================*/
void EnemyManager::ChackHitGroundObjectEnemy(AABB* pObjectCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum||
			mpEnemy[i]->GetMovePhaseNumber()==0)continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),	//敵の当たり判定
			pObjectCollider))								//地上オブジェクトの当たり判定
		{
			//もしノックバックを受けている状態ならば
			if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::KNOCK_BACK)
			{
				//歩き状態に戻して
				mpEnemy[i]->ChangeStateWalk();
			}
			//向きを反転させる
			mpEnemy[i]->GetStateRotation()->ReverseRotEnemyModel();
			//反転数を増やす
			mpEnemy[i]->SetReverseNumUp();

		}
	}
}

/*======================================================================
柵と敵の当たり判定
引数：柵の当たり判定ポインタ
=======================================================================*/
void EnemyManager::ChackHitWallEnemy(AABB* pWallCollider)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)
		{
			continue;
		}
		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)
		{
			continue;
		}

		//当たっていたら処理をする
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),	//敵の当たり判定
			pWallCollider))									//地上オブジェクトの当たり判定
		{
			//向きを反転させる
			mpEnemy[i]->GetStateRotation()->ReverseRotEnemyModel();
			
			//反転数を増やす
			mpEnemy[i]->SetReverseNumUp();
		}
	}
}

/*========================================
危険信号ラインと敵の当たり判定
引数：危険信号ラインのポインタ
=========================================*/
bool EnemyManager::ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine)
{
	//簡略化用変数の宣言
	float enemyPositionZ = 0.f, linePositionZ = 0.f;


	//発動判定用フラグの宣言
	bool effectMoveFlag = false;

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用中ではないなら通さない。
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//敵の現在の状態が出現状態ならば通さない
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;


		//フェーズがまだ来てなければ処理を行わない
		//指定されたフェーズ番号より小さい番号を持つの敵のみ描画する
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;


		//座標を設定する
		enemyPositionZ = mpEnemy[i]->GetBoxModel()->GetPosition().z;
		linePositionZ = pDangerousLine->GetLinePositionZ();

		//もし敵がラインより家側にいたらフラグを建てる
		if (enemyPositionZ > linePositionZ)
		{
			effectMoveFlag = true;
			//いる数は関係ないので抜ける
			break;
		}
	}

	return effectMoveFlag;
}

/*========================================
対象と敵の距離判定
引数：対象の座標
=========================================*/
void EnemyManager::ChackDistanceTargetEnemy(DirectX::SimpleMath::Vector3 const& pos, bool playerFlag)
{
	//算出用変数
	float distance(0);

	//向きベクトル保存用変数
	DirectX::SimpleMath::Vector3 distanceVelocity(DirectX::SimpleMath::Vector3::Zero);

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用していなければ処理を行わない
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//稼働状態でなければ処理を行わない
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//歩行状態でないなら処理を行わない
		if (mpEnemy[i]->GetStateEnemy() != eStateEnemy::WALK)continue;

		//正面を向いていなければ処理を行わない
		if (mpEnemy[i]->GetAngleEnemy() != eAngleEnemy::STRAIGHT)continue;

		//対象がプレイヤーでプレイヤーを追いかけていなかったら
		if (playerFlag && !mpEnemy[i]->GetPlayerChaseFlag())continue;


		//距離を計測する
		distance = std::sqrtf((std::abs(pos.x - mpEnemy[i]->GetBoxModel()->GetPosition().x)) * 2 +
						  (std::abs(pos.z - mpEnemy[i]->GetBoxModel()->GetPosition().z)) * 2);

		//一定距離間にいたら
		if (distance < ENEMY_CAPTURE_RANGE &&
			mpEnemy[i]->GetEnemyWalkState()== eEnemyWalkState::CHASING)
		{
			//距離を求める
			distanceVelocity = pos - mpEnemy[i]->GetBoxModel()->GetPosition();

			distanceVelocity.Normalize();		//正規化

			//敵の移動速度を設定する
			mpEnemy[i]->GetStateWalk()->ChaseVelocitySet(distanceVelocity);


			mpEnemy[i]->GetStateWalk()->RotEnemyForTarget(pos);

		}
		//一定距離におらず、追いかけ状態なら
		else if (mpEnemy[i]->GetEnemyWalkState() == eEnemyWalkState::CHASING)
		{
			//通常に戻す
			mpEnemy[i]->GetStateWalk()->ResetChaseVelocity();
			mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

			//プレイヤーを追いかけていたら解除する
			if (mpEnemy[i]->GetPlayerChaseFlag())
			{
				mpEnemy[i]->SetPlayerChaseFlag(false);
			}
		}
	}
}

/*========================================
リセット処理(ポインタは保持)
=========================================*/
void EnemyManager::Reset()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		if (mpEnemy[i] != nullptr)
		{
			mpEnemy[i]->SelfDestroy();
		}
	}
}

/*=================================
読み込むファイル名を作成
引数：ステージ番号
返り値：ファイル名
===================================*/
std::string EnemyManager::CreateLoadEnemyFileName(std::string const& stagenum)
{
	std::string filetop = "Resources/CSV/Enemy",
		filebottom = ".csv",
		filename = "none";

	filename = filetop + stagenum + filebottom;

	return filename;

}

/*========================================
全ての敵の衝突判定フラグを降ろす処理
==========================================*/
void EnemyManager::ResetEnemyHitFlag()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mEnemyBlockHitFlag[i] = false;
		mpEnemy[i]->SetEnemyGroundObjectHitFlag(false);
	}
}



/*==========================================
全ての敵が死亡したことを確認するフラグ
==========================================*/
bool EnemyManager::AllEnemyDeathFlag()
{
	//現在のフェーズが最大フェーズ出ないならば処理を通さない
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}

	//敵の数だけ行う
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		
		//使用している敵がいたら
		if (mpEnemy[i]->GetEnemyUseFlag())
		{
			//falseを返す
			return false;
		}
	}
	//ここに来る==全ての敵が未使用状態の場合
	return true;
}

/*===================================================================
対象の弾番号を持つ敵の弾番号を初期化する:private
引数：弾の要素番号
===================================================================*/
void EnemyManager::ResetBulletNum(int const& bulletIndex)
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//番号が消滅した番号と同じならば
		if (mpEnemy[i]->GetSaveBulletNumber() == bulletIndex)
		{
			//番号を初期化する
			mpEnemy[i]->SetSaveBulletNumber(Utility::EXCEPTION_NUM);
		}
	}
}

/*==================================
生きている敵を一斉に爆破させる
===================================*/
void EnemyManager::ExplosionSimultaneousEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//使用していなければ処理を行わない
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//エフェクトを設定する
		this->SetEnemyEffect(eEffectType::BOMB, mpEnemy[i]->GetBoxModel()->GetPosition(), i);
		mpEnemy[i]->SelfDestroy();
	}
}

/*===================================
ファイルから情報を取得する:private
引数：ファイルパス、カメラへのポインタ
===================================*/
void EnemyManager::LoadFile(std::string filepath,CameraBase* camera)
{
	//初期化
	DirectX::SimpleMath::Vector3 pos= NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//情報読み込み
	mpEnemyCall->LoadInfo(filepath);

	//サイズを改めて指定
	mpEnemy.resize(mpEnemyCall->GetEnemyStructerSize());

	//生成
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//情報が最大サイズになったら(これ以上敵情報がなければ)
		if (i == mpEnemyCall->GetEnemyStructerSize()) 
		{
			//for文を抜ける。
			break;
		}
		pos = mpEnemyCall.get()->GetEnemyStructer(i).mVectorESPosition;
		phasenum = mpEnemyCall.get()->GetEnemyStructer(i).mPhaseNumber;
		mpEnemy[i]->SetMovePhaseNumber(phasenum);
		mpEnemy[i]->Initialize(pos, camera);
	}

	//不要になったので削除
	mpEnemyCall->Reset();
}


/*========================================================================
エフェクトを設定する:private
引数：エフェクトの種類、敵の座標、
		敵の要素番号、エフェクトフラグを建てるか(true：建てる)
========================================================================*/
void EnemyManager::SetEnemyEffect(eEffectType type, DirectX::SimpleMath::Vector3 pos,
								int index,bool flagOn)
{
	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(pos + EFFECT_SHIFT_POSITION);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);

	if (flagOn)
	{
		//エフェクトを稼働中にする
		mpEnemy[index]->SetEffectFlag(true);
		mpEnemy[index]->SetSpriteFlagAddress(effect->GetSpriteFlagAddress());
	}
}


/*===================================================
全てのブーメラン接触フラグを下す:private
===================================================*/
void EnemyManager::ResetBoomerangHitFlag()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->SetBoomerangHitFlag(false);
	}
}