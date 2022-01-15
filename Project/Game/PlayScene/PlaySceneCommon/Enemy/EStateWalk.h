/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateWalk :public EnemyStateBase
{
private:

	//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//�g�嗦(�����蔻��)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//�ړ����x
	static const float ENEMY_MOVE_SPEED;

	//���f���p�x
	static const float ESTATE_MODEL_ANGLE_STRAIGHT;
	static const float ESTATE_MODEL_ANGLE_RIGHT;
	static const float ESTATE_MODEL_ANGLE_LEFT;

	//�����蔻��
	std::unique_ptr<AABB> mpWalkCollider;

	//�ۑ��p�ϐ�
	Enemy* mpEnemy;

	//�ǂ������p�ړ����x�ۑ��ϐ�
	DirectX::SimpleMath::Vector3 mChaseVelocity;


public:
	//�R���X�g���N�^
	EStateWalk();

	//�f�X�g���N�^
	~EStateWalk()override;

	//����������
	 void Initialize(Enemy * pEnemy)override;

	//�X�V����
	 void Update()override;

	//State�J�n���̏���������
	 void Reset()override;


	 //�����蔻��̃A�N�Z�T
	 AABB* GetCollider()const;	//�w�b�_�[�t�@�C���̓s����CPP�ŏ������s��

	//�ǂ������p�ړ����x�ۑ��ϐ��̐ݒ�
	 void ChaseVelocitySet(DirectX::SimpleMath::Vector3 vel);
	 void ResetChaseVelocity() { mChaseVelocity = DirectX::SimpleMath::Vector3::Zero; }

	 //������ύX����
	 void RotEnemyForTarget(DirectX::SimpleMath::Vector3 targetpos);
	 //������������
	 void ResetEnemyAngle();

private:
	//�����蔻���ݒ肷��
	void SetAABBCollider()override;

	//�͈͓��Ɏ��߂�
	float Clamp(float const& num, float const& minNum, float const& maxNum)const;

};