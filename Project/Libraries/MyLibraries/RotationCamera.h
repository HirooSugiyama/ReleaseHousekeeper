/*
����J����
�쐬���F2021/10/11
*/
#pragma once

#include <SimpleMath.h>

//���N���X
#include"MoveCamera.h"

class RotationCamera :public MoveCamera
{
private:

	//�J�����̈ړ��X�s�[�h
	static const float CAMERA_MOVE_SPEED;

	//�J�����������W
	static const DirectX::SimpleMath::Vector3 CAMERA_INIT_EYE_POSITION;
	//�^�[�Q�b�g���W
	static const DirectX::SimpleMath::Vector3 CAMERA_INIT_TARGET;
	//�J�����̉�]���x
	static const float CAMERA_ROT_SPEED;

	//�����_�ƃJ�������W�̋���
	static const DirectX::SimpleMath::Vector3 ROT_CAMERA_DISTANCE;


	// �Q�Ǝ��_
	DirectX::SimpleMath::Vector3 mRefEye;

	// �Q�ƒ����_
	DirectX::SimpleMath::Vector3 mRefTarget;

	//��]�l
	float mRot;

public:
	// �R���X�g���N�^
	RotationCamera();

	// �f�X�g���N�^
	~RotationCamera();

	//�X�V����
	void Update();

	// �J�������W�̃A�N�Z�T
	void SetRefEyePosition(DirectX::SimpleMath::Vector3 eye) { mRefEye = eye; }
	DirectX::SimpleMath::Vector3 GetRefEyePosition() const { return mRefEye; }

	// �Q�ƒ����_���W�̃A�N�Z�T
	void SetRefTargetPosition(DirectX::SimpleMath::Vector3 target) { mRefTarget = target; }
	DirectX::SimpleMath::Vector3 GetRefTargetPosition() const { return mRefTarget; }

	//�ړ�����
	void Move();

	//�J�������W���Z�b�g����
	void Reset(DirectX::SimpleMath::Vector3 pos);
};
