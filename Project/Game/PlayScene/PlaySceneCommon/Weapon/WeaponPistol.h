/*
�s�X�g���N���X
�쐬���F2021/10/14
*/
#pragma once

//���N���X
#include"WeaponBase.h"


class WeaponPistol:public WeaponBase
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 PISTOL_MODEL_SCALE;

	//���ˈʒu�̒���
	static const DirectX::SimpleMath::Vector3 PISTOL_SHOT_SHIFT_POSITION;

	//�w���z
	static const int PISTOL_PRICE;

	//�w�����̑��e��
	static const int PISTOL_MAX_BULLET_NUM;

public:

	//�R���X�g���N�^
	WeaponPistol();
	//�f�X�g���N�^
	~WeaponPistol()override;
	//����������
	void Initialize()override;
	//���Z�b�g����
	void Reset()override;
	//�`�揈��
	void Draw()override;
	//�e���ˏ���
	void Shot()override;
	//�w���z��Ԃ�
	int GetWeaponPrice()const override { return PISTOL_PRICE; }

private:
	//���f���̏����ݒ�
	void ModelInit();
};
