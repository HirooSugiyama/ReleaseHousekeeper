/*
���݂̓G�̐���`�悷��N���X

�쐬���F2021/12/11
*/
#pragma once

#include"../Common/ObjectTexture.h"
#include"../Common/SpriteNumber/SpriteNumber2D.h"

class DefeatEnemyRender
{
private:
	//�w�i�摜�̍��W
	static const DirectX::SimpleMath::Vector2 TEX_POSITION;
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//���݂̓G�̐��̕����摜�̍��W
	static const DirectX::SimpleMath::Vector2 CURRENT_NUM_POSITION;
	static const float CURRENT_NUM_SCALE;

	//�G�̍ő吔�̉摜�̍��W
	static const DirectX::SimpleMath::Vector2 OVERALL_NUM_POSITION;
	static const float OVERALL_NUM_SCALE;


	//�w�i�摜
	std::unique_ptr<ObjectTexture> mpDefeatEnemyTexture;

	//���݂̓G�̐�
	std::unique_ptr<SpriteNumber2D> mpCurrentEnemyNum;
	//�S�̂̓G�̐�
	std::unique_ptr<SpriteNumber2D> mpOverallEnemyNum;

public:

	//�R���X�g���N�^
	DefeatEnemyRender();
	//�f�X�g���N�^
	~DefeatEnemyRender();
	//����������
	void Initialize();
	//�`�揈��
	void Draw(int currentNum,int overallNum);

};
