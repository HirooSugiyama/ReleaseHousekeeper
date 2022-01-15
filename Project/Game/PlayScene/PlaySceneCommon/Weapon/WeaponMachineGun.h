/*
�@�֏e�N���X
�쐬���F2021/09/06
*/
#pragma once

//���N���X
#include"WeaponBase.h"


class WeaponMachineGun:public WeaponBase
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 MACHINEGUN_MODEL_SCALE;

	//���ˈʒu�̒���
	static const DirectX::SimpleMath::Vector3 MACHINEGUN_SHOT_SHIFT_POSITION;

	//�w���z
	static const int MACHINEGUN_PRICE;

	//�w�����̑��e��
	static const int MACHINEGUN_MAX_BULLET_NUM;


public:

	//�R���X�g���N�^
	WeaponMachineGun();
	//�f�X�g���N�^
	~WeaponMachineGun()override;
	//����������
	void Initialize()override;
	//���Z�b�g����
	void Reset()override;
	//�`�揈��
	void Draw()override;
	//�e���ˏ���
	void Shot()override;
	//�w���z��Ԃ�
	int GetWeaponPrice()const override { return MACHINEGUN_PRICE; }

private:
	//���f���̏����ݒ�
	void ModelInit();
};
