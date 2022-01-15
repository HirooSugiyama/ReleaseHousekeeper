/*
����Ǘ��N���X
�쐬���F2021/09/14
*/
#pragma once

//�񋓌^�̎g�p
#include"WeaponeType.h"

#include"WeaponMachineGun.h"
#include"WeaponBomb.h"
#include"WeaponBoomerang.h"
#include"WeaponPistol.h"
#include"WeaponRocketLauncher.h"


//�O���錾
class WeaponBase;			//�Ԃ�l�Ŏg�p
class BulletManager;		//�|�C���^�ۑ��֐��̈����Ŏg�p

class WeaponManager
{
private:

	//�e�핐��
	std::unique_ptr<WeaponMachineGun> mpWeaponmachineGun;
	std::unique_ptr<WeaponBomb> mpWeaponBomb;
	std::unique_ptr<WeaponBoomerang> mpWeaponBoomerang;
	std::unique_ptr<WeaponPistol> mpWeaponPistol;
	std::unique_ptr<WeaponRocketLauncher> mpWeaponRocketLauncher;

public:
	//�R���X�g���N�^
	WeaponManager();
	//�f�X�g���N�^
	~WeaponManager();
	//������
	void Initialize(BulletManager* pBulletManager);

	//�����ύX���鏈��
	WeaponBase* GetWeapon(eWeaponType const& type);


};