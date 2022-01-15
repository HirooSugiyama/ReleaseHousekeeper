/*
�v���C���[�̍s����ԕ����X�e�[�g�p�^�[��
�쐬���F2021/09/14
*/

#include"pch.h"
#include "ActionStateAttackEnemy.h"


//�O���錾
#include"../Weapon/WeaponBase.h"
#include"../Weapon/WeaponManager.h"
#include"../Bullet/BulletManager.h"
#include"../../../UI/UI.h"

//�֐������̉{���̂��ߎg�p
#include"../ObjectModel/BoxModel.h"
#include"../Bullet/BulletStateBoomerang.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//�v���C���[�̍��W�ƕ��탂�f���̍��W�̍�
const DirectX::SimpleMath::Vector3 ActionStateAttackEnemy::WEPON_MODEL_PLAYER_SHIFT_POSITION(0.5f, 0.f, -1.f);


/*=====================================
�R���X�g���N�^
=====================================*/
ActionStateAttackEnemy::ActionStateAttackEnemy()
	:
	ActionStateBase(),
	mpHand(nullptr),
	mpStrongWeapon(nullptr),
	mpPlayer(nullptr),
	mpWeaponManager(nullptr),
	mpBulletManager(nullptr),
	mAttackState(eAttackState::WEEK_ATTACK),
	mUseWeapon(eWeaponType::NONE),
	mAttackFlag(false),
	mMachinGunSEID(Utility::EXCEPTION_NUM)
{
	//��U���͌Œ蕐��
	mpHand = std::make_unique<WeaponHand>();
}

/*=====================================
�f�X�g���N�^
=====================================*/
ActionStateAttackEnemy::~ActionStateAttackEnemy()
{

}

/*=====================================
����������
�����F�v���C���[�̃|�C���^
=====================================*/
void ActionStateAttackEnemy::Initialize(Player* pPlayer)
{
	//�|�C���^�̕ۑ�
	mpPlayer = pPlayer;
	mpHand->SetPlayerPointer(mpPlayer);

	//�e�U�������̏�����
	mpHand->Initialize();
}

/*=====================================
�X�V����
=====================================*/
void ActionStateAttackEnemy::Update()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	//���݂̏�Ԃɉ������������s��
	switch (mAttackState)
	{
		case eAttackState::NONE: {break;}

		//��U���̏ꍇ
		case eAttackState::WEEK_ATTACK:
		{
			//������U���̓��͂�����A�ҋ@��ԂȂ�
			if ((pKey->ActionWeekAttack()|| pGamePad->ActionPlayer()) && mpHand->GetAttackFlag()== eHandState::STAND_BY)
			{	
				//�e�U�������̍X�V����
				mpHand->SetAttackFlag(eHandState::ATTACK);
				ADX2::GetInstance().Play(CRI_CUESHEET_0_SE_ATTACK_NORMALATTACK);
			}
			//�X�V�����͏펞�ʂ�
			mpHand->Update();

			break;
		}
		//���U���̏ꍇ
		case eAttackState::STRONG_ATTACK:
		{
			//�����U���̏������s��
			this->StrongWeaponAttack();

			if (mpStrongWeapon == nullptr)
			{
				//�摜���ς���
				mAttackState = eAttackState::WEEK_ATTACK;

				mpPlayer->GetUIPointer()->ChangeActionInfoTexture(eWeaponType::NONE);
			}

			mpHand->SetCollider(true);

			break;
		}

	}

	//����؂�ւ�����
	this->ChangeStrongHand();
}

/*=====================================
State�J�n���̏���������
=====================================*/
void ActionStateAttackEnemy::Reset()
{
	
}

/*===================================
�`�揈��
=====================================*/
void ActionStateAttackEnemy::Draw()
{
	//���݂̏�Ԃɉ������������s��
	switch (mAttackState)
	{
		case eAttackState::NONE: {break; }

		//��U���̏ꍇ					
		case eAttackState::WEEK_ATTACK:
		{
			mpHand->Draw();

			break;
		}
		//���U���̏ꍇ
		case eAttackState::STRONG_ATTACK:
		{
			//����`��
			mpStrongWeapon->SetPosition(mpPlayer->GetPlayerModel()->GetPosition() + WEPON_MODEL_PLAYER_SHIFT_POSITION);
			mpStrongWeapon->Draw();

			break;
		}
	}
}

/*===========================
��������������ς���
=============================*/
void ActionStateAttackEnemy::ChangeStrongWeapon(eWeaponType const& weapon)
{
	//�������Ă��镐���ς���
	mUseWeapon = weapon;
	mpStrongWeapon = mpWeaponManager->GetWeapon(weapon);

	//��������Z�b�g����
	mpStrongWeapon->Reset();

	mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());

	//�e��Ή������e�ɕύX����
	mpBulletManager->SetWeaponType(mUseWeapon);
}

/*=====================================
�������������
=====================================*/
void ActionStateAttackEnemy::UseStrongWeapon()
{
	mAttackState = eAttackState::STRONG_ATTACK;
}

/*=====================================
���㕐��̐؂�ւ�:private
=====================================*/
void ActionStateAttackEnemy::ChangeStrongHand()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	if (pKey->SwitchToWeapon()|| pGamePad->ChangePlayerWeapon())
	{
		//��U����ԂȂ��
		if (mAttackState == eAttackState::WEEK_ATTACK)
		{
			//���e�������Ă���ꍇ�̂ݕύX����
			if (mpStrongWeapon != nullptr)
			{
				this->UseStrongWeapon();
				//�摜���ς���
				mpPlayer->GetUIPointer()->ChangeActionInfoTexture(mUseWeapon);
			}
		}
		else
		{
			mAttackState = eAttackState::WEEK_ATTACK;

			//�摜���ς���
			mpPlayer->GetUIPointer()->ChangeActionInfoTexture(eWeaponType::NONE);
		}
	}
}

/*=====================================
�����U���̍U������:private
=====================================*/
void ActionStateAttackEnemy::StrongWeaponAttack()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	//�T�E���h�Đ������擾����
	ADX2& pSound = ADX2::GetInstance();

	bool shotFlag = false;

	switch (mUseWeapon)
	{
		case eWeaponType::NONE:
		{
			//�������Ȃ�
			break;
		}
		case eWeaponType::MACHINE_GUN:
		{
			//�X�y�[�X����������Ă�����
			if (pKey->PressActionStrongAttack()|| pGamePad->ActionPlayer())
			{
				//�e���쐬����
				shotFlag = true;
				if (pSound.ChackPlay(mMachinGunSEID))
				{
					mMachinGunSEID = pSound.Play(CRI_CUESHEET_0_SE_SHOT_MACHINEGUN);
				}			
			}

			//�Đ����̏ꍇ�����~����
			else if (mMachinGunSEID != Utility::EXCEPTION_NUM)
			{
				pSound.Stop(mMachinGunSEID);
				mMachinGunSEID = Utility::EXCEPTION_NUM;
			}

			break;
		}
		case eWeaponType::BOMB:
		{
			//�X�y�[�X���P���������ꂽ��
			if (pKey->PushActionStrongAttack()||pGamePad->AttackStrongPlayer())
			{
				//�e���쐬����
				shotFlag = true;	

			}

			break;
		}
		case eWeaponType::ROCKET_LAUNCHER:
		{
			//�X�y�[�X���P���������ꂽ��
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//�e���쐬����
				shotFlag = true;

			}
			break;
		}
		case eWeaponType::PISTOL:
		{
			//�X�y�[�X���P���������ꂽ��
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//�e���쐬����
				shotFlag = true;
			}

			break;
		}
		case eWeaponType::BOOMERANG:
		{
			//�X�y�[�X���P���������ꂽ��
			if (pKey->PushActionStrongAttack() || pGamePad->AttackStrongPlayer())
			{
				//�e���쐬����
				shotFlag = true;
			}
			//�u�[��������p����
			this->BoomerangUpdate();

			break;
		}
	}
	if (shotFlag)
	{
 		mpStrongWeapon->Shot();

		//�c�e���\�����X�V
		mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());

		//�u�[�������ȊO�Ȃ�
		if (mUseWeapon != eWeaponType::BOOMERANG)
		{
			//�����e�؂�Ȃ��
			if (mpStrongWeapon->Destroy())
			{
				//�폜����
				mpStrongWeapon = nullptr;

				//�Đ����̏ꍇ�����~����
				if (mMachinGunSEID != Utility::EXCEPTION_NUM && mUseWeapon == eWeaponType::MACHINE_GUN)
				{
					pSound.Stop(mMachinGunSEID);
					mMachinGunSEID = Utility::EXCEPTION_NUM;
				}
			}
		}		
	}
	
}

/*====================================
�u�[��������p�����Fprivate
=====================================*/
void ActionStateAttackEnemy::BoomerangUpdate()
{
	//�����u�[����������O�ɏo����
	if (mpBulletManager->GetBoomerangBullet()->GetOutOfRangeFlag())
	{
		//�폜����
		mpStrongWeapon = nullptr;
		mpBulletManager->GetBoomerangBullet()->Reset();
	}

	if (mpBulletManager->GetBoomerangBullet()->GetBoomerangState() == eBoomerangState::CATCH)
	{
		//��������Z�b�g����
		mpStrongWeapon->Reset();
		mpPlayer->GetUIPointer()->SetActionInfoStrongBulletNum(mpStrongWeapon->GetBulletNum());
	}
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->PressActionStrongAttack()|| pGamePad->ActionPlayer())
	{
		mpBulletManager->GetBoomerangBullet()->DistanceAddValue();
	}
}
