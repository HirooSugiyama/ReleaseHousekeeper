/*
�G�Ǘ��N���X
*/
#pragma once


#include"../../Effect/EffectType.h"

//����
#include"EnemyCall.h"
#include"Enemy.h"

//�O���錾
class Block;				//�����蔻��
class Player;				//�����蔻��
class Protecter;			//�����蔻��
class Administrator;		//�|�C���^(����)
class DangerousLine;		//�|�C���^(����)
class GroundObjectManager;	//�����蔻��
class BulletManager;		//�����蔻��
struct AABB;				//�����蔻��
class EffectSpriteTexture;	//����
class CameraBase;				//�|�C���^(����)

class EnemyManager
{
private:

	//�萔
	//�����T�C�Y
	static const int ENEMY_INIT_SIZE;
	 
	//���g�p�̓G�̏o�����W
	static const DirectX::SimpleMath::Vector3 NOT_SET_ENEMY_POSITION;

	//�����g�嗦
	static const DirectX::SimpleMath::Vector3 ENEMY_INIT_SCALE;

	//�G�̍U����
	static const int ENEMY_ATTACK_NUM;

	//�G�������o���������̐�
	static const int ENEMY_RAND_ANGLE_NUM;

	//�X�R�A�l
	static const int ENEMY_SCORE;

	//�G�t�F�N�g�̏o����������W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//�G�̃v���C���[�ߑ��͈�
	static const float ENEMY_CAPTURE_RANGE;


	//�ϐ�
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

	//�G�o���C���^�[�o��
	int mEnemyAppearanceInterval;

	//�Ăяo���N���X
	std::unique_ptr<EnemyCall> mpEnemyCall;

	//�|�C���^�ۑ�
	Administrator* mpAdministrator;

	//�G�̍ő�o�����W
	int mMaxEnemySpawnPositionZ;

	//�ǂݍ��ރt�@�C����
	std::string mLoadEnemyFileName;

	//���݂̃t�F�[�Y�ԍ�
	int mNowPhaseNum;

	//�ő�t�F�[�Y��
	int mMaxPhaseNum;

	//�Փ˔���p�t���O�ϐ��̐錾
	std::vector<bool> mEnemyBlockHitFlag;

	//���݂̓G�̌��j��
	int mNowEnemyBreakNum;

public:
	//�֐�
	//�R���X�g���N�^
	EnemyManager();
	//�f�X�g���N�^
	~EnemyManager();
	//������
	void Initialize(CameraBase* camera, Administrator* pAdministrator);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I������
	void Finalize();

	//�G�̉񐔕����������蔻����񂷏���
	void RoolBulletManagerChackhit(BulletManager* pBulletManager);

	//�u���b�N�ƓG�̓����蔻��
	void ChackHitBlocklEnemy(Block* pBlock,int const& blockNum);

	//�G�̉�]����
	void RotationEnemy();

	//Todo:�����蔻�聨Detect

	//�v���C���[�ƓG�̓����蔻��
	void ChackHitPlayerEnemy(Player* pPlayer);
	void ChackHitNormalAttackPlayerEnemy(Player* pPlayer);	//�v���C���[�U�����̔���

	//���_�ƓG�̓����蔻��
	void ChackHitProtecterEnemy(Protecter* pProtecter);

	//�n��I�u�W�F�N�g�ƓG�̓����蔻��
	void ChackHitGroundObjectEnemy(AABB* pObjectCollider);

	//��ƓG�̓����蔻��
	void ChackHitWallEnemy(AABB* pWallCollider);

	//�댯�M�����C���ƓG�̓����蔻��
	bool ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine);

	//�ΏۂƓG�̋�������
	void ChackDistanceTargetEnemy(DirectX::SimpleMath::Vector3 const& pos,bool playerFlag=false);

	//���Z�b�g����
	void Reset();

	//�ǂݍ��ރt�@�C�����̎擾
	void SetLoadEnemyFileName(std::string const& filename) { mLoadEnemyFileName = filename; }

	//�ǂݍ��ރt�@�C�������쐬
	std::string CreateLoadEnemyFileName(std::string const& stagenum);

	//�t�F�[�Y�ԍ��̎擾
	void SetNowPhaseNum(int const& phasenumber) { mNowPhaseNum = phasenumber; }

	void SetMaxPhaseNum(int const& phasenumber) { mMaxPhaseNum = phasenumber; }


	//�G�̏Փ˔���t���O�̃A�N�Z�T
	bool GetEnemyHitFlag(int const& i) const { return mEnemyBlockHitFlag[i]; }

	//�S�Ă̓G�̏Փ˔���t���O���~�낷����
	void ResetEnemyHitFlag();

	//�S�Ă̓G�����S�������Ƃ��m�F����t���O
	bool AllEnemyDeathFlag();

	//�G���j���̃A�N�Z�T
	int GetBreakEnemyNum()const { return mNowEnemyBreakNum; }

	//�G�̍ő吔�̃A�N�Z�T
	int GetMaxEnemyNum()const { return static_cast<int>(mpEnemy.size()); }

	//�Ώۂ̒e�ԍ������G�̒e�ԍ�������������
	void ResetBulletNum(int const& bulletIndex);

	//�c���Ă���G����Ăɔ��j������
	void ExplosionSimultaneousEnemy();



private:

	//�t�@�C����������擾����
	void LoadFile(std::string filepath, CameraBase* camera);

	
	//�G�t�F�N�g��ݒ肷��
	void SetEnemyEffect(eEffectType type,DirectX::SimpleMath::Vector3 pos,
		int index,bool flagOn=false);


	//�S�Ẵu�[�������ڐG�t���O������
	void ResetBoomerangHitFlag();

};
