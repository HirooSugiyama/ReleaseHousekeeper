/*
�����J�����N���X

�쐬���F2021/12/05
*/

#include"pch.h"
#include"MoveCamera.h"


//�΂˂̋���
const float MoveCamera::SPRING_POWER = 0.05f;

/*===============================
�R���X�g���N�^
�����F�J�������W�A�J���������_
==================================*/

MoveCamera::MoveCamera(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target)
	:
	CameraBase(eye,target)
{
}
