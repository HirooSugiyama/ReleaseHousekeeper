/*
�r���[�Ǝˉe�ƃJ�������W��ۑ����邽�߂̃C���^�[�t�F�[�X
*/

#include<pch.h>
#include "CameraInfoInterface.h"
//�N���X�O���ŏ�����
CameraInfoIF* CameraInfoIF::sCameraInfoIF = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoIF::spView = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoIF::spProj = nullptr;
std::unique_ptr<DirectX::SimpleMath::Vector3> CameraInfoIF::spCameraPosition = nullptr;

/*=========================================
�R���X�g���N�^
=========================================*/
CameraInfoIF::CameraInfoIF()
{
	spView = std::make_unique<DirectX::SimpleMath::Matrix>();
	spProj = std::make_unique<DirectX::SimpleMath::Matrix>();
	spCameraPosition = std::make_unique<DirectX::SimpleMath::Vector3>();
}

/*=========================================
�C���X�^���X���擾
�Ԃ�l�F���g�̃C���X�^���X
=========================================*/
CameraInfoIF& CameraInfoIF::GetCameraInfoIFInstance()
{
	if (sCameraInfoIF == nullptr)
	{
		sCameraInfoIF = new CameraInfoIF();
	}
	return *sCameraInfoIF;
}

/*=========================================
���g�̓��e�폜����
=========================================*/
void CameraInfoIF::Destroy() const
{
	if (sCameraInfoIF != nullptr) {
		delete sCameraInfoIF;
		sCameraInfoIF = nullptr;
	}
}

/*==========================
�r���[�s���ݒ肷��֐�
�����FMatrix�^	�r���[�s��
===========================*/
void CameraInfoIF::SetView(DirectX::SimpleMath::Matrix const& view)
{
	*spView = view;
}

/*=========================================
�ˉe�s���ݒ肷��֐�
�����FMatrix�^�@�ˉe�s��
=========================================*/
void CameraInfoIF::SetProjection(DirectX::SimpleMath::Matrix const& proj)
{
	*spProj = proj;
}

/*=========================================
���݂̃J�����̍��W��ݒ肷��֐�
�����FVector�^�@�J�����̍��W
=========================================*/
void CameraInfoIF::SetCameraPosition(DirectX::SimpleMath::Vector3 const& cameraPosition)
{
	*spCameraPosition = cameraPosition;
}

/*=================
�擾�֐�
=================*/
DirectX::SimpleMath::Matrix* CameraInfoIF::GetView() const
{
	return spView.get();
}

DirectX::SimpleMath::Matrix* CameraInfoIF::GetProjection() const
{
	return spProj.get();
}

DirectX::SimpleMath::Vector3* CameraInfoIF::GetCameraPosition() const
{
	return spCameraPosition.get();
}
