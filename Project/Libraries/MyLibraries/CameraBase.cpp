/*
�J�����̊��N���X
�쐬���F2021/10/24
*/
#include"pch.h"
#include "CameraBase.h"
#include <DeviceResources.h>


// �J�����̋���
const float CameraBase::DEFAULT_CAMERA_DISTANCE = 5.0f;

/*==================================
�R���X�g���N�^
�����F�J�������W�A�^�[�Q�b�g�̍��W
==================================*/
CameraBase::CameraBase(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target)
	:
	mView(DirectX::SimpleMath::Matrix::Identity),
	mEye(eye),
	mTarget(target),
	mUp(0.0f, 1.0f, 0.0f)
{
}

/*=========================
�r���[�s��̎Z�o
=========================*/
void CameraBase::CalculateViewMatrix()
{
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}

/*=========================
�v���W�F�N�V�����s��̎Z�o
=========================*/
void CameraBase::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// �E�B���h�E�T�C�Y�̎擾
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	// ��p
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);
	// ��ʏc����
	float aspectRatio = width / height;
	// �J���������ԋ߂����e��
	float nearPlane = 1.0f;  
	// �J���������ԉ������e��
	float farPlane = 1000.0f;

	//�ˉe�s������߂�
	mProjection = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}


void CameraBase::CalculationMatrix()
{
	this->CalculateViewMatrix();
	this->CalculateProjectionMatrix();
}
