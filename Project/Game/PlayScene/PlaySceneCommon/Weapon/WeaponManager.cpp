/*
����Ǘ��N���X
�쐬���F2021/09/14
*/
#include"pch.h"
#include "WeaponManager.h"

//�O���錾
#include"WeaponBase.h"


/*===============================
�R���X�g���N�^
===============================*/
WeaponManager::WeaponManager()
	:
	mpWeaponmachineGun(nullptr),
	mpWeaponBomb(nullptr),
	mpWeaponBoomerang(nullptr),
	mpWeaponPistol(nullptr),
	mpWeaponRocketLauncher(nullptr)
{
	mpWeaponmachineGun = std::make_unique<WeaponMachineGun>();
	mpWeaponBomb = std::make_unique<WeaponBomb>();
	mpWeaponBoomerang = std::make_unique<WeaponBoomerang>();
	mpWeaponPistol = std::make_unique<WeaponPistol>();
	mpWeaponRocketLauncher = std::make_unique<WeaponRocketLauncher>();
}


/*===============================
�f�X�g���N�^
===============================*/
WeaponManager::~WeaponManager()
{
}


/*===============================
����������
�����F�e�Ǘ��N���X�̃|�C���^
===============================*/
void WeaponManager::Initialize(BulletManager* pBulletManager)
{
	//����������
	mpWeaponmachineGun->Initialize();
	mpWeaponBomb->Initialize();
	mpWeaponBoomerang->Initialize();
	mpWeaponPistol->Initialize();
	mpWeaponRocketLauncher->Initialize();

	//�|�C���^�ۑ�����
	mpWeaponmachineGun->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponBomb->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponBoomerang->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponPistol->
		SetBulletManagerPointer(pBulletManager);
	mpWeaponRocketLauncher->
		SetBulletManagerPointer(pBulletManager);

}


/*=========================================
�����ύX���鏈��
����	�F����̎��(��)
�Ԃ�l	�F�����ɉ���������̃|�C���^
=========================================*/
WeaponBase* WeaponManager::GetWeapon(eWeaponType const& type)
{
	//�����ɉ����ĕԂ����̂�ς���
	switch (type)
	{
		case eWeaponType::MACHINE_GUN:
		{
			return (WeaponBase*)mpWeaponmachineGun.get();
			break;
		}
		case eWeaponType::BOMB:
		{
			return (WeaponBase*)mpWeaponBomb.get();
			break;
		}
		case eWeaponType::ROCKET_LAUNCHER:
		{
			
			return (WeaponBase*)mpWeaponRocketLauncher.get();
			break;
		}
		case eWeaponType::PISTOL:
		{
			return (WeaponBase*)mpWeaponPistol.get();
			break;
		}
		case eWeaponType::BOOMERANG:
		{
			//������ԂȂ̂ł܂������ĂȂ����߁A2��ڃt���O�͍~�낷
			mpWeaponBoomerang->DownSecondFlag();
			return (WeaponBase*)mpWeaponBoomerang.get();
			break;
		}
	}
	return nullptr;
}
