/*
��������e�̈ړ�����
�쐬���F2021/10/16
*/

#pragma once


//���N���X
#include"BulletStateBase.h"


class BulletStateExplosion :public BulletStateBase
{
private:
	//�d�͒萔
	static const float GRAVITY;

	//�������x
	static const float FIRST_VELOCITY;

	//�ŏ��̍���
	static const float FIRST_HEIGHT;

	//�G�t�F�N�g���o����������W
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;



	//���x
	float mBulletVelocity;
	//����
	float mBulletHeight;

public:
	//�R���X�g���N�^
	BulletStateExplosion();

	//�f�X�g���N�^
	~BulletStateExplosion()override = default;

	//�ړ�����
	bool Move()override;

	//�`�揈��
	void Draw()override;

private:
	//���Z�b�g����
	void Reset();
};