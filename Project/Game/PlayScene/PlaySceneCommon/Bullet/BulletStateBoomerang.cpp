/*
��{�I�Ȓe�̈ړ�����
�쐬���F2021/10/16
*/

#include"pch.h"
#include "BulletStateBoomerang.h"

//�O���錾
#include"Bullet.h"

//�֐��̎g�p
#include"../ObjectModel/SphereModel.h"
#include"../Player/Player.h"
#include"../ObjectModel/BoxModel.h"

//���ł�������
const float BulletStateBoomerang::BOOMERANG_FLY_DISTANCE = 20.f;

//��؎���
const int BulletStateBoomerang::BOOMERANG_STAGNATION = 1;

//���W�ŏ��l
const float BulletStateBoomerang::BULLET_MIN_POSITION_Z = 16.f;

//��]���x
const float BulletStateBoomerang::BULLET_ROT_VELOCITY = 12.f;

//���x���ފ���
const float BulletStateBoomerang::BULLET_VELOCITY_DECLINE = 0.98f;

//�Œᑬ�x
const float BulletStateBoomerang::BULLET_MIN_VELOCITY = -0.1f;


/*==================
�X�V����
==================*/
BulletStateBoomerang::BulletStateBoomerang()
	:
	BulletStateBase(),
	mState(eBoomerangState::NONE),
	mFlyDistance(0.f),
	mBoomerangAngle(DirectX::SimpleMath::Vector3::Zero),
	mpPlayer(nullptr),
	mpTimer(nullptr),
	mOutOfRangeFlag(false),
	mFlyDistanceNum(0)
{
	mpTimer = std::make_unique<Timer>();
}

/*===============================
�ړ�����
�Ԃ�l�F���W���E�l
(true:������	false �F�܂�)
===============================*/
bool BulletStateBoomerang::Move()
{
	//��]����
	this->RotBullet();

	//��Ԃɉ����ď�����ύX����
	switch (mState)
	{
		case eBoomerangState::NONE:
		{
			//���Z�b�g����
			this->Reset();

			mBoomerangVelocity = -BulletStateBase::GetBullet()->GetBulletVelocity();
			mBoomerangAngle = DirectX::SimpleMath::Vector3(0.f,0.f, mBoomerangVelocity);

			//��������
			mState = eBoomerangState::SHOT;

			break;
		}
		case eBoomerangState::SHOT:
		{
			//�ݒ�̋�����Ԃ܂ł�
			if (mFlyDistance < mFlyDistanceNum)
			{
				//�����𑝂₷
				mFlyDistance += -mBoomerangVelocity;

				//���x���ޏ���
				this->SlowDown();

				//���W�֔��f
				BulletStateBase::GetBullet()->GetBulletModel()->Move(mBoomerangAngle);
			}
			//�����ɓ��B������
			else
			{
				mFlyDistanceNum = 0;

				//��؏�����
				mState = eBoomerangState::CALCULATION;
			}


			break;
		}
		case eBoomerangState::CALCULATION:		//�v���C���[�Ƃ̌������v�Z����
		{
			//�����p�ϐ���錾
			DirectX::SimpleMath::Vector3 distanceAngle = DirectX::SimpleMath::Vector3::Zero,pos1,pos2;

			//�v�Z
			pos1 = BulletStateBase::GetBullet()->GetBulletModel()->GetPosition();
			pos2 = mpPlayer->GetPlayerModel()->GetPosition();
			distanceAngle = pos1 - pos2;

			//���K��
			distanceAngle.Normalize();			

			//�^�C�}�[�̍X�V
			mpTimer->Update();

			//�ő厞�ԂƂȂ�����
			if (mpTimer->GetMainTimer() == mpTimer->GetMaxTime())
			{
				mBoomerangAngle = distanceAngle * DirectX::SimpleMath::Vector3(mBoomerangVelocity, mBoomerangVelocity, mBoomerangVelocity);
				//�Ԃ��Ă��鏈����
				mState = eBoomerangState::RETURN;
			}
		
			break;
		}
		case eBoomerangState::RETURN:
		{
			//���x���ޏ���
			this->SlowDown();

			//���W�֔��f
			BulletStateBase::GetBullet()->GetBulletModel()->Move(mBoomerangAngle);

			//�����ő�l���}������
			if (BulletStateBase::GetBullet()->GetBulletModel()->GetPosition().z >= BULLET_MIN_POSITION_Z)
			{
				//�Ԃ��Ă��鏈����
				mState = eBoomerangState::NONE;
				mOutOfRangeFlag = true;
				return true;
			}

			break;
		}
		case eBoomerangState::CATCH:
		{

			//���Z�b�g��������
			this->Reset();

			//�v���C���[�Ɏ�������
			BulletStateBase::GetBullet()->GetBulletModel()->
				SetPosition(mpPlayer->GetPlayerModel()->GetPosition());

			break;
		}
	}
	return false;
}

/*==================
���Z�b�g����
==================*/
void BulletStateBoomerang::Reset()
{
	//��؎��Ԃ̏�����
	mpTimer->SetMaxTime(BOOMERANG_STAGNATION);
	mpTimer->ResetMainTimer();
	mFlyDistance = 0.f;
	mOutOfRangeFlag = false;
	mBoomerangAngle = DirectX::SimpleMath::Vector3::Zero;
	mBoomerangVelocity = 0.f;
	BulletStateBase::GetBullet()->GetBulletModel()->SetRotationY(0);
}

/*=========================
�򋗗��ǉ�:private
==========================*/
void BulletStateBoomerang::DistanceAddValue()
{
	if (BulletStateBase::GetBullet() == nullptr)
	{
		return;
	}

	if (mState == eBoomerangState::SHOT || mState == eBoomerangState::NONE)
	{
		mFlyDistanceNum += BulletStateBase::GetBullet()->GetBulletVelocity();
	}

	//�ő勗���͒萔
     mFlyDistanceNum = std::min(mFlyDistanceNum, BOOMERANG_FLY_DISTANCE);

}

/*==========================
�e�̉�]����:private
==========================*/
void BulletStateBoomerang::RotBullet()
{
	if (mState != eBoomerangState::CATCH)
	{
		//�e�̉�]����
		BulletStateBase::GetBullet()->GetBulletModel()->SetRotationY
		(
			BulletStateBase::GetBullet()->GetBulletModel()->GetRotAngleY() + BULLET_ROT_VELOCITY
		);
	}
}

/*========================
���x���ޏ���:private
==========================*/
void BulletStateBoomerang::SlowDown()
{
	//�����������Ȃ����
	if (mBoomerangAngle.z<BULLET_MIN_VELOCITY)
	{
		//���x�̋������ޏ���
		mBoomerangAngle *= BULLET_VELOCITY_DECLINE;
	}
}
