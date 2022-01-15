/*
���e�N���X
�쐬���F2021/10/14
*/
#pragma once

//���N���X
#include"WeaponBase.h"

//����
#include"../FlatPolygon.h"

class WeaponBomb:public WeaponBase
{
private:

	//���f���̊g�嗦
	static const DirectX::SimpleMath::Vector3 BOMB_MODEL_SCALE;

	//���ˈʒu�̒���
	static const DirectX::SimpleMath::Vector3 BOMB_SHOT_SHIFT_POSITION;

	//�w���z
	static const int BOMB_PRICE;

	//�w�����̑��e��
	static const int BOMB_MAX_BULLET_NUM;

	//�������x
	static const float FIRST_VELOCITY;

	//�ŏ��̍���
	static const float FIRST_HEIGHT;

	//�e�̑��x
	static const float BULLET_VELOCITY;

	//���j���鍂��
	static const float BOMB_MIN_HEIGHT;

	//�e
	std::unique_ptr<FlatPolygon> mpShadow;

public:

	//�R���X�g���N�^
	WeaponBomb();
	//�f�X�g���N�^
	~WeaponBomb()override;
	//����������
	void Initialize()override;
	//���Z�b�g����
	void Reset()override;
	//�`�揈��
	void Draw()override;
	//�e���ˏ���
	void Shot()override;
	//�w���z��Ԃ�
	int GetWeaponPrice()const override  { return BOMB_PRICE; }

private:
	//���f���̏����ݒ�
	void ModelInit();

	//�����n�_�\��
	DirectX::SimpleMath::Vector3 FallPoint();
};
