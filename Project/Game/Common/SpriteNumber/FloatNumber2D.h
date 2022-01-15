/*
�����������\�����s���N���X
�쐬���F2021/10/22
*/
#pragma once

//���N���X
#include"SpriteNumber2D.h"


class FloatNumber2D :public SpriteNumber2D
{
private:

	//�����x�̕ω����x
	static const float NUM_ALPHA_VELOCITY;

	//�����̈ړ����x
	static const float NUM_MOVE_VELOCITY;

	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 FLOAT_TEX_SCALE;

public:

	//�R���X�g���N�^
	FloatNumber2D();
	//�f�X�g���N�^
	~FloatNumber2D()override;
	//�X�V����
	void Update()override;

	//���Z�b�g����
	void Reset();
};

