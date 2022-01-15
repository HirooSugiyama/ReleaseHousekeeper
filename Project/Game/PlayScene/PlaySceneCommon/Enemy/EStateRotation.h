/*
�G�s���p�^�[��
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

class EStateRotation :public EnemyStateBase
{
private:


	//�G���f�����W����̓����蔻��̍��̋���(�����蔻��̍��W)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_POSITION;

	//�g�嗦(�����蔻��)
	static const DirectX::SimpleMath::Vector3 ESTATE_COLLIDER_SCALE;

	//��]�X�s�[�h
	static const float ESTATE_ROT_SPEED;

	//���p
	static const float RIGHT_ANGLE;


	//�G�̌��݂̌�����\��
	static const int ESTATE_ENEMY_ROT_STRAIGHT;
	static const int ESTATE_ENEMY_ROT_LEFT;
	static const int ESTATE_ENEMY_ROT_RIGHT;

	//���W�̂��炷��
	static const int ESTATE_ENEMY_SHIFT_POSITION_RANGE;

	//�����蔻��
	std::unique_ptr<AABB> mpRotationCollider;


	//�ۑ��p�ϐ�
	Enemy* mpEnemy;


	//���݂̉�]�p
	float mSaveRotation;


	//��]��������������ۑ�����ϐ�
	eChangeAfterAngle mChangeAfterAngle;


public:
	//�R���X�g���N�^
	EStateRotation();

	//�f�X�g���N�^
	~EStateRotation()override;

	//����������
	void Initialize(Enemy* pEnemy)override;

	//�X�V����
	void Update()override;

	//State�J�n���̏���������
	void Reset()override;

	//�����蔻��̃A�N�Z�T
	AABB* GetCollider()const;	//�w�b�_�[�t�@�C���̓s����CPP�ŏ������s��



	//��]��������������ۑ�����
	void SetChangeAfterAngle(eChangeAfterAngle const& angle) { mChangeAfterAngle = angle; }

	//���f���̌����𔽓]������
	void ReverseRotEnemyModel();


private:


	//90�x��]������
	bool RotationRightAngle();

	//���̓G�̌������Z�o����
	void CalculationEnemyAngle();

	//�����蔻���ݒ肷��
	void SetAABBCollider()override;
};