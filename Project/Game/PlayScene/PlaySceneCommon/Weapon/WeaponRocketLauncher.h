/*
���P�����N���X
�쐬���F2021/10/14
*/
#pragma once

//���N���X
#include"WeaponBase.h"


class WeaponRocketLauncher:public WeaponBase
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 ROCKETLUNCHER_MODEL_SCALE;

	//���ˈʒu�̒���
	static const DirectX::SimpleMath::Vector3 ROCKETLUNCHER_SHOT_SHIFT_POSITION;

	//�w���z
	static const int ROCKETLUNCHER_PRICE;

	//�w�����̑��e��
	static const int ROCKETLUNCHER_MAX_BULLET_NUM;


public:

	//�R���X�g���N�^
	WeaponRocketLauncher();
	//�f�X�g���N�^
	~WeaponRocketLauncher()override;
	//����������
	void Initialize()override;
	//���Z�b�g����
	void Reset()override;
	//�`�揈��
	void Draw()override;
	//�e���ˏ���
	void Shot()override;
	//�w���z��Ԃ�
	int GetWeaponPrice()const override { return ROCKETLUNCHER_PRICE; }

private:
	//���f���̏����ݒ�
	void ModelInit();
};
