/*
����J����
�쐬���F2021/10/11
*/
#include "pch.h"
#include "RotationCamera.h"
#include"CameraBase.h"


//�J�����̈ړ��X�s�[�h
const float RotationCamera::CAMERA_MOVE_SPEED = 0.3f;


//�J�����������W
const DirectX::SimpleMath::Vector3 RotationCamera::CAMERA_INIT_EYE_POSITION(0.f, 30.f, 61.f);
//�^�[�Q�b�g���W
const DirectX::SimpleMath::Vector3 RotationCamera::CAMERA_INIT_TARGET(0.0f, 1.0f, -15.0f);
//�J�����̉�]���x
const float RotationCamera::CAMERA_ROT_SPEED = 0.005f;

//�����_�ƃJ�������W�̋���
const DirectX::SimpleMath::Vector3 RotationCamera::ROT_CAMERA_DISTANCE(0.0f, 1.0f, 6.0f);

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
RotationCamera::RotationCamera()
	: 
	MoveCamera(CAMERA_INIT_EYE_POSITION, CAMERA_INIT_TARGET),
	mRefEye(CAMERA_INIT_EYE_POSITION),
	mRefTarget(CAMERA_INIT_TARGET),
	mRot()
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
RotationCamera::~RotationCamera()
{
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void RotationCamera::Update()
{
	DirectX::SimpleMath::Vector3 addPosition =
		DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION,
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);
	mRot += CAMERA_ROT_SPEED;
	CameraBase::SetEyePosition(CameraBase::GetTargetPosition() + addPosition);
	
	
	CameraBase::CalculateViewMatrix();
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	//�V���O���g���֏���ۑ�
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}

//-------------------------------------------------------------------
// �ړ�����
//-------------------------------------------------------------------
void RotationCamera::Move()
{
	// �L�[���͏����擾����
	auto pKey = KeyTracker::GetKeyTrackerInstance();

	//�ړ��p�ϐ�
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 addPosition = DirectX::SimpleMath::Vector3::Zero;

	//�e�ړ������ւ̓��͏���
	if (pKey->WalkForward())
	{
		vel.z = -CAMERA_MOVE_SPEED;
	}
	if (pKey->WalkBack())
	{
		vel.z = CAMERA_MOVE_SPEED;
	}
	//���ֈړ�
	if (pKey->WalkLeft())
	{
		vel.x = -CAMERA_MOVE_SPEED;
	}
	//�E�ֈړ�
	if (pKey->WalkRight())
	{
		vel.x = CAMERA_MOVE_SPEED;
	}

	//��]����
	if (pKey->LeftRotation())
	{
		mRot -= CAMERA_ROT_SPEED;
		addPosition = DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION,
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);

	}
	if (pKey->RightRotation())
	{
		mRot += CAMERA_ROT_SPEED;
		addPosition = DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION, 
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);
	}


	// ���x���Z
	vel = DirectX::SimpleMath::Vector3::Transform
	(
		vel,
		DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
	);

	//�����ړ����Ă�����
	if (addPosition != DirectX::SimpleMath::Vector3::Zero)
	{
		this->SetRefEyePosition(this->GetRefTargetPosition() + addPosition);
	}
	if (vel != DirectX::SimpleMath::Vector3::Zero)
	{
		mRefEye += vel;
		mRefTarget += vel;
	}

	CameraInfoIF& pPvIF = CameraInfoIF::GetCameraInfoIFInstance();
	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition() +
		(mRefTarget - CameraBase::GetTargetPosition()) 
		* 0.05f
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition())
		* 0.05f
	);


	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
	//�V���O���g���֏���ۑ�
	pPvIF.SetView(CameraBase::GetViewMatrix());
	pPvIF.SetProjection(CameraBase::GetProjectionMatrix());
}

//-------------------------------------------------------------------
// ���Z�b�g����
//-------------------------------------------------------------------
void RotationCamera::Reset(DirectX::SimpleMath::Vector3 pos)
{

	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//�����_�ƃJ�����ʒu�𒲐�
	this->SetRefTargetPosition(pos - ROT_CAMERA_DISTANCE);

	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition()+
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);

	this->SetRefEyePosition
	(
		pos + CAMERA_INIT_EYE_POSITION - ROT_CAMERA_DISTANCE
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);

	//��]�p�x�����Z�b�g����
	mRot = 0.f;

	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
	//�V���O���g���֏���ۑ�
	pCiIF.SetView(GetViewMatrix());
	pCiIF.SetProjection(GetProjectionMatrix());
}
