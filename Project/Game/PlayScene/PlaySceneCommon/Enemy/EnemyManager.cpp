/*
�G�Ǘ��N���X
*/

#include<pch.h>

#include "EnemyManager.h"


//�O���錾
#include"../../Effect/Effect.h"

//�����蔻��
#include"../Block/Block.h"
#include"../Player/Player.h"
#include"../Protecter.h"
#include"../Administrator/Administrator.h"

//�����蔻��̍ۂɊ֐����g�p
#include"../Administrator/Score.h"
#include"../ObjectModel/BoxModel.h"
#include"../Weapon/WeaponHand.h"
#include"../ObjectModel/SphereModel.h"
#include"EStateKnockBack.h"
#include"../../PlaySceneDefence/DangerousLine.h"

//�񋓌^�̎g�p
#include "EnemyStateBase.h"
#include"../Player/ActionStateAttackEnemy.h"

//�G�t�F�N�g�̎擾
#include"../../Effect/EffectManager.h"

//�֐��̎g�p
#include"EStateWalk.h"
#include"EStateAppearance.h"
#include"EStateRotation.h"
#include"EStateAttack.h"
#include"EStateBuried.h"

#include"../Bullet/BulletManager.h"


//�����T�C�Y
const int EnemyManager::ENEMY_INIT_SIZE = 100;

//���g�p�̓G�̏o�����W
const DirectX::SimpleMath::Vector3 EnemyManager::NOT_SET_ENEMY_POSITION(-10.f, -10.f, -10.f);


//�����g�嗦
const DirectX::SimpleMath::Vector3 EnemyManager::ENEMY_INIT_SCALE(1.f, 1.f, 1.f);


//�G�̍U����
const int EnemyManager::ENEMY_ATTACK_NUM = 1;


//�G�������o���������̐�
const int EnemyManager::ENEMY_RAND_ANGLE_NUM = 2;


//�X�R�A�l
const int EnemyManager::ENEMY_SCORE = 100;

//�G�t�F�N�g�̏o����������W
const DirectX::SimpleMath::Vector3 EnemyManager::EFFECT_SHIFT_POSITION(0.f, 1.f, 1.f);

//�G�̃v���C���[�ߑ��͈�
const float EnemyManager::ENEMY_CAPTURE_RANGE = 5.f;

/*===================================
�R���X�g���N�^
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
	//�T�C�Y���������m�ۗp�ő吔�ɐݒ肷��
	mpEnemy.resize(ENEMY_INIT_SIZE);

	//�Ăяo���N���X���`
	mpEnemyCall = std::make_unique<EnemyCall>();


	//�G�̃������m��
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		mpEnemy[i] = std::make_unique<Enemy>();
	}

	//�G�̐��̕��Փ˃t���O���쐬����
	mEnemyBlockHitFlag.resize(static_cast<int>(mpEnemy.size()));

}

/*=================================
�f�X�g���N�^
===================================*/
EnemyManager::~EnemyManager()
{
}
/*=========================================================
����������
�����F�J�����ւ̃|�C���^�A�Ǘ��҃N���X�̃|�C���^
=========================================================*/
void EnemyManager::Initialize(CameraBase* camera, Administrator* pAdministrator)
{
	//�G�̓ǂݍ���
	this->LoadFile(mLoadEnemyFileName, camera);

	//�|�C���^�ۑ�
	mpAdministrator = pAdministrator;
}

/*===================================
�X�V����
===================================*/
void EnemyManager::Update()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		//�g�p���̂�
		if (mpEnemy[i]->GetEnemyUseFlag()) 
		{

			//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݏ�����ʂ�
			if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
			{
				//�����ҋ@��Ԃ̓G��������
				if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)
				{
					//���̏����֑���
					mpEnemy[i]->GetStateBuried()->ChangeNextState();
				}

				mpEnemy[i]->Update();
			}	
		}
	}
}

/*=================================
�`�揈��
===================================*/
void EnemyManager::Draw()
{

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++) 
	{
		if (mpEnemy[i]->GetEnemyUseFlag()) 
		{
			//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
			if (mpEnemy[i]->GetMovePhaseNumber() <= mNowPhaseNum)
			{
				mpEnemy[i]->Draw();
			}		
		}
	}
	
}

/*=================================
�I������
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
�G�̉񐔕����������蔻����񂷏���
�����F�e�Ǘ��N���X�̃|�C���^
====================================================*/
void EnemyManager::RoolBulletManagerChackhit(BulletManager* pBulletManager)
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!mpEnemy[i]->GetEnemyUseFlag())continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//�����蔻��̏�����ʂ�
		int breaknum = pBulletManager->ChackHitBulletEnemy(mpEnemy[i].get());
		
		//���j��������������������
		mNowEnemyBreakNum += breaknum;

		//�X�R�A����
		mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE * breaknum);
	}
}


/*====================================================================================================
�u���b�N�ƓG�̏Փ˔���֐�
����	�FpBlock(�g�p����u���b�N�̃|�C���^)
		�FblockNum(�u���b�N�̔z��ԍ�)
========================================================================================================*/
void EnemyManager::ChackHitBlocklEnemy(Block* pBlock, int const& blockNum)
{
	//�ȗ����p�ϐ��̐錾
	bool colliderFlag = false;
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!(mpEnemy[i]->GetEnemyUseFlag())) continue;

		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;


		//�U����Ԃ̏ꍇ 
		if (mpEnemy[i]->GetStateEnemy()== eStateEnemy::ATTACK)
		{
			//�U���p�̓����蔻��ŏՓ˔�������
			colliderFlag = pC.Intersect(
				mpEnemy[i]->GetStateAttack()->GetCollider(),
				pBlock->GetBoxModel()->GetAABBCollider());

			//�������Ă�����
			if (colliderFlag)
			{
				//�ǔԍ����ۑ�����ĂȂ�������
				if (mpEnemy[i]->GetStateAttack()->GetAttackBlockNum() == Utility::EXCEPTION_NUM)
				{
					//�ԍ���ۑ�����
					mpEnemy[i]->GetStateAttack()->SetAttackBlockNum(blockNum);
				}

				//�U������^�C�~���O�ł͂Ȃ�������
				if (!mpEnemy[i]->GetStateAttack()->AttackTiming())continue;

				//�u���b�N�Ƀ_���[�W��^����
				bool blockHP = pBlock->BlockDamage(mpEnemy[i]->GetStateAttack()->GetAttackPower());

				//�G�t�F�N�g��ݒ肷��
				this->SetEnemyEffect(eEffectType::CLAW, pBlock->GetBoxModel()->GetPosition(), i);

				//�����u���b�N��HP���Ȃ�������
				if (blockHP)
				{
					//�u���b�N��j�󂷂�
					pBlock->SelfDestroy();

					//�G�t�F�N�g�̐ݒ�
					this->SetEnemyEffect(eEffectType::DESTROY,
						pBlock->GetBoxModel()->GetPosition(), i);


					int blockindex = mpEnemy[i]->GetStateAttack()->GetAttackBlockNum();

					//�����ǔԍ��������ׂĂ̓G�ɏ������s��
					for (int j = 0; j < static_cast<int>(mpEnemy.size()); j++)
					{
						if (mpEnemy[j]->GetStateEnemy() != eStateEnemy::ATTACK)continue;

						//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
						if (!(mpEnemy[j]->GetEnemyUseFlag()))continue;


						//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
						//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
						if (mpEnemy[j]->GetMovePhaseNumber() > mNowPhaseNum ||
							mpEnemy[j]->GetMovePhaseNumber() == 0)continue;


						if (mpEnemy[j]->GetStateAttack()->GetAttackBlockNum() == blockindex)
						{
							//�ǔԍ������Z�b�g����
							mpEnemy[j]->GetStateAttack()->ResetAttackBlockNum();

							//�����𐳖ʂƂ���
							mpEnemy[j]->SetAngleEnemy(eAngleEnemy::STRAIGHT);

							//�����������ԂƂ���
							mpEnemy[j]->ChangeStateWalk();
						}

					}
				}
			}
		}
		//�U����ԈȊO�̏ꍇ
		else
		{
			//�G�s��State�̓����蔻��ŏՓ˔�������
			colliderFlag = pC.Intersect(
				mpEnemy[i]->GetWalkCollider(), pBlock->GetBoxModel()->GetAABBCollider());

			//�������Ă����珈��������
			if (colliderFlag)
			{
				//�G�����������t���O��ݒ肷��(�S�Ă̕ǂƂ̏Փ˔����A�~�낷�B)
				mEnemyBlockHitFlag[i] = true;

				//���ʈړ��ɐ؂�ւ���
				mpEnemy[i]->GetStateWalk()->ResetChaseVelocity();
				mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

				//�����G�����ړ����Ă��Ȃ�������
				if (mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::STRAIGHT)
				{
					//��]�ɐ؂�ւ���
					mpEnemy[i]->ChangeStateRotation();
					//�����łǂ����������������߂�
					srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
					bool angleflag = static_cast<bool>(rand() % ENEMY_RAND_ANGLE_NUM);
					//���ړ�������
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
�G�̉�]����
====================================================*/
void EnemyManager::RotationEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		if (!mEnemyBlockHitFlag[i])						//���̃t���[���łǂ̃u���b�N�ɂ��Ԃ����Ă��炸
		{
			if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::WALK)				//������Ԃ�
			{

				if (!mpEnemy[i]->GetEnemyGroundObjectHitFlag()&&			//�n��I�u�W�F�N�g�ɓ������Ă��炸
					(mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::LEFT ||				//���ړ����Ă���G��������
					mpEnemy[i]->GetAngleEnemy() == eAngleEnemy::RIGHT))
				{
					//���݂̃��f���̌������擾
					eAngleEnemy rot = mpEnemy[i]->GetAngleEnemy();


					switch (rot)
					{
						case eAngleEnemy::STRAIGHT:
						{
							break;
						}
						//���������Ă�����
						case eAngleEnemy::LEFT:
						{
							//����]������
							mpEnemy[i]->GetStateRotation()->
								SetChangeAfterAngle(eChangeAfterAngle::LEFT_ROTATION);

							break;
						}
						//�E�������Ă�����
						case eAngleEnemy::RIGHT:
						{
							//�E��]������
							mpEnemy[i]->GetStateRotation()->
								SetChangeAfterAngle(eChangeAfterAngle::RIGHT_ROTATION);

							break;
						}
					}

					//��]�ɐ؂�ւ���
					mpEnemy[i]->ChangeStateRotation();
				}
				//�ЂƂł��n��I�u�W�F�N�g�Ɠ������Ă�����
				else if(mpEnemy[i]->GetEnemyGroundObjectHitFlag())	
				{
					switch (mpEnemy[i]->GetAngleEnemy())
					{
						case eAngleEnemy::STRAIGHT:	//���ʂ������Ă�����
						{
							//��]�ɐ؂�ւ���
							mpEnemy[i]->ChangeStateRotation();
							//�����łǂ����������������߂�
							srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
							bool angleflag = static_cast<bool>(rand() % ENEMY_RAND_ANGLE_NUM);
							//���ړ�������
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
�v���C���[�ƓG�̏Փ˔���֐�
�����F�v���C���[�̃|�C���^
====================================================*/
void EnemyManager::ChackHitPlayerEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BLINKING)continue;

		//�v���C���[���_���[�W��ԂȂ珈�������Ȃ�
		if (pPlayer->GetPlayerState() == ePlayerState::DAMAGE) continue;


		//�������Ă����珈��������
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(), pPlayer->GetPlayerModel()->GetAABBCollider()))
		{
			//�v���C���[�Ƀ_���[�W��^����
			pPlayer->ChangeStateDamage();
		}
	}
}

/*===================================================
�v���C���[�U�����̃v���C���[�ƓG�̏Փ˔���֐�
�����F�v���C���[�̃|�C���^
====================================================*/
void EnemyManager::ChackHitNormalAttackPlayerEnemy(Player* pPlayer)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;


		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BLINKING||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::KNOCK_BACK)continue;



		//�I������null������\�������邽�߃`�F�b�N����
		if (pPlayer->GetAttackEnemy()->GetHand()->GetCollider() == nullptr)break;

		//�����v���C���[����U����ԂłȂ��Ȃ�Βʂ�Ȃ�
		if (pPlayer->GetAttackEnemy()->GetHand()->GetAttackFlag() != eHandState::ATTACK)continue;

		//�����G�t�F�N�g�ғ����Ȃ珈����ʂ��Ȃ�
		if (mpEnemy[i]->GetEffectFlag())continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			pPlayer->GetAttackEnemy()->GetHand()->GetCollider()->GetSphereCollider(),
			mpEnemy[i]->GetBoxModel()->GetAABBCollider()))
		{

			//���݂̓G�̏�Ԃ��m�b�N�o�b�N��ԂƂ���
			mpEnemy[i]->GetStateKnockBack()->Reset();//�A���U���Ή��p		

			//��U���̃_���[�W��^����
			int damageNum(pPlayer->GetAttackEnemy()->GetHand()->GetDamage());

			bool breakjuge=mpEnemy[i]->Damage(damageNum);

			//�����G��|���Ă�����
			if (breakjuge)
			{
				//���j���ǉ�
				mNowEnemyBreakNum++;
				
				//�X�R�A�𑝂₵��
				mpAdministrator->DirectAcceserScore()->SetScoreUp(ENEMY_SCORE);
			}
			//�|���ĂȂ�������_���[�W�l��\������
			else
			{
				//�G�t�F�N�g�����Z�b�g����
				mpEnemy[i]->ResetNumberEffect();

 				mpEnemy[i]->CreateNumberEffect(mpEnemy[i]->GetEnemyDamage());
			}
			
			//�G�t�F�N�g��ݒ肷��
			this->SetEnemyEffect(eEffectType::SLASH, mpEnemy[i]->GetBoxModel()->GetPosition(),i,true);

			//�m�b�N�o�b�N�̕������Z�o����
			DirectX::SimpleMath::Vector3 knockBackVelocity =
				pPlayer->GetAttackEnemy()->GetHand()->GetColliderPosition() - pPlayer->GetPlayerModel()->GetPosition();

			mpEnemy[i]->GetStateKnockBack()->SetMoveVector(knockBackVelocity);
			mpEnemy[i]->ChangeStateKnockBack();

			//�ǂ�������ԂƂ���
			mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::CHASING);
			mpEnemy[i]->SetPlayerChaseFlag(true);
		}
	}
}

/*==================================================
���_�ƓG�̏Փ˔���֐�
�����F���_�̃|�C���^
====================================================*/
void EnemyManager::ChackHitProtecterEnemy(Protecter* pProtecter)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	//�G�̐�������������
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),
			pProtecter->GetProtecterModel()->GetAABBCollider()))
		{
			//�G��j�󂷂�
			mpEnemy[i]->SelfDestroy();


			//�Ƃ̑ϋv�l�����炷
			pProtecter->SetDamageFlag(true);
		}
	}
}

/*======================================================================
�n��I�u�W�F�N�g�ƓG�̓����蔻��
�����F�n��I�u�W�F�N�g�Ǘ��N���X���̓����蔻��ЂƂ̃|�C���^
=======================================================================*/
void EnemyManager::ChackHitGroundObjectEnemy(AABB* pObjectCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum||
			mpEnemy[i]->GetMovePhaseNumber()==0)continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;

		//�������Ă����珈��������
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),	//�G�̓����蔻��
			pObjectCollider))								//�n��I�u�W�F�N�g�̓����蔻��
		{
			//�����m�b�N�o�b�N���󂯂Ă����ԂȂ��
			if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::KNOCK_BACK)
			{
				//������Ԃɖ߂���
				mpEnemy[i]->ChangeStateWalk();
			}
			//�����𔽓]������
			mpEnemy[i]->GetStateRotation()->ReverseRotEnemyModel();
			//���]���𑝂₷
			mpEnemy[i]->SetReverseNumUp();

		}
	}
}

/*======================================================================
��ƓG�̓����蔻��
�����F��̓����蔻��|�C���^
=======================================================================*/
void EnemyManager::ChackHitWallEnemy(AABB* pWallCollider)
{
	//�����蔻��֐��Q�̎擾
	Collider& pC = Collider::GetColliderInstance();

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)
		{
			continue;
		}
		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)
		{
			continue;
		}

		//�������Ă����珈��������
		if (pC.Intersect(
			mpEnemy[i]->GetBoxModel()->GetAABBCollider(),	//�G�̓����蔻��
			pWallCollider))									//�n��I�u�W�F�N�g�̓����蔻��
		{
			//�����𔽓]������
			mpEnemy[i]->GetStateRotation()->ReverseRotEnemyModel();
			
			//���]���𑝂₷
			mpEnemy[i]->SetReverseNumUp();
		}
	}
}

/*========================================
�댯�M�����C���ƓG�̓����蔻��
�����F�댯�M�����C���̃|�C���^
=========================================*/
bool EnemyManager::ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine)
{
	//�ȗ����p�ϐ��̐錾
	float enemyPositionZ = 0.f, linePositionZ = 0.f;


	//��������p�t���O�̐錾
	bool effectMoveFlag = false;

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���ł͂Ȃ��Ȃ�ʂ��Ȃ��B
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//�G�̌��݂̏�Ԃ��o����ԂȂ�Βʂ��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() == eStateEnemy::APPEARANCE ||
			mpEnemy[i]->GetStateEnemy() == eStateEnemy::BURIED)continue;


		//�t�F�[�Y���܂����ĂȂ���Ώ������s��Ȃ�
		//�w�肳�ꂽ�t�F�[�Y�ԍ���菬�����ԍ������̓G�̂ݕ`�悷��
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;


		//���W��ݒ肷��
		enemyPositionZ = mpEnemy[i]->GetBoxModel()->GetPosition().z;
		linePositionZ = pDangerousLine->GetLinePositionZ();

		//�����G�����C�����Ƒ��ɂ�����t���O�����Ă�
		if (enemyPositionZ > linePositionZ)
		{
			effectMoveFlag = true;
			//���鐔�͊֌W�Ȃ��̂Ŕ�����
			break;
		}
	}

	return effectMoveFlag;
}

/*========================================
�ΏۂƓG�̋�������
�����F�Ώۂ̍��W
=========================================*/
void EnemyManager::ChackDistanceTargetEnemy(DirectX::SimpleMath::Vector3 const& pos, bool playerFlag)
{
	//�Z�o�p�ϐ�
	float distance(0);

	//�����x�N�g���ۑ��p�ϐ�
	DirectX::SimpleMath::Vector3 distanceVelocity(DirectX::SimpleMath::Vector3::Zero);

	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���Ă��Ȃ���Ώ������s��Ȃ�
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//�ғ���ԂłȂ���Ώ������s��Ȃ�
		if (mpEnemy[i]->GetMovePhaseNumber() > mNowPhaseNum ||
			mpEnemy[i]->GetMovePhaseNumber() == 0)continue;

		//���s��ԂłȂ��Ȃ珈�����s��Ȃ�
		if (mpEnemy[i]->GetStateEnemy() != eStateEnemy::WALK)continue;

		//���ʂ������Ă��Ȃ���Ώ������s��Ȃ�
		if (mpEnemy[i]->GetAngleEnemy() != eAngleEnemy::STRAIGHT)continue;

		//�Ώۂ��v���C���[�Ńv���C���[��ǂ������Ă��Ȃ�������
		if (playerFlag && !mpEnemy[i]->GetPlayerChaseFlag())continue;


		//�������v������
		distance = std::sqrtf((std::abs(pos.x - mpEnemy[i]->GetBoxModel()->GetPosition().x)) * 2 +
						  (std::abs(pos.z - mpEnemy[i]->GetBoxModel()->GetPosition().z)) * 2);

		//��苗���Ԃɂ�����
		if (distance < ENEMY_CAPTURE_RANGE &&
			mpEnemy[i]->GetEnemyWalkState()== eEnemyWalkState::CHASING)
		{
			//���������߂�
			distanceVelocity = pos - mpEnemy[i]->GetBoxModel()->GetPosition();

			distanceVelocity.Normalize();		//���K��

			//�G�̈ړ����x��ݒ肷��
			mpEnemy[i]->GetStateWalk()->ChaseVelocitySet(distanceVelocity);


			mpEnemy[i]->GetStateWalk()->RotEnemyForTarget(pos);

		}
		//��苗���ɂ��炸�A�ǂ�������ԂȂ�
		else if (mpEnemy[i]->GetEnemyWalkState() == eEnemyWalkState::CHASING)
		{
			//�ʏ�ɖ߂�
			mpEnemy[i]->GetStateWalk()->ResetChaseVelocity();
			mpEnemy[i]->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

			//�v���C���[��ǂ������Ă������������
			if (mpEnemy[i]->GetPlayerChaseFlag())
			{
				mpEnemy[i]->SetPlayerChaseFlag(false);
			}
		}
	}
}

/*========================================
���Z�b�g����(�|�C���^�͕ێ�)
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
�ǂݍ��ރt�@�C�������쐬
�����F�X�e�[�W�ԍ�
�Ԃ�l�F�t�@�C����
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
�S�Ă̓G�̏Փ˔���t���O���~�낷����
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
�S�Ă̓G�����S�������Ƃ��m�F����t���O
==========================================*/
bool EnemyManager::AllEnemyDeathFlag()
{
	//���݂̃t�F�[�Y���ő�t�F�[�Y�o�Ȃ��Ȃ�Ώ�����ʂ��Ȃ�
	if (mNowPhaseNum != mMaxPhaseNum)
	{
		return false;
	}

	//�G�̐������s��
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		
		//�g�p���Ă���G��������
		if (mpEnemy[i]->GetEnemyUseFlag())
		{
			//false��Ԃ�
			return false;
		}
	}
	//�����ɗ���==�S�Ă̓G�����g�p��Ԃ̏ꍇ
	return true;
}

/*===================================================================
�Ώۂ̒e�ԍ������G�̒e�ԍ�������������:private
�����F�e�̗v�f�ԍ�
===================================================================*/
void EnemyManager::ResetBulletNum(int const& bulletIndex)
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�ԍ������ł����ԍ��Ɠ����Ȃ��
		if (mpEnemy[i]->GetSaveBulletNumber() == bulletIndex)
		{
			//�ԍ�������������
			mpEnemy[i]->SetSaveBulletNumber(Utility::EXCEPTION_NUM);
		}
	}
}

/*==================================
�����Ă���G����Ăɔ��j������
===================================*/
void EnemyManager::ExplosionSimultaneousEnemy()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//�g�p���Ă��Ȃ���Ώ������s��Ȃ�
		if (!(mpEnemy[i]->GetEnemyUseFlag()))continue;

		//�G�t�F�N�g��ݒ肷��
		this->SetEnemyEffect(eEffectType::BOMB, mpEnemy[i]->GetBoxModel()->GetPosition(), i);
		mpEnemy[i]->SelfDestroy();
	}
}

/*===================================
�t�@�C����������擾����:private
�����F�t�@�C���p�X�A�J�����ւ̃|�C���^
===================================*/
void EnemyManager::LoadFile(std::string filepath,CameraBase* camera)
{
	//������
	DirectX::SimpleMath::Vector3 pos= NOT_SET_ENEMY_POSITION;
	int phasenum = 0;


	//���ǂݍ���
	mpEnemyCall->LoadInfo(filepath);

	//�T�C�Y�����߂Ďw��
	mpEnemy.resize(mpEnemyCall->GetEnemyStructerSize());

	//����
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		//��񂪍ő�T�C�Y�ɂȂ�����(����ȏ�G��񂪂Ȃ����)
		if (i == mpEnemyCall->GetEnemyStructerSize()) 
		{
			//for���𔲂���B
			break;
		}
		pos = mpEnemyCall.get()->GetEnemyStructer(i).mVectorESPosition;
		phasenum = mpEnemyCall.get()->GetEnemyStructer(i).mPhaseNumber;
		mpEnemy[i]->SetMovePhaseNumber(phasenum);
		mpEnemy[i]->Initialize(pos, camera);
	}

	//�s�v�ɂȂ����̂ō폜
	mpEnemyCall->Reset();
}


/*========================================================================
�G�t�F�N�g��ݒ肷��:private
�����F�G�t�F�N�g�̎�ށA�G�̍��W�A
		�G�̗v�f�ԍ��A�G�t�F�N�g�t���O�����Ă邩(true�F���Ă�)
========================================================================*/
void EnemyManager::SetEnemyEffect(eEffectType type, DirectX::SimpleMath::Vector3 pos,
								int index,bool flagOn)
{
	//�G�t�F�N�g�}�l�[�W���[�̎擾
	auto pEM = EffectManager::GetInstance();

	auto effect = pEM->GetEffect(type);
	effect->SetPosition(pos + EFFECT_SHIFT_POSITION);
	effect->SetSpriteFlag(true);
	effect->SetLoopFlag(false);

	if (flagOn)
	{
		//�G�t�F�N�g���ғ����ɂ���
		mpEnemy[index]->SetEffectFlag(true);
		mpEnemy[index]->SetSpriteFlagAddress(effect->GetSpriteFlagAddress());
	}
}


/*===================================================
�S�Ẵu�[�������ڐG�t���O������:private
===================================================*/
void EnemyManager::ResetBoomerangHitFlag()
{
	for (int i = 0; i < static_cast<int>(mpEnemy.size()); i++)
	{
		mpEnemy[i]->SetBoomerangHitFlag(false);
	}
}