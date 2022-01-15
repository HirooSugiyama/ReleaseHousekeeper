/*
障害物管理クラス
*/
#pragma once

//所持
#include"Block.h"

//前方宣言
//当たり判定用
class PreparingBlock;
class Player;
class Administrator;
class Bullet;
class Camera;

//ポインタ保存用
class EnemyManager;


class BlockManager
{
private:
	//定数
	//壁の初期数
	static const int BLOCK_MAXNUM = 500;

	//爆発ダメージ
	static const int EXPLOSION_BLOCK_DAMAGE;

	//エフェクトを描画する座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//変数
	std::unique_ptr<Block> mpBlock[BLOCK_MAXNUM];

	//ポインタ保存用変数
	EnemyManager* mpEnemyManager;

public:
	//関数
		//コンストラクタ
	BlockManager();
		//デストラクタ
	~BlockManager();
		//初期化
	void Initialize(EnemyManager* pEnemyManager);
		//更新
	void Update();
		//壁生成
	void CreateBlock
		(DirectX::SimpleMath::Vector3 const& pos,
		DirectX::SimpleMath::Vector3 const& scale);
		//描画
	void Draw();
		//終了処理
	void Finalize();

	//敵の当たり判定を回す
	void RoolEnemyManagerChackHit();

	//サンプルブロックとブロックの当たり判定
	void ChackHitSampleBlockBlock(PreparingBlock* pPreparingBlock, Player* pPlayer);

	//ブロックとプレイヤーの当たり判定
	void ChackhitPlayerBlock(Player* pPlayer);

	//ブロックと球の当たり判定
	void ChackBulletBlock(Bullet* pBullet);

};