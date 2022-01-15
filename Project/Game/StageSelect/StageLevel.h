/*
�X�e�[�W�̃��x���`��N���X
*/
#pragma once

//�O���錾
#include"../Common/ObjectTexture.h"


class StageLevel
{
private:
	//�X�e�[�W�ő僌�x��
	static const int STAGE_MAX_LEVELOCITY = 6;

	//�摜�������W
	static const DirectX::SimpleMath::Vector2 STAGELEVELOCITY_TEXTURE_INIT_POSITION;
	//�摜�g�嗦
	static const DirectX::SimpleMath::Vector2 STAGELEVELOCITY_TEXTURE_SCALE;
	//�摜�����炷��
	static const float STAGELEVELOCITY_SHIFT_POSITION_X;

	//�摜�N���X
	std::unique_ptr<ObjectTexture> mpStarTexture[STAGE_MAX_LEVELOCITY];

public:

	//�R���X�g���N�^
	StageLevel();
	//�f�X�g���N�^
	~StageLevel();
	//����������
	void Initialize();
	//�`�揈��
	void Draw(int const& stagelevel);

};
