/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/

#include"pch.h"
#include"EStateRotation.h"

//�O���錾
#include"Enemy.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"
#include"EStateAttack.h"
#include"EStateWalk.h"


//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
const DirectX::SimpleMath::Vector3 EStateRotation::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//�g�嗦(�����蔻��)
const DirectX::SimpleMath::Vector3 EStateRotation::ESTATE_COLLIDER_SCALE(0.25f, 0.125f, 0.125f);

//��]�X�s�[�h
const float EStateRotation::ESTATE_ROT_SPEED = 1.5f;


//�G�̌��݂̌�����\��
const int EStateRotation::ESTATE_ENEMY_ROT_STRAIGHT = 180;
const int EStateRotation::ESTATE_ENEMY_ROT_LEFT = 90;
const int EStateRotation::ESTATE_ENEMY_ROT_RIGHT = 270;


//���p
const float EStateRotation::RIGHT_ANGLE = 90.f;

//���W�̂��炷��
const int EStateRotation::ESTATE_ENEMY_SHIFT_POSITION_RANGE = 1;

/*============================
�R���X�g���N�^
============================*/
EStateRotation::EStateRotation()
	:
	EnemyStateBase(),
	mpRotationCollider(nullptr),
	mpEnemy(nullptr),
	mSaveRotation(),
	mChangeAfterAngle(eChangeAfterAngle::NONE)
{
	mpRotationCollider = std::make_unique<AABB>();
}

/*============================
�f�X�g���N�^
============================*/
EStateRotation::~EStateRotation()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateRotation::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;
}


/*============================
State�J�n���̏���������
============================*/
void EStateRotation::Reset()
{
}

/*============================
�����蔻��̃A�N�Z�T
============================*/
AABB* EStateRotation::GetCollider()const
{
	return mpRotationCollider.get();
}

/*===================================
���f���𔽓]������:private
====================================*/
void EStateRotation::ReverseRotEnemyModel()
{
	//���݂̃��f���̌������擾
	this->CalculationEnemyAngle();

	//���݂̓G�̃��f���̌����ɉ����ď�����ύX����
	switch (mpEnemy->GetAngleEnemy())
	{
		//�����꒼�i����G��������
		case eAngleEnemy::STRAIGHT:
		{
			//�������Ȃ�
			break;
		}
		//���Ƃ��Ƃ̌������������Ȃ�
		case eAngleEnemy::LEFT:
		{
			//�E�����ɂ���
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_RIGHT);
			break;
		}
		//���Ƃ��Ƃ̌������E�����Ȃ�
		case eAngleEnemy::RIGHT:
		{
			//�������ɂ���
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_LEFT);
			break;
		}
	}

	//���߂Č��݂̃��f���̌������擾
	this->CalculationEnemyAngle();
}

/*===================================
90�x��]������:private
====================================*/
bool EStateRotation::RotationRightAngle()
{
	//���p�ɂȂ��Ă��Ȃ�������
	if (mSaveRotation < RIGHT_ANGLE)
	{
		//����p�ϐ���ݒ肷��
		mSaveRotation += ESTATE_ROT_SPEED;		
	}
	//���p�ɂȂ�����
	else
	{
		//�����l�ɖ߂�
		mSaveRotation = 0;

		return true;
	}
	return false;
}

/*====================================
�X�V����:private
====================================*/
void EStateRotation::Update()
{
	//�ύX�����������ɉ����ď�����ʂ�
	switch (mChangeAfterAngle)
	{
		//��O
		case eChangeAfterAngle::NONE:
		{
			mpEnemy->ChangeStateWalk();
			break;
		}
		//���ɉ�]���������ꍇ
		case eChangeAfterAngle::LEFT_ROTATION:
		{
			//��]�p�x�Ǘ��p�ϐ����X�V������
			bool flag=this->RotationRightAngle();
			//�܂���]���Ȃ�
			if (!flag)
			{
				//�ȗ����ϐ��̐錾
				float rot = mpEnemy->GetBoxModel()->GetRotAngleY();

				//���f���p�x��ύX����
				mpEnemy->GetBoxModel()->SetRotationY(rot + ESTATE_ROT_SPEED);

				mpEnemy->SetAngleEnemy(eAngleEnemy::LEFT);
			}
			//�w��̊p�x��]���I�������
			else
			{
				//�������Z�o
				this->CalculationEnemyAngle();


				//������ԂƂ���
				mpEnemy->ChangeStateWalk();
			}

			break;
		}
		//�E�ɉ�]���������ꍇ
		case eChangeAfterAngle::RIGHT_ROTATION:
		{
			//��]�p�x�Ǘ��p�ϐ����X�V������
			bool flag=this->RotationRightAngle();
			//�܂���]���Ȃ�
			if (!flag)
			{
				//�ȗ����ϐ��̐錾
				float rot = mpEnemy->GetBoxModel()->GetRotAngleY();

				//���f���p�x��ύX����
				mpEnemy->GetBoxModel()->SetRotationY(rot - ESTATE_ROT_SPEED);

				mpEnemy->SetAngleEnemy(eAngleEnemy::RIGHT);
			}
			//�w��̊p�x��]���I�������
			else
			{
				//�������Z�o
				this->CalculationEnemyAngle();

				//������ԂƂ���
				mpEnemy->ChangeStateWalk();
			}
			break;
		}
		//���ʂɌ��������ꍇ
		case eChangeAfterAngle::STRAIGHT:
		{
			//���f���p�x��ύX����(���ʂɌ�����)
			mpEnemy->GetBoxModel()->SetRotationY(ESTATE_ENEMY_ROT_STRAIGHT);

			//��Ԃ��U����Ԃɂ���
			mpEnemy->ChangeStateAttack();

			//�����蔻���ݒ肷��
			mpEnemy->GetStateAttack()->SetCollider(mpRotationCollider.get());

			break;
		}
	}
	//�����蔻����X�V����
	this->SetAABBCollider();
}


/*====================================
���̓G�̌������Z�o����:private
====================================*/
void EStateRotation::CalculationEnemyAngle()
{
	//���݂̃��f���̌������擾
	int rot = static_cast<int>(mpEnemy->GetBoxModel()->GetRotAngleY());	//��ׂ�悪int�Ȃ̂ł��炩���ߕϊ�

	switch (rot)
	{
		case ESTATE_ENEMY_ROT_STRAIGHT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::STRAIGHT);
			break;
		}
		case ESTATE_ENEMY_ROT_LEFT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::LEFT);
			break;
		}
		case ESTATE_ENEMY_ROT_RIGHT:
		{
			mpEnemy->SetAngleEnemy(eAngleEnemy::RIGHT);
			break;
		}
	}
}

/*============================
�����蔻���ݒ肷��:private
============================*/
void EStateRotation::SetAABBCollider()
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
	mpRotationCollider->SetCollider(min, max);
}