/*
�t�F�[�h�������s�������摜�̃N���X

�쐬���F2021/12/11
*/
#pragma once

#include"SpriteNumber2D.h"


class FadeNumber2D :public SpriteNumber2D
{
private:

public:

	//�R���X�g���N�^
	FadeNumber2D();
	//�f�X�g���N�^
	~FadeNumber2D()override;

	//�X�V����
	void Update()override;

	//���Z�b�g����
	void Reset();

};
