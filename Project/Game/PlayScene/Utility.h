/*
�ėp�������܂Ƃ߂��w�b�_�[�t�@�C��
�쐬���F2021/08/31
*/
#pragma once

//3D����2D���W�Ŏg�p�����X,Z���g�p���邽�߂̕ϊ��p�\����
struct Vector2XZ
{
	float x;
	float z;

};


struct Utility
{
	//�����t�H���g�T�C�Y
	//��
	static const float STRING_SIZE_BIG;
	//��
	static const float STRING_SIZE_MEDIUM;
	//��
	static const float STRING_SIZE_SMALL;
	//�ɏ�
	static const float STRING_SIZE_MINIMUM;

	//�����o�b�t�@�[�T�C�Y
	static const size_t BUFFER_SIZE;
	

	//��O����
	static const int EXCEPTION_NUM;

	//�g�嗦�𔼕��ɂ���
	static const int SCALE_HALF;

	//������`�悷��֐�
	static void DrawString
	(
		int const& drawNum= EXCEPTION_NUM,
		DirectX::SimpleMath::Vector2 const& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		DirectX::FXMVECTOR const& stringColor= DirectX::Colors::White,
		float const& stringSize= STRING_SIZE_MEDIUM,
		int const& secondNum=EXCEPTION_NUM
	);
	static void DrawString
	(
		wchar_t const* string=L"none",
		DirectX::SimpleMath::Vector2 const& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		DirectX::FXMVECTOR const& stringColor= DirectX::Colors::White,
		float const& stringSize= STRING_SIZE_MEDIUM
	);

};
