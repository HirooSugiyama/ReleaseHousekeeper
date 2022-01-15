/*
�u�[�������N���X
�쐬���F2021/10/14
*/
#pragma once

//���N���X
#include"WeaponBase.h"

class WeaponBoomerang:public WeaponBase
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 BOOMERANG_MODEL_SCALE;

	//���ˈʒu�̒���
	static const DirectX::SimpleMath::Vector3 BOOMERANG_SHOT_SHIFT_POSITION;
	
	//�w���z
	static const int BOOMERANG_PRICE;

	//�w�����̑��e��
	static const int BOOMERANG_MAX_BULLET_NUM;


	//2��ڈȍ~�̃t���O
	bool mSecondFlag;	//2��ڈȍ~�͒e���������Ȃ�����


public:

	//�R���X�g���N�^
	WeaponBoomerang();
	//�f�X�g���N�^
	~WeaponBoomerang()override;
	//����������
	void Initialize()override;
	//���Z�b�g����
	void Reset()override;
	//�`�揈��
	void Draw()override;
	//�e���ˏ���
	void Shot()override;
	//�w���z��Ԃ�
	int GetWeaponPrice()const override { return BOOMERANG_PRICE; }

	//2��ڃt���O������
	void DownSecondFlag() { mSecondFlag = false; }

private:
	
	//���f���̏����ݒ�
	void ModelInit();
};
