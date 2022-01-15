/*
��_�J����
�쐬���F2021/10/24
*/
#include "pch.h"
#include "FixedPointCamera.h"

#include "DeviceResources.h"

//�J�������W
const DirectX::SimpleMath::Vector3 FixedPointCamera::EYE_TO_VEC(0.0f, 2.0f, 10.0f);
//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
FixedPointCamera::FixedPointCamera()
	:
	CameraBase(EYE_TO_VEC, DirectX::SimpleMath::Vector3::Zero)
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
FixedPointCamera::~FixedPointCamera()
{
}
