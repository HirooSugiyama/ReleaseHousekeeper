/*
プレイフェーズ内部のフェーズ分け基底クラス
作成日：2021/06/16
*/
#pragma once



//前方宣言
//共通で使用するもの
//ポインタ保存用
class Administrator;
class BlockManager;
class EnemyManager;
class GridLineManager;
class WeaponManager;
class WallManager;
class Player;
class Ground;
class Protecter;
class GroundObjectManager;
class BulletManager;
class UI;
class PlayScene;

class PlayScenePhaseBase
{
private:
	//各種ポインタ保存用変数
	Administrator* mpAdministrator;
	BlockManager* mpBlockManager;
	EnemyManager* mpEnemyManager;
	GridLineManager* mpGridLineManager;
	WeaponManager* mpWeaponManager;
	WallManager* mpWallManager;
	Player* mpPlayer;
	Ground* mpGround;
	Protecter* mpProtecter;
	GroundObjectManager* mpGroundObjectManager;
	BulletManager* mpBulletManager;
	UI* mpUI;

public:
	//コンストラクタ
	PlayScenePhaseBase();
	//デストラクタ
	virtual ~PlayScenePhaseBase() = default;

	//初期化
	virtual void Initialize(PlayScene* pPlayScene) = 0;
	//ポインタの保存
	void SaveCommonPointer(
		Administrator* pAdministrator,
		BlockManager* pBlockManager,
		EnemyManager* pEnemyManager,
		GridLineManager* pGridLineManager,
		WeaponManager* pWeaponManager,
		WallManager* pWallManager,
		Player* pPlayer,
		Ground* pGround,
		Protecter* mpProtecter,
		GroundObjectManager* pGroundObjectManager,
		BulletManager* pBulletManager,
		UI* pUI);

	//更新
	virtual void Update()=0;

	//State変更前のリセット処理
	virtual void Reset() {}

	//描画
	virtual void Draw() = 0;


protected:
	Administrator* GetAdministrator(){ return mpAdministrator; }
	BlockManager* GetBlockManager() { return mpBlockManager; }
	EnemyManager* GetEnemyManager() { return mpEnemyManager; }
	GridLineManager* GetGridLineManager() { return mpGridLineManager; }
	WeaponManager* GetWeaponManager() { return mpWeaponManager; }
	WallManager* GetWallManager() { return mpWallManager; }
	Player* GetPlayer(){ return mpPlayer; }
	Ground* GetGround(){ return mpGround; }
	Protecter* GetProtecter() { return mpProtecter; }
	GroundObjectManager* GetGroundObjectManager() { return mpGroundObjectManager; }
	BulletManager* GetBulletManager() { return mpBulletManager; }
	UI* GetUI() { return mpUI; }

};
