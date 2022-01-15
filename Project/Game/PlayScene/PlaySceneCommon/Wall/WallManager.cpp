/*
障害物管理クラス
*/
#include<pch.h>
#include "WallManager.h"


//前方宣言
//当たり判定用
#include"../Player/Player.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../Enemy/EnemyManager.h"

//当たり判定で内部閲覧のため使用
#include"../ObjectModel/BoxModel.h"
//移動速度の取得で使用
#include"../ObjectMove.h"

#include"WallConstant.h"

/*===================================
コンストラクタ
===================================*/
WallManager::WallManager()
	:
	mpWall{}
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		mpWall[i] = std::make_unique<Wall>();
	}
}

/*===================================
デストラクタ
===================================*/
WallManager::~WallManager()
{
}

/*===================================
初期化処理
===================================*/
void WallManager::Initialize()
{
	//変数の宣言
	DirectX::SimpleMath::Vector3 pos,scale;

	//左壁
	pos.x = WallConstant::WALL_LEFT_POSITION_X;
	pos.y = WallConstant::WALL_LEFT_POSITION_Y;
	pos.z = WallConstant::WALL_LEFT_POSITION_Z;

	scale.x = WallConstant::WALL_LEFT_SCALE_X;
	scale.y = WallConstant::WALL_LEFT_SCALE_Y;
	scale.z = WallConstant::WALL_LEFT_SCALE_Z;

	mpWall[static_cast<int>(eWallPosition::LEFT_WALL)]->Initialize(pos, scale);

	//右壁
	pos.x = WallConstant::WALL_RIGHT_POSITION_X;
	pos.y = WallConstant::WALL_RIGHT_POSITION_Y;
	pos.z = WallConstant::WALL_RIGHT_POSITION_Z;

	scale.x = WallConstant::WALL_RIGHT_SCALE_X;
	scale.y = WallConstant::WALL_RIGHT_SCALE_Y;
	scale.z = WallConstant::WALL_RIGHT_SCALE_Z;
	mpWall[static_cast<int>(eWallPosition::RIGHT_WALL)]->Initialize(pos, scale);

}
/*===================================
描画処理
===================================*/
void WallManager::Draw()
{
	for (int i = 0; i < WALL_MAX_NUM; i++) 
	{
		mpWall[i]->Draw();
	}
}

/*===================================
敵との当たり判定を回す処理
引数：敵管理クラスのポインタ
===================================*/
void WallManager::RoolEnemyManagerChackHit(EnemyManager* pEnemyManager)
{
	for (int i = 0; i < WALL_MAX_NUM; i++)
	{
		//当たり判定を回す
		pEnemyManager->ChackHitWallEnemy(mpWall[i]->GetWallModel()->GetAABBCollider());
	}
}
