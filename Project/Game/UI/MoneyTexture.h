/*
����������̕`��摜�Ǘ��N���X
*/
#pragma once


//�O���錾
#include"../Common/ObjectTexture.h"
#include"../Common/SpriteNumber/SpriteNumber2D.h"

class MoneyTexture
{
private:

	//�摜�̍��W
	static const DirectX::SimpleMath::Vector2 UI_MONEYTEXTURE_POSITION;
	//�摜�̊g�嗦
	static const DirectX::SimpleMath::Vector2 UI_MONEYTEXTURE_SCALE;
	//���ۂ̒l�̕`��
	static const DirectX::SimpleMath::Vector2 UI_MONEY_NUM_POSITION;

	//���j�[�N�|�C���^
	std::unique_ptr<ObjectTexture> mpTexture;
	std::unique_ptr<SpriteNumber2D> mpSpriteTexture;

public:

	//�R���X�g���N�^
	MoneyTexture();
	//�f�X�g���N�^
	~MoneyTexture();
	//����������
	void Initialize();
	//�`�揈��
	void Draw();

};
