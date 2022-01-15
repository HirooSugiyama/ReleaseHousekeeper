/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/


#include"pch.h"
#include "EStateKnockBack.h"

//�O���錾
#include"Enemy.h"

//�֐��̎g�p
#include"../ObjectModel/BoxModel.h"


//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
const DirectX::SimpleMath::Vector3 EStateKnockBack::ESTATE_COLLIDER_POSITION(0.f, 0.f, 1.f);

//�g�嗦(�����蔻��)
const DirectX::SimpleMath::Vector3 EStateKnockBack::ESTATE_COLLIDER_SCALE(0.525f, 0.125f, 0.125f);

//�ړ����x
const float EStateKnockBack::ENEMY_MOVE_SPEED = 0.5f;

//���x������
const float EStateKnockBack::ENEMY_MOVE_SPEED_DECREASE = 0.7f;

//���x�ŏ��l
const float EStateKnockBack::ENEMY_MIN_VELOCITY = 0.0001f;

//�ړ��x�N�g��������������
const float EStateKnockBack::ENEMY_MOVE_VELOCITY_SMALL = 0.5f;

//�ړ��x�N�g���𔽓]������
const float EStateKnockBack::ENEMY_MOVE_VELOCITY_REVERSE = -1.f;

/*============================
�R���X�g���N�^
============================*/
EStateKnockBack::EStateKnockBack()
	:
	EnemyStateBase(),
	mpKnockBackCollider(nullptr),
	mpEnemy(nullptr),
	mMoveVec()
{
	mpKnockBackCollider = std::make_unique<AABB>();
}

/*============================
�f�X�g���N�^
============================*/
EStateKnockBack::~EStateKnockBack()
{
}

/*============================
����������
�����F�G�̃|�C���^
============================*/
void EStateKnockBack::Initialize(Enemy* pEnemy)
{
	//�|�C���^�̕ۑ�
	mpEnemy = pEnemy;
}

/*============================
�X�V����
============================*/
void EStateKnockBack::Update()
{
	//�ϊ��p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 vel;

	vel -= mMoveVec;

	//���x������������
	mMoveVec *= ENEMY_MOVE_SPEED_DECREASE;

	//���f�����ړ�������
	mpEnemy->GetBoxModel()->Move(vel);

	//�����蔻����X�V����
	this->SetAABBCollider();


	//�������x��0�ɋ߂Â�����
	if (this->Vector3Max(mMoveVec) <= ENEMY_MIN_VELOCITY)
	{
		//����State�����Z�b�g����
		this->Reset();

		//������Ԃ�
		mpEnemy->ChangeStateBlinking();
	}
}

/*==========================
State�J�n���̏���������
============================*/
void EStateKnockBack::Reset()
{
	//���x�̏�����
	mMoveVec = DirectX::SimpleMath::Vector3::Zero;
}

/*============================
�����蔻��̃A�N�Z�T
============================*/
AABB* EStateKnockBack::GetCollider()
{
	return mpKnockBackCollider.get();
}

/*=======================
�ړ��x�N�g���ۑ��p�ϐ�
�����F�ړ��x�N�g��
=========================*/
void EStateKnockBack::SetMoveVector(DirectX::SimpleMath::Vector3 movevec)
{
	mMoveVec = movevec;
	mMoveVec.Normalize();
	mMoveVec *= ENEMY_MOVE_VELOCITY_REVERSE;
	mMoveVec *= ENEMY_MOVE_VELOCITY_SMALL;
}

/*============================
�����蔻���ݒ肷��:private
============================*/
void EStateKnockBack::SetAABBCollider()
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
	mpKnockBackCollider->SetCollider(min, max);
}

/*====================================================
Vector3�̂����̍ł��傫���l��Ԃ��֐�:private
�����FVector3�^�̒l
�Ԃ�l�F�������̍ő�l
====================================================*/
float EStateKnockBack::Vector3Max(DirectX::SimpleMath::Vector3 num)
{
	//�����l�Ƃ���X�̒l������
	float returnnum = std::fabs(num.x);

	//Y�̂ق����傫�����
	if (returnnum < std::fabs(num.y))
	{
		//Y������
		returnnum = num.y;
	}
	//Z�̂ق����傫�����
	if (returnnum < std::fabs(num.z))
	{
		//Z������
		returnnum = num.z;
	}

	//�ő�l��Ԃ�
	return returnnum;
}
