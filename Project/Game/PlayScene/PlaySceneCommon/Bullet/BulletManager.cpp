/*
�e�Ǘ��N���X
�쐬���F2021/09/17
*/
#include"pch.h"

#include"BulletManager.h"

//�O���錾
#include"../ObjectModel/BoxModel.h"
#include"../Enemy/Enemy.h"
#include"../Block/BlockManager.h"
#include"BulletStateBoomerang.h"
#include"../Enemy/EnemyManager.h"

//�G�t�F�N�g�̎g�p
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//�֐��̎g�p
#include"Libraries/MyLibraries/Camera.h"
#include"../Player/Player.h"
#include"../Enemy/EStateKnockBack.h"
#include"../ObjectModel/SphereModel.h"


//�ő�͈�
const float BulletManager::BULLET_MAX_POSITION_Z = -50.f;

//�C���^�[�o���v���I���p�������p�萔
const int BulletManager::BULLET_INTERVAL_FINISH_NUM = -1;

/*===================================
�R���X�g���N�^
===================================*/
BulletManager::BulletManager()
	:
	mpBullet{ nullptr },
	mpBulletType(nullptr),
	mBulletShotIntervalFlag(false),
	mIntervalTimer(Utility::EXCEPTION_NUM),
	mWeaponType(),
	mpCamera(nullptr),
	mpBoomerangBullet(nullptr),
	mpEnemyManager(nullptr)
{
	//�e�̏�������
	for (int i = 0; i < BULLET_MAX_NUM ; i++)
	{
		mpBullet[i] = std::make_unique<Bullet>();
	}

	//�e���Ǘ��N���X
	mpBulletType = std::make_unique<BulletType>();

	//�u�[�������̏����N���X
	mpBoomerangBullet = std::make_unique<BulletStateBoomerang>();
}

/*===================================
�f�X�g���N�^
===================================*/
BulletManager::~BulletManager()
{
}

/*=============================================================================================
����������
�����F�J�����̃|�C���^�A�v���C���[�̃|�C���^�A�G�Ǘ��N���X�̃|�C���^
===============================================================================================*/
void BulletManager::Initialize(CameraBase* pCamera, Player* pPlayer, EnemyManager* pEnemyManager)
{
	//�S�Ă̒e�̏���������
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		mpBullet[i]->Initialize();
	}

	//�|�C���^�ۑ�
	mpCamera = pCamera;
	mpEnemyManager = pEnemyManager;

	//�t�@�C���ǂݍ���
	mpBulletType->SetCSV("Resources/CSV/WeaponInfomation.csv");

	//���W�����炩���ߕۑ����Ă���
	mpBoomerangBullet->SavePlayerPointer(pPlayer);

}
/*==========================================
�e��������
�����F�e�̏o�����W�A�e�̎��
�Ԃ�l�F�e�̐����̐��������s��(true�F����)
==========================================*/
bool BulletManager::Create(DirectX::SimpleMath::Vector3 const& pos)
{
	//�������˂ł����Ԃł͂Ȃ��Ȃ珈�����I����
	if (!mBulletShotIntervalFlag)
	{
		return false;
	}

	//�S�Ă̒e����
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//�����e���g�p����Ă�����X�L�b�v����
		if (mpBullet[i]->GetUseFlag())
		{
			continue;
		}

		//�����Ώۂ̒e�Ȃ�|�C���^��n��
		if (mWeaponType == eWeaponType::BOOMERANG)
		{
			mpBoomerangBullet->SetBuletPointer(mpBullet[i].get());
			mpBullet[i]->SetBoomerangPointer(mpBoomerangBullet.get());
		}


		//�e���쐬
		mpBullet[i]->Create(pos, mWeaponType);
		//�Ή������e�̎�ނ����A���̒e�̏���e�P�̂ɕۑ��ۑ�
		mpBullet[i]->SetBulletInfomation(*mpBulletType.get()->GetBulletInfomation(mWeaponType));

		//�C���^�[�o���v���J�n
		this->ResetIntervalTimer();

		//�쐬�ł����甲����
		return true;
	}

	return false;
}

/*=================================
�X�V����
===================================*/
void BulletManager::Update()
{
	//�S�Ă̒e�̍X�V����
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��ԂȂ珈�������Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			//���g�p��Ԃ�


			continue;
		}

		mpBullet[i]->Update();
	}

	//�C���^�[�o���v������
	mBulletShotIntervalFlag = this->MeasureInterval();

	//�͈͊O����
	this->OutOfRange();
}

/*==================================
�`�揈��
===================================*/
void BulletManager::Draw()
{
	//�S�Ă̒e�̕`�揈��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��ԂȂ珈�������Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			continue;
		}
		mpBullet[i]->Draw();
	}
}

/*==================================
�e�ƓG�̏Փ˔���
�����F�G�P�̂̃|�C���^
�Ԃ�l�F�G�̒ǉ����j��
===================================*/
int BulletManager::ChackHitBulletEnemy(Enemy* pEnemy)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	int breakNum = 0;
	bool hitflag = false;
	//�e�̐�������
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��Ԃ̒e�͏�����ʂ��Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			continue;
		}

		//�����������Ă�����
		if (pC.Intersect(
			mpBullet[i]->GetBulletModelCollider(), 
			pEnemy->GetBoxModel()->GetAABBCollider()))
		{
			
			bool breakflag = false;
			hitflag = true;

			//�_���[�W�l���ɏo���Ă���
			int damageNum(mpBullet[i]->GetBulletAttackNum());


			//�e�̎�ނɉ����ď�����ς���
			switch (mpBullet[i]->GetBulletWeaponType())
			{
				case eWeaponType::MACHINE_GUN:
				case eWeaponType::PISTOL:			//NoBreak
				{
					//�����܂������������Ƃ̂Ȃ��e��������
					if (pEnemy->GetSaveBulletNumber()!=i)
					{
						breakflag = pEnemy->Damage(damageNum);

						//�G�t�F�N�g��ݒ肷��
						this->SetEffect(eEffectType::SLASH, pEnemy->GetBoxModel()->GetPosition());

						//�ڐG�����e�ԍ���ۑ�����
						pEnemy->SetSaveBulletNumber(i);
					}
					
					break;
				}		
				case eWeaponType::BOMB:
				case eWeaponType::ROCKET_LAUNCHER://NoBreak
				{
					//�G�Ƀ_���[�W��^����
					breakflag = pEnemy->Damage(mpBullet[i]->GetBulletAttackNum());
					//�����t���O�����Ă�
					mpBullet[i]->SetExplosionFlag(true);
					mpBullet[i]->SetDoubleCollider();
					//�G�t�F�N�g��ݒ肷��
					this->SetEffect(eEffectType::BOMB, pEnemy->GetBoxModel()->GetPosition());

					//�Ώۂ̃u�[�������ڐG�t���O�𗧂Ă�
					pEnemy->SetBoomerangHitFlag(true);

					//�ڐG�����e�ԍ���ۑ�����
					pEnemy->SetSaveBulletNumber(i);

					//�m�b�N�o�b�N�̕������Z�o����
					DirectX::SimpleMath::Vector3 knockBackVelocity = pEnemy->GetBoxModel()->GetPosition() -
						mpBullet[i]->GetBulletModel()->GetPosition();
					knockBackVelocity.y = 0.f;
					pEnemy->GetStateKnockBack()->SetMoveVector(knockBackVelocity);
					pEnemy->ChangeStateKnockBack();
					
					break;
				}
				case eWeaponType::BOOMERANG:
				{
					//�u�[�������ɓ������Ă��Ȃ�������
					if (!pEnemy->GetBoomerangHitFlag())
					{
						//�G�Ƀ_���[�W��^����
						breakflag = pEnemy->Damage(mpBullet[i]->GetBulletAttackNum());
						//�G�t�F�N�g��ݒ肷��
						this->SetEffect(eEffectType::SLASH, pEnemy->GetBoxModel()->GetPosition());
						//�Ώۂ̃u�[�������ڐG�t���O�𗧂Ă�
						pEnemy->SetBoomerangHitFlag(true);
					}
					
					break;
				}
			}

			//�_���[�W�G�t�F�N�g�����Z�b�g����
			pEnemy->ResetNumberEffect();
			//�쐬����
			pEnemy->CreateNumberEffect(pEnemy->GetEnemyDamage());

			//�|���Ă����瑝��������
			if (breakflag)
			{
				breakNum++;
			}

			//�u�[�������A�����n�e�ȊO�Ȃ�
			if (mpBullet[i]->GetBulletWeaponType() != eWeaponType::BOOMERANG&&
				mpBullet[i]->GetBulletWeaponType() != eWeaponType::BOMB&&
				mpBullet[i]->GetBulletWeaponType() != eWeaponType::ROCKET_LAUNCHER)
			{
				//�e�����ł�����
				mpBullet[i]->SelfDestroy();

				//�ԍ������ł����ԍ��Ɠ����Ȃ��
				if (pEnemy->GetSaveBulletNumber() == i)
				{
					//�ԍ�������������
					pEnemy->SetSaveBulletNumber(Utility::EXCEPTION_NUM);
				}
			}
		}
		//�u�[�������ɓ������Ă��Ȃ�������
		else if(pEnemy->GetBoomerangHitFlag())
		{
			//�Ώۂ̃u�[�������ڐG�t���O������
			pEnemy->SetBoomerangHitFlag(false);
		}
		
	}
	return breakNum;
}

/*=================================
�v���C���[�ƒe�̏Փ˔���
�����F�v���C���[�̃|�C���^
===================================*/
void BulletManager::ChackHitBulletPlayer(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�S�Ă̒e�̕`�揈��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��ԂȂ珈�������Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			continue;
		}
		//�u�[�������ȊO�ł�������ʂ��Ȃ�
		if (mpBullet[i]->GetBulletWeaponType() != eWeaponType::BOOMERANG)
		{
			continue;
		}
		if (mpBoomerangBullet->GetBoomerangState() == eBoomerangState::SHOT||
			mpBoomerangBullet->GetBoomerangState() == eBoomerangState::NONE)
		{
			continue;
		}

		//�����蔻������
		if (pC.Intersect(
			mpBullet[i]->GetBulletModelCollider(),
			pPlayer->GetPlayerModel()->GetAABBCollider()))
		{
			//�������Ă�����
			mpBoomerangBullet->ChangeBoomerangState(eBoomerangState::CATCH);
		}
	}
}

/*===================================
�u���b�N�Ƃ̏Փ˔�����񂷊֐�
�����F�u���b�N�Ǘ��N���X�̃|�C���^
===================================*/
void BulletManager::RoolChackHitBlock(BlockManager* pBlockManager)
{
	//�S�Ă̒e�̕`�揈��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��ԂȂ珈�������Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			continue;
		}

		//�����蔻�菈��
		pBlockManager->ChackBulletBlock(mpBullet[i].get());
	}
}

/*===================================
�͈͊O�̒e�̏���:private
===================================*/
void BulletManager::OutOfRange()
{
	//�S�Ă̒e�̕`�揈��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//���g�p��ԂȂ珈�������Ȃ�
		if (!mpBullet[i]->GetUseFlag())
		{
			continue;
		}
		//�u�[�������ł����������Ȃ�
		if (mpBullet[i]->GetBulletWeaponType() == eWeaponType::BOOMERANG)
		{
			continue;
		}

		//����Z���W���͈͊O�ɂȂ�����
		if (mpBullet[i]->GetBulletPositionZ() <= BULLET_MAX_POSITION_Z)
		{
			//���g�p��ԂƂ���
			mpBullet[i]->SelfDestroy();

			//�e�ԍ������Z�b�g����
			mpEnemyManager->ResetBulletNum(i);
		}
	}
}

/*=============================================
�C���^�[�o���v��:private
�Ԃ�l�F�e���ˉ\���s�\��(true�F�\)
=============================================*/
bool BulletManager::MeasureInterval()
{
	if (mIntervalTimer == BULLET_INTERVAL_FINISH_NUM)
	{
		return true;
	}

	//�^�C�}�[���X�V
	mIntervalTimer++;

	//�����ɉ������C���^�[�o���������s��
	//�ȗ����ϐ��̐錾
	int intervalNum = mpBulletType.get()->GetBulletInfomation(mWeaponType)
													->mBulletIntervalNum;
	//�C���^�[�o�����I�������
	if (mIntervalTimer == intervalNum)
	{
		mIntervalTimer = BULLET_INTERVAL_FINISH_NUM;

		return true;
	}

	return false;
}

/*====================================================
�G�t�F�N�g��ݒ肷��:private
�����F�G�t�F�N�g�̎�ށA���W
====================================================*/
void BulletManager::SetEffect(eEffectType const& type, DirectX::SimpleMath::Vector3 const& pos)
{
	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(pos + DirectX::SimpleMath::Vector3::UnitY);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);
}
