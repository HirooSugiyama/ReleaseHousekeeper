/*
�u�[�������N���X
�쐬���F2021/10/14
*/
#include"pch.h"
#include"WeaponBoomerang.h"

//�֐��̎g�p
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"
#include"../Bullet/BulletStateBoomerang.h"


//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 WeaponBoomerang::BOOMERANG_MODEL_SCALE(1.5f,1.5f,1.5f);

//���ˈʒu�̒���
const DirectX::SimpleMath::Vector3 WeaponBoomerang::BOOMERANG_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//�w���z
const int WeaponBoomerang::BOOMERANG_PRICE = 1000;

//�w�����̑��e��
const int WeaponBoomerang::BOOMERANG_MAX_BULLET_NUM = 1;

/*===================================
�R���X�g���N�^
===================================*/
WeaponBoomerang::WeaponBoomerang()
	:
	WeaponBase(),
	mSecondFlag(false)
{
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponBoomerang::~WeaponBoomerang()
{
}

/*===================================
����������
===================================*/
void WeaponBoomerang::Initialize()
{
	//���f���̏����ݒ�
	this->ModelInit();

	//���Z�b�g����
	this->Reset();
}

/*===================================
���Z�b�g����
===================================*/
void WeaponBoomerang::Reset()
{
	//���e���̏�����
	WeaponBase::SetBulletNum(BOOMERANG_MAX_BULLET_NUM);
}

/*=================================
�`�揈��
===================================*/
void WeaponBoomerang::Draw()
{
	//�܂��e��\�����Ă��Ȃ�������
	if (!mSecondFlag)
	{
		//���f����`�悷��
		WeaponBase::GetWeaponModel()->Draw();
	}
}

/*===================================
�e���ˏ���
�Ԃ�l�F���ː��������s��(true :����)
===================================*/
void  WeaponBoomerang::Shot()
{

	//�e���˂�1��ڂȂ�
	if (!mSecondFlag)
	{
		bool shotFlag = WeaponBase::GetBulletManager()->Create
		(
			WeaponBase::GetWeaponModel()->GetPosition() + BOOMERANG_SHOT_SHIFT_POSITION
		);
		//�������˂ł����
		if (shotFlag)
		{
			//���ł̂�2���
			mSecondFlag = true;

			//�e�������炷
			WeaponBase::ReduceBulletNum();
		}
	}
	else if(WeaponBase::GetBulletManager()->GetBoomerangBullet()->
			GetBoomerangState()== eBoomerangState::CATCH)
	{
		//���ɂ���e�𔭎ˏ�ԂƂ���
		WeaponBase::GetBulletManager()->GetBoomerangBullet()->
			ChangeBoomerangState(eBoomerangState::NONE);


		//�^�C�}�[�͋N������
		WeaponBase::GetBulletManager()->ResetIntervalTimer();

		//�e�������炷
		WeaponBase::ReduceBulletNum();
	}
}

/*===================================
���f���̏����ݒ�:private
===================================*/
void WeaponBoomerang::ModelInit()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Boomerang");

	//���f���̐ݒ�
	WeaponBase::GetWeaponModel()->SetModel(model);


	//���f���̊g�嗦
	WeaponBase::GetWeaponModel()->SetScale(BOOMERANG_MODEL_SCALE);
}

