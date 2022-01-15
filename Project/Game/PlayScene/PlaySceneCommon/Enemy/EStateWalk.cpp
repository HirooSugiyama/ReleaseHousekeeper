/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/

#include"pch.h"
#include "EStateWalk.h"

//�O���錾
#include"Enemy.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"


//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
const DirectX::SimpleMath::Vector3 EStateWalk::ESTATE_COLLIDER_POSITION(0.f,0.f,1.f);

//�g�嗦(�����蔻��)
const DirectX::SimpleMath::Vector3 EStateWalk::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//�ړ����x
const float EStateWalk::ENEMY_MOVE_SPEED = 0.03f;

//���f���p�x
const float EStateWalk::ESTATE_MODEL_ANGLE_STRAIGHT = 180.f;
const float EStateWalk::ESTATE_MODEL_ANGLE_RIGHT = 270.f;
const float EStateWalk::ESTATE_MODEL_ANGLE_LEFT = 90.f;

/*============================
�R���X�g���N�^
============================*/
EStateWalk::EStateWalk()
	:
	EnemyStateBase(),
	mpWalkCollider(nullptr),
	mpEnemy(nullptr),
	mChaseVelocity(DirectX::SimpleMath::Vector3::Zero)
{
	mpWalkCollider = std::make_unique<AABB>();
}

/*============================
�f�X�g���N�^
============================*/
EStateWalk::~EStateWalk()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateWalk::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;
}

/*============================
�X�V����
============================*/
void EStateWalk::Update()
{
	//��Ԃɉ����ď�����ύX����
	switch (mpEnemy->GetEnemyWalkState())
	{
		case eEnemyWalkState::GENERALLY:
		{
			//�ϊ��p�ϐ��̐錾
			DirectX::SimpleMath::Vector3 vel;

			//�G�̍������Ă�������ɉ����ď������s��
			switch (mpEnemy->GetAngleEnemy())
			{
				case eAngleEnemy::STRAIGHT:
				{
					vel.z = ENEMY_MOVE_SPEED;	//Z�����ɓ�����
					break;
				}
				case eAngleEnemy::LEFT:
				{
					vel.x = -ENEMY_MOVE_SPEED;	//-X�����ɓ�����
					break;
				}
				case eAngleEnemy::RIGHT:
				{
					vel.x = ENEMY_MOVE_SPEED;	//X�����ɓ�����
					break;
				}
			}

			//���f�����ړ�������
			mpEnemy->GetBoxModel()->Move(vel);

			break;
		}
		case eEnemyWalkState::CHASING:
		{
			if (mChaseVelocity == DirectX::SimpleMath::Vector3::Zero)
			{
				mpEnemy->SetEnemyWalkState(eEnemyWalkState::GENERALLY);
			}
				
			//���f�����ړ�������
			mpEnemy->GetBoxModel()->Move(mChaseVelocity);

			break;
		}
	}

	//�����蔻����X�V����
	this->SetAABBCollider();
}

/*============================
State�J�n���̏���������
============================*/
void EStateWalk::Reset()
{

}

/*==========================
�����蔻��̃A�N�Z�T
============================*/
AABB* EStateWalk::GetCollider()const
{
	return mpWalkCollider.get();
}

/*==============================================
�ǂ������p�ړ����x�ۑ��ϐ��̐ݒ�
==============================================*/
void EStateWalk::ChaseVelocitySet(DirectX::SimpleMath::Vector3 vel)
{
	mChaseVelocity.x = vel.x*ENEMY_MOVE_SPEED;
	mChaseVelocity.z = vel.z*ENEMY_MOVE_SPEED;
}

/*=====================
������ύX����
�����F�Ώۂ̍��W
======================*/
void EStateWalk::RotEnemyForTarget(DirectX::SimpleMath::Vector3 targetpos)
{
	//���S�_
	DirectX::SimpleMath::Vector3 nierPosition = targetpos;
	//���S�_���獡�̂���ʒu�̃x�N�g��
	DirectX::SimpleMath::Vector3 toVec = nierPosition - mpEnemy->GetBoxModel()->GetPosition();

	//�����A�Ώۂ��G��艜�ɂ����ԂȂ�ΓG�͒��i�Ƃ���
	if (toVec.z <= 0)
	{
		mpEnemy->GetBoxModel()->SetRotationY(180.f);
		mpEnemy->SetEnemyWalkState(eEnemyWalkState::GENERALLY);

		//�v���C���[��ǂ������Ă������������
		if (mpEnemy->GetPlayerChaseFlag())
		{
			mpEnemy->SetPlayerChaseFlag(false);
		}
	}
	else
	{
		//�@���x�N�g��
		DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Left;
		//�Ȃ��p
		float angle = std::acosf(toVec.Dot(vel) / (toVec.Length() * vel.Length()));
		angle = DirectX::XMConvertToDegrees(angle) + ESTATE_MODEL_ANGLE_LEFT;
		//�Ȃ��p�����f���̊p�x�ɂ���
		mpEnemy->GetBoxModel()->SetRotationY(angle);
	}	
}

/*============================
������������
============================*/
void EStateWalk::ResetEnemyAngle()
{
	//�G�̍������Ă�������ɉ����ď������s��
	switch (mpEnemy->GetAngleEnemy())
	{
		case eAngleEnemy::STRAIGHT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_STRAIGHT);
			break;
		}
		case eAngleEnemy::LEFT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_LEFT);
			break;
		}
		case eAngleEnemy::RIGHT:
		{
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_MODEL_ANGLE_RIGHT);
			break;
		}
	}
}


/*============================
�����蔻���ݒ肷��:private
============================*/
void EStateWalk::SetAABBCollider()
{
	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 min, max;

	//�؂����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 pos, scale;

	//�ȗ���
	pos = mpEnemy->GetBoxModel()->GetPosition() + ESTATE_COLLIDER_POSITION;
	scale = ESTATE_COLLIDER_SCALE;
	

	//�����蔻��̍��W���Z�o
	min = pos - scale;
	max = pos + scale;

	//�����蔻���������
	mpWalkCollider->SetCollider(min,max);
}

/*===========================================================
�͈͓��Ɏ��߂�:private
�����F��r����l�A�ŏ��l�A�ő�l
�Ԃ�l�F�C����̒l
=============================================================*/
float EStateWalk::Clamp(float const& num, float const& minNum, float const& maxNum)const
{
	if (num < minNum)
	{
		return minNum;
	}
	else if (num > maxNum)
	{
		return maxNum;
	}
	else
	{
		return num;
	}
}
