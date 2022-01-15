/*
�X�e�[�W�I���^�O
�쐬���F2021/10/21
*/
#include"pch.h"

#include"StageNumberTag.h"

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 StageNumberTag::TEX_SCALE(1.7f,2.2f);

//�摜�`��ʒu���琔���`��ʒu���Z�o���邽�߂̒萔
const DirectX::SimpleMath::Vector2 StageNumberTag::NUM_SHIFT(60.f,-20.f);

/*=================================
�R���X�g���N�^
===================================*/
StageNumberTag::StageNumberTag()
	:
	mpBackGround(nullptr),
	mDrawStageString(),
	mDrawPosition()
{
	mpBackGround = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
StageNumberTag::~StageNumberTag()
{
}

/*===================================
����������
===================================*/
void StageNumberTag::Initialize()
{
	//����������
	mpBackGround->Initialize();

	//���\�[�X�̎擾
	auto pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("StageTag");

	//�摜�̐ݒ�
	mpBackGround->SetTexture(texture);
	//�g�嗦�̐ݒ�
	mpBackGround->SetScale(TEX_SCALE);

}

/*===================================
�`�揈��
�����F�`��t���O(false �`�悵�Ȃ�)
===================================*/
void StageNumberTag::Draw(bool const& flag)
{
	//��O�����Ȃ珈�����s��Ȃ�
	if (mDrawStageString == -1)
	{
		return;
	}
	if (!flag)
	{
		return;
	}

	//�w�i�̕`��
	mpBackGround->Draw();

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	wchar_t buf[32];

	swprintf_s(buf, 32, L" Stage%d", mDrawStageString);
	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf, 
		mDrawPosition+ NUM_SHIFT,
		DirectX::Colors::Black,
		0, 
		DirectX::SimpleMath::Vector2::Zero,
		Utility::STRING_SIZE_MEDIUM
	);
}

/*===================================
�`��ʒu�̎w��
�����F���W
===================================*/
void StageNumberTag::SetPosition(DirectX::SimpleMath::Vector2 const& pos)
{
	mDrawPosition = pos;
	mpBackGround->SetPosition(pos);
}




