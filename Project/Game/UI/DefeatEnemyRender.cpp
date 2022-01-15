/*
���݂̓G�̐���`�悷��N���X

�쐬���F2021/12/11
*/
#include"pch.h"

#include"DefeatEnemyRender.h"

//�w�i�摜�̍��W
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::TEX_POSITION(30.f, 70.f);
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::TEX_SCALE(0.5f,0.5f);

//���݂̓G�̐��̕����摜�̍��W
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::CURRENT_NUM_POSITION(90.f, 95.f);
const float DefeatEnemyRender::CURRENT_NUM_SCALE = 1.f;

//�G�̍ő吔�̉摜�̍��W
const DirectX::SimpleMath::Vector2 DefeatEnemyRender::OVERALL_NUM_POSITION(120.f, 130.f);
const float DefeatEnemyRender::OVERALL_NUM_SCALE = 0.7f;

/*===================================
�R���X�g���N�^
===================================*/
DefeatEnemyRender::DefeatEnemyRender()
	:
	mpDefeatEnemyTexture(),
	mpCurrentEnemyNum(),
	mpOverallEnemyNum()
{
	mpDefeatEnemyTexture = std::make_unique<ObjectTexture>();
	mpCurrentEnemyNum = std::make_unique<SpriteNumber2D>();
	mpOverallEnemyNum = std::make_unique<SpriteNumber2D>();
}

/*===================================
�f�X�g���N�^
===================================*/
DefeatEnemyRender::~DefeatEnemyRender()
{
}

/*===================================
����������
===================================*/
void DefeatEnemyRender::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("DefeatEnemy");
	//�摜�ݒ菈��
	mpDefeatEnemyTexture->SetTexture(texture);

	mpCurrentEnemyNum->SetTextureKey("DamageNumberFont");
	mpOverallEnemyNum->SetTextureKey("NormalNumberFont");

	//����������
	mpDefeatEnemyTexture->Initialize();
	mpDefeatEnemyTexture->SetPosition(TEX_POSITION);
	mpDefeatEnemyTexture->SetScale(TEX_SCALE);

	mpCurrentEnemyNum->Initialize();
	mpCurrentEnemyNum->SetScale(CURRENT_NUM_SCALE);

	mpOverallEnemyNum->Initialize();
	mpOverallEnemyNum->SetAlign(eAlign::LEFT);
	mpOverallEnemyNum->SetScale(OVERALL_NUM_SCALE);
}

/*===================================
�`�揈��
�����F���݂̓G�̐��A�G�̍ő吔
===================================*/
void DefeatEnemyRender::Draw(int currentNum, int overallNum)
{
	//����������
	mpDefeatEnemyTexture->Draw();

	mpCurrentEnemyNum->Create(currentNum, CURRENT_NUM_POSITION);
	mpCurrentEnemyNum->Draw();

	mpOverallEnemyNum->Create(overallNum, OVERALL_NUM_POSITION);
	mpOverallEnemyNum->Draw();
}