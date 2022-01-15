/*
���C���J����
�쐬���F2021/10/24
*/
#pragma once



//���N���X
#include"MoveCamera.h"


class Camera :public MoveCamera
{
private:
	//�萔

	//�J�������W
	static const DirectX::SimpleMath::Vector3 EYE_TO_VEC;
	//�ŏ��̃^�[�Q�b�g���W
	static const DirectX::SimpleMath::Vector3 TARGET_INIT_TO_VEC;
	//�^�[�Q�b�g���W
	static const DirectX::SimpleMath::Vector3 TARGET_TO_VEC;	

	//�ړ�����
	static const float MOVE_RESTRICTION_MAX_Z;

	// �Q�Ǝ��_
	DirectX::SimpleMath::Vector3 mRefEye;

	// �Q�ƒ����_
	DirectX::SimpleMath::Vector3 mRefTarget;

	//�g�p�J�������_
	DirectX::SimpleMath::Vector3 mUseEye;


public:
	// �R���X�g���N�^
	Camera();

	//�펞����
	void Update(DirectX::SimpleMath::Vector3 modelpos);
	void Update();

	// �f�X�g���N�^
	~Camera();

	// �J�������W�̃A�N�Z�T
	void SetRefEyePosition(DirectX::SimpleMath::Vector3 eye) { mRefEye = eye; }
	DirectX::SimpleMath::Vector3 GetRefEyePosition() const { return mRefEye; }
		//����ɍׂ����A�N�Z�T
		//X
		void SetRefEyePositionX(float eyex) { mRefEye.x = eyex; }
		float GetRefEyePositionX() const { return mRefEye.x; }
		//Y
		void SetRefEyePositionY(float eyey) { mRefEye.y = eyey; }
		float GetRefEyePositionY() const { return mRefEye.y; }
		//Z
		void SetRefEyePositionZ(float eyez) { mRefEye.z = eyez; }
		float GetRefEyePositionZ() const { return mRefEye.z; }

	// �Q�ƒ����_���W�̃A�N�Z�T
	void SetRefTargetPosition(DirectX::SimpleMath::Vector3 target) { mRefTarget = target; }
	DirectX::SimpleMath::Vector3 GetRefTargetPosition() const { return mRefTarget; }
		//����ɍׂ����A�N�Z�T
		//X
		void SetRefTargetPositionX(float targetx) { mRefTarget.x = targetx; }
		float GetRefTargetPositionX() const { return mRefTarget.x; }
		//Y
		void SetRefTargetPositionY(float targety) { mRefTarget.y = targety; }
		float GetRefTargetPositionY() const { return mRefTarget.y; }
		//Z
		void SetRefTargetPositionZ(float targetz) { mRefTarget.z = targetz; }
		float GetRefTargetPositionZ() const { return mRefTarget.z; }
};
