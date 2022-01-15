/*
���P�����N���X
�쐬���F2021/10/14
*/
#include"pch.h"
#include"WeaponRocketLauncher.h"


//�֐��̎g�p
#include"../Bullet/BulletManager.h"
#include"../ObjectModel/ObjectModel.h"

//�T�E���h�֌W
#include"Libraries/MyLibraries/Adx2.h"
#include "Libraries/MyLibraries/CueSheet_0.h"


//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 WeaponRocketLauncher::ROCKETLUNCHER_MODEL_SCALE(1.5f,1.5f,1.5f);

//���ˈʒu�̒���
const DirectX::SimpleMath::Vector3 WeaponRocketLauncher::ROCKETLUNCHER_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//�w���z
const int WeaponRocketLauncher::ROCKETLUNCHER_PRICE = 5500;

//�w�����̑��e��
const int WeaponRocketLauncher::ROCKETLUNCHER_MAX_BULLET_NUM = 4;

/*===================================
�R���X�g���N�^
===================================*/
WeaponRocketLauncher::WeaponRocketLauncher()
	:
	WeaponBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponRocketLauncher::~WeaponRocketLauncher()
{
}

/*===================================
����������
===================================*/
void WeaponRocketLauncher::Initialize()
{
	//���f���̏����ݒ�
	this->ModelInit();

	//���Z�b�g����
	this->Reset();
}

/*===================================
���Z�b�g����
===================================*/
void WeaponRocketLauncher::Reset()
{
	WeaponBase::SetBulletNum(ROCKETLUNCHER_MAX_BULLET_NUM);
}

/*==================================
�`�揈��
===================================*/
void WeaponRocketLauncher::Draw()
{
	//���f����`�悷��
	WeaponBase::GetWeaponModel()->Draw();
}

/*===================================
�e���ˏ���
�Ԃ�l�F���ː��������s��(true :����)
===================================*/
void WeaponRocketLauncher::Shot()
{

	//�T�E���h�Đ������擾����
	ADX2& pSound = ADX2::GetInstance();

	//�e�𐶐�����
	bool shotflag= WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + ROCKETLUNCHER_SHOT_SHIFT_POSITION
	);

	//�������˂ł����
	if (shotflag)
	{
		//�e�������炷
		WeaponBase::ReduceBulletNum();
		
		pSound.Play(CRI_CUESHEET_0_SE_SHOT_ROCKETLAUNCHER);
	}
}


/*===================================
���f���̏����ݒ�:private
===================================*/
void WeaponRocketLauncher::ModelInit()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("RocketLauncher");

	//���f���̐ݒ�
	WeaponBase::GetWeaponModel()->SetModel(model);


	//���f���̊g�嗦
	WeaponBase::GetWeaponModel()->SetScale(ROCKETLUNCHER_MODEL_SCALE);
}
