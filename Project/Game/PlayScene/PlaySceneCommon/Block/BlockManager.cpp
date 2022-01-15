/*
障害物管理クラス
*/

#include<pch.h>
#include <SimpleMath.h>

#include "BlockManager.h"



//当たり判定用
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../../PlaySceneCommon/Administrator/Administrator.h"
#include"../../PlaySceneCommon/Bullet/Bullet.h"

//ポインタ保存
#include"../../PlaySceneCommon/Enemy/EnemyManager.h"
#include"Libraries/MyLibraries/Camera.h"

//エフェクトの取得
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//当たり判定にて内部閲覧のため使用
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../../PlaySceneCommon/Player/ActionStateDefenseHouse.h"
#include"../../PlaySceneCommon/Player/PStateWalk.h"
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"
#include "../../PlaySceneCommon/Weapon/WeaponeType.h"

//関数の使用
#include"../Player/Defense/DefenseActionBlockCreate.h"




//爆発ダメージ
const int BlockManager::EXPLOSION_BLOCK_DAMAGE = 1;

//エフェクトを描画する座標
const DirectX::SimpleMath::Vector3 BlockManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

/*===================================
コンストラクタ
===================================*/
BlockManager::BlockManager()
	:
	mpBlock{},
	mpEnemyManager{}
{
}

/*===================================
デストラクタ
===================================*/
BlockManager::~BlockManager()
{
}
/*===================================================
初期化処理
引数：敵管理クラスのポインタ、カメラのポインタ
===================================================*/
void BlockManager::Initialize(EnemyManager* pEnemyManager)
{
	//ブロックそのもののメモリ確保
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		mpBlock[i] = std::make_unique<Block>();
	}

	//ブロックの初期化
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		mpBlock[i]->Initialize();
	}
	//ポインタの保存
	mpEnemyManager = pEnemyManager;
}

/*===================================
更新処理
===================================*/
void BlockManager::Update()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//使用していないブロックは処理を通さない
		if (mpBlock[i]->GetBlockUseFlag() == false)
		{
			continue;
		}
		mpBlock[i]->Update();		
	}
}

/*================================
壁生成
引数：	pos(座標)、scale(拡大処理)
==================================*/
void BlockManager::CreateBlock(DirectX::SimpleMath::Vector3 const& pos,DirectX::SimpleMath::Vector3 const& scale)
{
	//使用していない壁を検索
	for (int i = 0; i <= BLOCK_MAXNUM; i++) 
	{
		//使用中のブロックなら次のブロックへ
		if (mpBlock[i]->GetBlockUseFlag() == true) 
		{			
			continue;
		}
		else 
		{
			//作成できたらループを抜ける。
			mpBlock[i]->Create(pos, scale);
			break;
		}		
	}	
}

/*===================================
描画処理
===================================*/
void BlockManager::Draw()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//使用していないブロックは処理を通さない
		if (mpBlock[i]->GetBlockUseFlag() == false) 
		{
			continue;
		}
		//描画処理
		mpBlock[i]->Draw();
	}
}

/*===================================
終了処理
===================================*/
void BlockManager::Finalize()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//全てのブロックの処理を通す
		mpBlock[i]->Finalize();
	}
}

/*====================================================================
ブロックと敵の当たり判定を回す場所
引数：落ちているアイテムの管理クラスのポインタ
======================================================================*/
void BlockManager::RoolEnemyManagerChackHit()
{
	//ブロックの数だけ処理を行う
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//壁を使用していなかったら処理を通さない
		if (mpBlock[i]->GetBlockUseFlag() == false) 
		{
			continue;
		}
		//当たり判定を回す
		mpEnemyManager->ChackHitBlocklEnemy(mpBlock[i].get(),i);
	}

	//条件が当てはまった敵の回転処理
	mpEnemyManager->RotationEnemy();

	//全ての衝突フラグを下す
	mpEnemyManager->ResetEnemyHitFlag();
}

/*=================================================
サンプルブロックとブロックの当たり判定
引数：見本ブロックとプレイヤーのポインタ
===============================================*/
void BlockManager::ChackHitSampleBlockBlock(PreparingBlock* pPreparingBlock, Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	bool createflag = false;
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{

		//使用中ではないなら通さない。
		if (!(mpBlock[i]->GetBlockUseFlag())) continue;

		//当たっていたら処理をする
		if (pC.Intersect(
			mpBlock[i]->GetBoxModel()->GetAABBCollider(),
			pPreparingBlock->GetBoxModel()->GetAABBCollider()))
		{
			//リソースマネージャの準備
			auto pRM = ResourceManager::GetInstance();

			//プレイヤー側が建てられない状態にする
			pPlayer->GetDefenseHouse()->GetBlockCreate()->SetmOverLappingFlag(true);
			createflag = true;

			//建てられない表示に変更する
			auto samplemodel = pRM->GetCmoModel("NotUseBlock");
			pPreparingBlock->GetBoxModel()->SetModel(samplemodel);
			break;
		}
	}
	//もしどの壁とも当たっていなかったら
	if (!createflag) 
	{
		//建てられるようにする
		pPlayer->GetDefenseHouse()->GetBlockCreate()->SetmOverLappingFlag(false);

		//リソースマネージャの準備
		auto pRM = ResourceManager::GetInstance();
		//建てられない表示に変更する
		auto samplemodel = pRM->GetCmoModel("WBlock");
		pPreparingBlock->GetBoxModel()->SetModel(samplemodel);
	}
}

/*=============================================
ブロックとプレイヤーの当たり判定
引数：プレイヤーのポインタ
===============================================*/
void BlockManager::ChackhitPlayerBlock(Player* pPlayer)
{
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//判定用変数の宣言
	bool hitflag = false;

	//当たり判定の数だけ行う
	for (int i = 0; i < static_cast<int>(BLOCK_MAXNUM); i++)
	{
		//使用中ではないなら通さない。
		if (!(mpBlock[i]->GetBlockUseFlag()))
		{				
			continue;	//falseなら
		}

		//もし当たっていたら処理を行う
		if (pC.Intersect(
			pPlayer->GetStateWalk()->GetDestinationPlayerCollider(),	//移動先にプレイヤーの当たり判定
			mpBlock[i]->GetBoxModel()->GetAABBCollider()))				//ブロックの当たり判定
		{
			hitflag = true;

			//ブロックには当たっていることにする
			pPlayer->GetStateWalk()->SetBlockHitFlag(true);
		}
	}

	//もし現在の入力で移動しても衝突しないならば
	if (hitflag == false)
	{
		//ブロックには当たっていないことにする
		pPlayer->GetStateWalk()->SetBlockHitFlag(false);
	}

}

/*==============================================
ブロックと弾の当たり判定
引数：弾のポインタ
===============================================*/
void BlockManager::ChackBulletBlock(Bullet* pBullet)
{	
	//当たり判定関数群の取得
	Collider& pC = Collider::GetColliderInstance();

	//当たり判定の数だけ行う
	for (int i = 0; i < static_cast<int>(BLOCK_MAXNUM); i++)
	{
		//使用中ではないなら通さない。
		if (!(mpBlock[i]->GetBlockUseFlag()))
		{
			continue;	//falseなら
		}

		//もし当たっていたら処理を行う
		if (pC.Intersect(
			pBullet->GetBulletModelCollider(),	//移動先にプレイヤーの当たり判定
			mpBlock[i]->GetBoxModel()->GetAABBCollider()))				//ブロックの当たり判定
		{
			//ブロックには弾の攻撃力分ダメージを与える
			int damagenum = pBullet->GetBulletAttackNum();

			//もし爆発物ならダメージを1/10とする
			if (pBullet->GetBulletWeaponType() == eWeaponType::BOMB ||
				pBullet->GetBulletWeaponType() == eWeaponType::ROCKET_LAUNCHER)
			{
				damagenum = EXPLOSION_BLOCK_DAMAGE;
			}

			bool hpJuge = mpBlock[i]->BlockDamage(damagenum);

			//HPが0以下なら未使用状態とする
			if (hpJuge)
			{
				mpBlock[i]->SelfDestroy();
				//エフェクトマネージャーの取得
				auto pEM = EffectManager::GetInstance();
				
				auto effect = pEM->GetEffect(eEffectType::DESTROY);
				effect->SetPosition(mpBlock[i]->GetBoxModel()->GetPosition() +
					EFFECT_SHIFT_POSITION);
				effect->SetSpriteFlag(true);
				effect->SetLoopFlag(false);
			}

			//もし弾の種類が下のいずれかならば
			eWeaponType type = pBullet->GetBulletWeaponType();

			if (type == eWeaponType::MACHINE_GUN ||
				type == eWeaponType::PISTOL)
			{
				//弾を未使用状態とする
				pBullet->SelfDestroy();
			}
			//もし爆発物なら
			if (type == eWeaponType::BOOMERANG ||
				type == eWeaponType::ROCKET_LAUNCHER)
			{
				//爆発フラグを建てる
				pBullet->SetExplosionFlag(true);
				pBullet->SetDoubleCollider();
			}
		}
	}
}
