/*===================================================
�ǂ̍��W��g�嗦�Ȃǂ��܂Ƃ߂��萔�p�w�b�_�[�t�@�C��
===================================================*/
#pragma once


//�ǂ��̕ǂ�
enum class eWallPosition
{
	LEFT,
	RIGHT,
	GROUND,
	NUM,	//�ǂ̐�
};

struct WallConstant
{
	//���̕�
		//�g�嗦
	static const float WALL_LEFT_SCALE_X;
	static const float WALL_LEFT_SCALE_Y;
	static const float WALL_LEFT_SCALE_Z;
		//���W
	static const float WALL_LEFT_POSITION_X;
	static const float WALL_LEFT_POSITION_Y;
	static const float WALL_LEFT_POSITION_Z;

	//�E�̕�
		//�g�嗦
	static const float WALL_RIGHT_SCALE_X;
	static const float WALL_RIGHT_SCALE_Y;
	static const float WALL_RIGHT_SCALE_Z;
		//���W				  
	static const float WALL_RIGHT_POSITION_X;
	static const float WALL_RIGHT_POSITION_Y;
	static const float WALL_RIGHT_POSITION_Z;

};




