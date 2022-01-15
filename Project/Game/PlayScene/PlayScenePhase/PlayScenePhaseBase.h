/*
�v���C�t�F�[�Y�����̃t�F�[�Y�������N���X
�쐬���F2021/06/16
*/
#pragma once



//�O���錾
//���ʂŎg�p�������
//�|�C���^�ۑ��p
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
	//�e��|�C���^�ۑ��p�ϐ�
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
	//�R���X�g���N�^
	PlayScenePhaseBase();
	//�f�X�g���N�^
	virtual ~PlayScenePhaseBase() = default;

	//������
	virtual void Initialize(PlayScene* pPlayScene) = 0;
	//�|�C���^�̕ۑ�
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

	//�X�V
	virtual void Update()=0;

	//State�ύX�O�̃��Z�b�g����
	virtual void Reset() {}

	//�`��
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
