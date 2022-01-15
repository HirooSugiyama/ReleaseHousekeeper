/*
�X�R�A����̕`��N���X

�쐬���F
*/
#pragma once


//����
#include"../Common/SpriteNumber/SpriteNumber2D.h"
#include"../Common/ObjectTexture.h"

class ScoreRender
{
private:

	//�X�R�A�̕`��ʒu
	static const DirectX::SimpleMath::Vector2 SCORE_NUM_POSITION;
	//�X�R�A�̕����摜�̕`��ʒu
	static const DirectX::SimpleMath::Vector2 SCORE_STRING_POSITION;

	//�����̊g�嗦
	static const float SCORE_NUM_SCALE;
	static const float SCORE_STRING_SCALE;


	//�X�R�A�`��
	std::unique_ptr<SpriteNumber2D> mpDrawScore;

	//�����摜
	std::unique_ptr<ObjectTexture> mpScoreStringTexture;

public:

	//�R���X�g���N�^
	ScoreRender();
	//�f�X�g���N�^
	~ScoreRender();
	//����������
	void Initialize();
	//�`�揈��
	void Draw(int scoreNum);

};
