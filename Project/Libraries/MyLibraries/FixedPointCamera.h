/*
��_�J����
�쐬���F2021/10/24
*/
#pragma once



//�K��N���X
#include"CameraBase.h"

class FixedPointCamera :public CameraBase
{
private:

	//�J�������W
	static const DirectX::SimpleMath::Vector3 EYE_TO_VEC;

public:
	// �R���X�g���N�^
	FixedPointCamera();

	// �f�X�g���N�^
	~FixedPointCamera();

};
