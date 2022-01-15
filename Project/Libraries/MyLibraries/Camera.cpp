//
// Camera.cpp
//
#include "pch.h"
#include "Camera.h"


#include"CameraBase.h"


// �萔�̏�����
//�J�������W
const DirectX::SimpleMath::Vector3 Camera::EYE_TO_VEC(0.f, 23.f, 15.f);
//�ŏ��̃^�[�Q�b�g���W
const DirectX::SimpleMath::Vector3 Camera::TARGET_INIT_TO_VEC(0.0f, 5.0f, 10.0f);	//�J�����̓����O�̍��W
//�^�[�Q�b�g���W
const DirectX::SimpleMath::Vector3 Camera::TARGET_TO_VEC(0.0f, 1.0f, 6.0f);			//�J�������˂��ꏊ

//�ړ�����
const float Camera::MOVE_RESTRICTION_MAX_Z = 15.f;

/*=========================================
�R���X�g���N�^
=========================================*/
Camera::Camera()
	:
	MoveCamera(EYE_TO_VEC, TARGET_INIT_TO_VEC),
	mRefEye(EYE_TO_VEC),
	mRefTarget(TARGET_INIT_TO_VEC),
	mUseEye(EYE_TO_VEC)
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


/*=========================================
�f�X�g���N�^
=========================================*/
Camera::~Camera()
{
}


/*=========================================
�X�V����
�����F�����_�Ώۃ��f�����W
=========================================*/
void Camera::Update(DirectX::SimpleMath::Vector3 modelpos)
{
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//�����_�ƃJ�����ʒu�𒲐�
	this->SetRefTargetPosition(modelpos - TARGET_TO_VEC);

	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition() +
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);


	this->SetRefEyePosition(modelpos + mUseEye - TARGET_TO_VEC);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);
	
	//�ړ��������W���z���Ă�����
	if (CameraBase::GetEyePosition().z > MOVE_RESTRICTION_MAX_Z) 
	{
		//�ϐ���ϊ�
		DirectX::SimpleMath::Vector3 limitPosition{ CameraBase::GetEyePosition() };
		limitPosition.z = MOVE_RESTRICTION_MAX_Z;

		//�ړ����������֖߂�
		CameraBase::SetEyePosition(limitPosition);
	}


	//�r���[�ϊ�
	CameraBase::CalculateViewMatrix();
	//�V���O���g���֏���ۑ�
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}

/*=========================================
�X�V����
=========================================*/
void Camera::Update()
{
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//�����_�ƃJ�����ʒu�𒲐�
	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition()+
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition()+
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);

	//�ړ��������W���z���Ă�����
	if (CameraBase::GetEyePosition().z > MOVE_RESTRICTION_MAX_Z)
	{
		//�ϐ���ϊ�
		DirectX::SimpleMath::Vector3 limitPosition{ CameraBase::GetEyePosition() };
		limitPosition.z = MOVE_RESTRICTION_MAX_Z;

		//�ړ����������֖߂�
		CameraBase::SetEyePosition(limitPosition);
	}


	//�r���[�ϊ�
	CameraBase::CalculateViewMatrix();
	//�V���O���g���֏���ۑ�
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}
