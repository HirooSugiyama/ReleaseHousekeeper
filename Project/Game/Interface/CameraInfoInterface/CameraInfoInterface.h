/*
�r���[�Ǝˉe�ƃJ�������W��ۑ����邽�߂̃C���^�[�t�F�[�X
*/

#pragma once
#include <SimpleMath.h>


class CameraInfoIF
{
private:
	static CameraInfoIF* sCameraInfoIF;

	static std::unique_ptr<DirectX::SimpleMath::Matrix> spView;
	static std::unique_ptr<DirectX::SimpleMath::Matrix> spProj;
	static std::unique_ptr<DirectX::SimpleMath::Vector3> spCameraPosition;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	CameraInfoIF( CameraInfoIF const& pv) = delete;
	CameraInfoIF operator=( CameraInfoIF const& pv) = delete;


	//�R���X�g���N�^
	CameraInfoIF();
	//�f�X�g���N�^
	~CameraInfoIF()=default;
public:
	//���g�̃C���X�^���X
	static CameraInfoIF& GetCameraInfoIFInstance();

	void Destroy()const;

	//�ݒ�֐�
	void SetView(DirectX::SimpleMath::Matrix const& view);
	void SetProjection(DirectX::SimpleMath::Matrix const& proj);
	void SetCameraPosition(DirectX::SimpleMath::Vector3 const& cameraPosition);

	//�擾�֐�
	DirectX::SimpleMath::Matrix* GetView() const;
	DirectX::SimpleMath::Matrix* GetProjection() const;
	DirectX::SimpleMath::Vector3* GetCameraPosition() const;
};