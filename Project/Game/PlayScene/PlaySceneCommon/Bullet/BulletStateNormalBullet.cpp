/*
��{�I�Ȓe�̈ړ�����
�쐬���F2021/10/16
*/

#include"pch.h"
#include "BulletStateNormalBullet.h"

//�O���錾
#include"Bullet.h"

//�֐��̎g�p
#include"../../PlaySceneCommon/ObjectModel/SphereModel.h"

/*==================
�R���X�g���N�^
==================*/
BulletStateNormalBullet::BulletStateNormalBullet()
	:
	BulletStateBase()
{
}

/*=======================================
�ړ�����
�Ԃ�l�F������͖��g�p(��State��Ŏg�p)
=======================================*/
bool BulletStateNormalBullet::Move()
{
	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 movevel =
		DirectX::SimpleMath::Vector3(0.f, 0.f, -BulletStateBase::GetBullet()->GetBulletVelocity());

	//���W�֔��f
	BulletStateBase::GetBullet()->GetBulletModel()->Move(movevel);

	return false;
}
