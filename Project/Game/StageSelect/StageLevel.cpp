/*
�X�e�[�W�̃��x���`��N���X
*/
#include"pch.h"
#include"StageLevel.h"



//�摜�������W
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_INIT_POSITION(855.f, 580.f);

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 StageLevel::STAGELEVELOCITY_TEXTURE_SCALE(1.2f,1.2f);

//�摜�����炷��
const float StageLevel::STAGELEVELOCITY_SHIFT_POSITION_X = 50.f;


/*===================================
�R���X�g���N�^
===================================*/
StageLevel::StageLevel()
	:mpStarTexture()
{
	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		mpStarTexture[i] = std::make_unique<ObjectTexture>();
	}
}

/*===================================
�f�X�g���N�^
===================================*/
StageLevel::~StageLevel()
{
}

/*===================================
����������
===================================*/
void StageLevel::Initialize()
{
	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture("Star");

	for (int i = 0; i < STAGE_MAX_LEVELOCITY; i++)
	{
		//�摜�ݒ�
		mpStarTexture[i]->SetTexture(textute);

		//����������
		mpStarTexture[i]->Initialize();

		//���W�ݒ�
		DirectX::SimpleMath::Vector2 pos =
			STAGELEVELOCITY_TEXTURE_INIT_POSITION +
			DirectX::SimpleMath::Vector2(i * STAGELEVELOCITY_SHIFT_POSITION_X, 0.f);

		mpStarTexture[i]->SetPosition(pos);

		//�g�嗦�ݒ�
		mpStarTexture[i]->SetScale(STAGELEVELOCITY_TEXTURE_SCALE);
	}
}

/*===================================
�`�揈��
===================================*/
void StageLevel::Draw(int const& stagelevel)
{
	for (int i = 0; i<stagelevel; i++)
	{
		mpStarTexture[i]->Draw();
	}
}
