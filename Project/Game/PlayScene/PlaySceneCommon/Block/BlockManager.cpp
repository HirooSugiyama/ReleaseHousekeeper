/*
��Q���Ǘ��N���X
*/

#include<pch.h>
#include <SimpleMath.h>

#include "BlockManager.h"



//�����蔻��p
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../../PlaySceneCommon/Administrator/Administrator.h"
#include"../../PlaySceneCommon/Bullet/Bullet.h"

//�|�C���^�ۑ�
#include"../../PlaySceneCommon/Enemy/EnemyManager.h"
#include"Libraries/MyLibraries/Camera.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"
#include"../../Effect/Effect.h"

//�����蔻��ɂē����{���̂��ߎg�p
#include"../../PlaySceneCommon/ObjectModel/BoxModel.h"
#include"../../PlaySceneCommon/Player/ActionStateDefenseHouse.h"
#include"../../PlaySceneCommon/Player/PStateWalk.h"
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"
#include "../../PlaySceneCommon/Weapon/WeaponeType.h"

//�֐��̎g�p
#include"../Player/Defense/DefenseActionBlockCreate.h"




//�����_���[�W
const int BlockManager::EXPLOSION_BLOCK_DAMAGE = 1;

//�G�t�F�N�g��`�悷����W
const DirectX::SimpleMath::Vector3 BlockManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

/*===================================
�R���X�g���N�^
===================================*/
BlockManager::BlockManager()
	:
	mpBlock{},
	mpEnemyManager{}
{
}

/*===================================
�f�X�g���N�^
===================================*/
BlockManager::~BlockManager()
{
}
/*===================================================
����������
�����F�G�Ǘ��N���X�̃|�C���^�A�J�����̃|�C���^
===================================================*/
void BlockManager::Initialize(EnemyManager* pEnemyManager)
{
	//�u���b�N���̂��̂̃������m��
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		mpBlock[i] = std::make_unique<Block>();
	}

	//�u���b�N�̏�����
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		mpBlock[i]->Initialize();
	}
	//�|�C���^�̕ۑ�
	mpEnemyManager = pEnemyManager;
}

/*===================================
�X�V����
===================================*/
void BlockManager::Update()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//�g�p���Ă��Ȃ��u���b�N�͏�����ʂ��Ȃ�
		if (mpBlock[i]->GetBlockUseFlag() == false)
		{
			continue;
		}
		mpBlock[i]->Update();		
	}
}

/*================================
�ǐ���
�����F	pos(���W)�Ascale(�g�又��)
==================================*/
void BlockManager::CreateBlock(DirectX::SimpleMath::Vector3 const& pos,DirectX::SimpleMath::Vector3 const& scale)
{
	//�g�p���Ă��Ȃ��ǂ�����
	for (int i = 0; i <= BLOCK_MAXNUM; i++) 
	{
		//�g�p���̃u���b�N�Ȃ玟�̃u���b�N��
		if (mpBlock[i]->GetBlockUseFlag() == true) 
		{			
			continue;
		}
		else 
		{
			//�쐬�ł����烋�[�v�𔲂���B
			mpBlock[i]->Create(pos, scale);
			break;
		}		
	}	
}

/*===================================
�`�揈��
===================================*/
void BlockManager::Draw()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//�g�p���Ă��Ȃ��u���b�N�͏�����ʂ��Ȃ�
		if (mpBlock[i]->GetBlockUseFlag() == false) 
		{
			continue;
		}
		//�`�揈��
		mpBlock[i]->Draw();
	}
}

/*===================================
�I������
===================================*/
void BlockManager::Finalize()
{
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//�S�Ẵu���b�N�̏�����ʂ�
		mpBlock[i]->Finalize();
	}
}

/*====================================================================
�u���b�N�ƓG�̓����蔻����񂷏ꏊ
�����F�����Ă���A�C�e���̊Ǘ��N���X�̃|�C���^
======================================================================*/
void BlockManager::RoolEnemyManagerChackHit()
{
	//�u���b�N�̐������������s��
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{
		//�ǂ��g�p���Ă��Ȃ������珈����ʂ��Ȃ�
		if (mpBlock[i]->GetBlockUseFlag() == false) 
		{
			continue;
		}
		//�����蔻�����
		mpEnemyManager->ChackHitBlocklEnemy(mpBlock[i].get(),i);
	}

	//���������Ă͂܂����G�̉�]����
	mpEnemyManager->RotationEnemy();

	//�S�Ă̏Փ˃t���O������
	mpEnemyManager->ResetEnemyHitFlag();
}

/*=================================================
�T���v���u���b�N�ƃu���b�N�̓����蔻��
�����F���{�u���b�N�ƃv���C���[�̃|�C���^
===============================================*/
void BlockManager::ChackHitSampleBlockBlock(PreparingBlock* pPreparingBlock, Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	bool createflag = false;
	for (int i = 0; i < BLOCK_MAXNUM; i++) 
	{

		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!(mpBlock[i]->GetBlockUseFlag())) continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpBlock[i]->GetBoxModel()->GetAABBCollider(),
			pPreparingBlock->GetBoxModel()->GetAABBCollider()))
		{
			//���\�[�X�}�l�[�W���̏���
			auto pRM = ResourceManager::GetInstance();

			//�v���C���[�������Ă��Ȃ���Ԃɂ���
			pPlayer->GetDefenseHouse()->GetBlockCreate()->SetmOverLappingFlag(true);
			createflag = true;

			//���Ă��Ȃ��\���ɕύX����
			auto samplemodel = pRM->GetCmoModel("NotUseBlock");
			pPreparingBlock->GetBoxModel()->SetModel(samplemodel);
			break;
		}
	}
	//�����ǂ̕ǂƂ��������Ă��Ȃ�������
	if (!createflag) 
	{
		//���Ă���悤�ɂ���
		pPlayer->GetDefenseHouse()->GetBlockCreate()->SetmOverLappingFlag(false);

		//���\�[�X�}�l�[�W���̏���
		auto pRM = ResourceManager::GetInstance();
		//���Ă��Ȃ��\���ɕύX����
		auto samplemodel = pRM->GetCmoModel("WBlock");
		pPreparingBlock->GetBoxModel()->SetModel(samplemodel);
	}
}

/*=============================================
�u���b�N�ƃv���C���[�̓����蔻��
�����F�v���C���[�̃|�C���^
===============================================*/
void BlockManager::ChackhitPlayerBlock(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//����p�ϐ��̐錾
	bool hitflag = false;

	//�����蔻��̐������s��
	for (int i = 0; i < static_cast<int>(BLOCK_MAXNUM); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!(mpBlock[i]->GetBlockUseFlag()))
		{				
			continue;	//false�Ȃ�
		}

		//�����������Ă����珈�����s��
		if (pC.Intersect(
			pPlayer->GetStateWalk()->GetDestinationPlayerCollider(),	//�ړ���Ƀv���C���[�̓����蔻��
			mpBlock[i]->GetBoxModel()->GetAABBCollider()))				//�u���b�N�̓����蔻��
		{
			hitflag = true;

			//�u���b�N�ɂ͓������Ă��邱�Ƃɂ���
			pPlayer->GetStateWalk()->SetBlockHitFlag(true);
		}
	}

	//�������݂̓��͂ňړ����Ă��Փ˂��Ȃ��Ȃ��
	if (hitflag == false)
	{
		//�u���b�N�ɂ͓������Ă��Ȃ����Ƃɂ���
		pPlayer->GetStateWalk()->SetBlockHitFlag(false);
	}

}

/*==============================================
�u���b�N�ƒe�̓����蔻��
�����F�e�̃|�C���^
===============================================*/
void BlockManager::ChackBulletBlock(Bullet* pBullet)
{	
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�����蔻��̐������s��
	for (int i = 0; i < static_cast<int>(BLOCK_MAXNUM); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!(mpBlock[i]->GetBlockUseFlag()))
		{
			continue;	//false�Ȃ�
		}

		//�����������Ă����珈�����s��
		if (pC.Intersect(
			pBullet->GetBulletModelCollider(),	//�ړ���Ƀv���C���[�̓����蔻��
			mpBlock[i]->GetBoxModel()->GetAABBCollider()))				//�u���b�N�̓����蔻��
		{
			//�u���b�N�ɂ͒e�̍U���͕��_���[�W��^����
			int damagenum = pBullet->GetBulletAttackNum();

			//�����������Ȃ�_���[�W��1/10�Ƃ���
			if (pBullet->GetBulletWeaponType() == eWeaponType::BOMB ||
				pBullet->GetBulletWeaponType() == eWeaponType::ROCKET_LAUNCHER)
			{
				damagenum = EXPLOSION_BLOCK_DAMAGE;
			}

			bool hpJuge = mpBlock[i]->BlockDamage(damagenum);

			//HP��0�ȉ��Ȃ疢�g�p��ԂƂ���
			if (hpJuge)
			{
				mpBlock[i]->SelfDestroy();
				//�G�t�F�N�g�}�l�[�W���[�̎擾
				auto pEM = EffectManager::GetInstance();
				
				auto effect = pEM->GetEffect(eEffectType::DESTROY);
				effect->SetPosition(mpBlock[i]->GetBoxModel()->GetPosition() +
					EFFECT_SHIFT_POSITION);
				effect->SetSpriteFlag(true);
				effect->SetLoopFlag(false);
			}

			//�����e�̎�ނ����̂����ꂩ�Ȃ��
			eWeaponType type = pBullet->GetBulletWeaponType();

			if (type == eWeaponType::MACHINE_GUN ||
				type == eWeaponType::PISTOL)
			{
				//�e�𖢎g�p��ԂƂ���
				pBullet->SelfDestroy();
			}
			//�����������Ȃ�
			if (type == eWeaponType::BOOMERANG ||
				type == eWeaponType::ROCKET_LAUNCHER)
			{
				//�����t���O�����Ă�
				pBullet->SetExplosionFlag(true);
				pBullet->SetDoubleCollider();
			}
		}
	}
}
