/*
�@�֏e�N���X
�쐬���F2021/10/14
*/
#include"pch.h"
#include"WeaponMachineGun.h"


//�֐��̎g�p
#include"../ObjectModel/ObjectModel.h"
#include"../Bullet/BulletManager.h"

#include"../Bullet/BulletType.h"


//���f���̊g�嗦
const DirectX::SimpleMath::Vector3 WeaponMachineGun::MACHINEGUN_MODEL_SCALE(1.5f,1.5f,1.5f);

//���ˈʒu�̒���
const DirectX::SimpleMath::Vector3 WeaponMachineGun::MACHINEGUN_SHOT_SHIFT_POSITION(0.f,0.f,-2.3f);

//�w���z
const int WeaponMachineGun::MACHINEGUN_PRICE = 1500;

//�w�����̑��e��
const int WeaponMachineGun::MACHINEGUN_MAX_BULLET_NUM = 120;

/*===================================
�R���X�g���N�^
===================================*/
WeaponMachineGun::WeaponMachineGun()
	:
	WeaponBase()
{
}

/*===================================
�f�X�g���N�^
===================================*/
WeaponMachineGun::~WeaponMachineGun()
{

}

/*===================================
����������
===================================*/
void WeaponMachineGun::Initialize()
{
	//���f���̏����ݒ�
	this->ModelInit();

	//���Z�b�g����
	this->Reset();
}

/*===================================
���Z�b�g����
===================================*/
void WeaponMachineGun::Reset()
{
	//���e���̏�����
	WeaponBase::SetBulletNum(MACHINEGUN_MAX_BULLET_NUM);
}

/*===================================
�`�揈��
===================================*/
void WeaponMachineGun::Draw()
{
	//���f����`�悷��
	WeaponBase::GetWeaponModel()->Draw();
}

/*===================================
�e���ˏ���
�Ԃ�l�F���ː��������s��(true :����)
===================================*/
void WeaponMachineGun::Shot()
{
	//�e�𐶐�����
	bool shotFlag = WeaponBase::GetBulletManager()->Create
	(
		WeaponBase::GetWeaponModel()->GetPosition() + MACHINEGUN_SHOT_SHIFT_POSITION
	);

	//�������˂ł����
	if (shotFlag)
	{
		//�e�������炷
		WeaponBase::ReduceBulletNum();
	}
}


/*===================================
���f���̏����ݒ�:private
===================================*/
void WeaponMachineGun::ModelInit()
{
	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("MachineGun");

	//���f���̐ݒ�
	WeaponBase::GetWeaponModel()->SetModel(model);
	
	//���f���̊g�嗦
	WeaponBase::GetWeaponModel()->SetScale(MACHINEGUN_MODEL_SCALE);
}