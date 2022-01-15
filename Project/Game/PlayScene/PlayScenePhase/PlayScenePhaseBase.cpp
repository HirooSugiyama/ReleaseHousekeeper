/*
�v���C�t�F�[�Y�����̃t�F�[�Y�������N���X
�쐬���F2021/06/16
*/
#include "pch.h"
#include "PlayScenePhaseBase.h"



//�O���錾
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/CelestialSphere.h"
#include"../PlaySceneCommon/Block/BlockManager.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"
#include"../PlaySceneCommon/GridLine/GridLineManager.h"
#include"../PlaySceneCommon/Weapon/WeaponManager.h"
#include"../PlaySceneCommon/Wall/WallManager.h"
#include"../PlaySceneCommon/Player/Player.h"
#include"../PlaySceneCommon/Ground.h"
#include"../PlaySceneCommon/Protecter.h"
#include"../PlaySceneCommon/GroundObject/GroundObjectManager.h"
#include"../PlaySceneCommon/Bullet/BulletManager.h"



/*=================================
�R���X�g���N�^
=================================*/
PlayScenePhaseBase::PlayScenePhaseBase()
	:
	mpAdministrator(nullptr),
	mpBlockManager(nullptr),
	mpEnemyManager(nullptr),
	mpGridLineManager(nullptr),
	mpWeaponManager(nullptr),
	mpWallManager(nullptr),
	mpPlayer(nullptr),
	mpGround(nullptr),
	mpProtecter(nullptr),
	mpGroundObjectManager(nullptr),
	mpBulletManager(nullptr),
	mpUI(nullptr)
{
}

/*=================================
���ʂŎg�p����|�C���^�̕ۑ�
=================================*/
void PlayScenePhaseBase::SaveCommonPointer(
	Administrator* pAdministrator, 
	BlockManager* pBlockManager, 
	EnemyManager* pEnemyManager, 
	GridLineManager* pGridLineManager,
	WeaponManager* pWeaponManager, 
	WallManager* pWallManager, 
	Player* pPlayer, 
	Ground* pGround, 
	Protecter* pProtecter,
	GroundObjectManager* pGroundObjectManager,
	BulletManager* pBulletManager,
	UI* pUI)
{
	mpAdministrator = pAdministrator; 
	mpBlockManager = pBlockManager;
	mpEnemyManager = pEnemyManager;
	mpGridLineManager = pGridLineManager;
	mpWeaponManager = pWeaponManager;
	mpWallManager = pWallManager;
	mpPlayer = pPlayer;
	mpGround = pGround;
	mpProtecter = pProtecter;
	mpGroundObjectManager = pGroundObjectManager;
	mpBulletManager = pBulletManager;
	mpUI = pUI;
}
