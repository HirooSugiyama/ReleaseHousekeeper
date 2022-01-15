/*
�J�����̊��N���X
�쐬���F2021/10/24
*/
#pragma once



class CameraBase
{
private:

	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

	// �r���[�s��
	DirectX::SimpleMath::Matrix mView;

	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix mProjection;

	// �J�������W
	DirectX::SimpleMath::Vector3 mEye;

	// �����_
	DirectX::SimpleMath::Vector3 mTarget;

	// ������x�N�g��
	DirectX::SimpleMath::Vector3 mUp;

protected:
	//�R���X�g���N�^
	CameraBase(DirectX::SimpleMath::Vector3 eye,DirectX::SimpleMath::Vector3 target);
	//�f�X�g���N�^
	virtual ~CameraBase() = default;


public:

	//�X�V����
	virtual void Update(DirectX::SimpleMath::Vector3 pos){ UNREFERENCED_PARAMETER(pos); }
	virtual void Update(){}

	//�e��A�N�Z�T
	// �r���[�s��̃A�N�Z�T
	void SetViewMatrix(DirectX::SimpleMath::Matrix view) { mView = view; }
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return mView; }

	// �v���W�F�N�V�����s��̃A�N�Z�T
	void SetProjectionMatrix(DirectX::SimpleMath::Matrix projection) { mProjection = projection; }
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return mProjection; }

	// �J�������W�̃A�N�Z�T
	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { mEye = eye; }
	DirectX::SimpleMath::Vector3 GetEyePosition() const { return mEye; }

	// �����_���W�̃A�N�Z�T
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { mTarget = target; }
	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return mTarget; }

	// ������x�N�g���̃A�N�Z�T
	void SetUpVector(DirectX::SimpleMath::Vector3 up) { mUp = up; }
	DirectX::SimpleMath::Vector3 GetUpVector() const { return mUp; }



protected:
	//�萔
	float GetCameraDistance() { return DEFAULT_CAMERA_DISTANCE; }

	// �r���[�s��̎Z�o
	virtual void CalculateViewMatrix();

	// �v���W�F�N�V�����s��̎Z�o
	virtual void CalculateProjectionMatrix();

public:
	//�s��v�Z���s��
	void CalculationMatrix();	//DEBUG
};