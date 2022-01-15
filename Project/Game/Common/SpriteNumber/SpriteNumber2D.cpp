/*
�X�v���C�g�V�[�g�̐������QD�`�悷��N���X

�쐬���F2021/12/11
*/
#include"pch.h"

#include"SpriteNumber2D.h"

//����1��������̉摜�T�C�Y
const RECT SpriteNumber2D::SPRITE_SIZE = { 0,0,160,320 };

//�摜�̊g�嗦
const DirectX::SimpleMath::Vector2 SpriteNumber2D::TEX_SCALE(0.15f, 0.15f);

//������
const int SpriteNumber2D::STRING_SPACE = 200;

/*===================================
�R���X�g���N�^
===================================*/
SpriteNumber2D::SpriteNumber2D()
	:
	NumberBase(),
	mpNumberTexture{},
	mUseFlag{},
	mInitPosition(),
	mAlign(eAlign::RIGHT),
	mNumShift(TEX_SCALE.x * STRING_SPACE),
	mTextureScale(TEX_SCALE)
{
	//�摜�̏���
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i] = std::make_unique<ObjectSpriteTexture>
			(
				SPRITE_SIZE,						//�摜�T�C�Y(�؂����)
				DirectX::SimpleMath::Vector2::Zero,	//���W
				TEX_SCALE							//�g�嗦
			);
	}
}

/*===================================
�f�X�g���N�^
===================================*/
SpriteNumber2D::~SpriteNumber2D()
{
}

/*===================================
����������
===================================*/
void SpriteNumber2D::Initialize()
{
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(NumberBase::GetTextureKey());

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetTexture(texture);

		mpNumberTexture[i]->Initialize();
		mpNumberTexture[i]->SetRect(SPRITE_SIZE);
	}
}

/*==================================
�쐬����
�����F�\�����鐔���A�\��������W
===================================*/
void SpriteNumber2D::Create(int const& num, DirectX::SimpleMath::Vector2 const& pos)
{
	//���W�ݒ�
	mInitPosition = pos;

	//�e�퐔����ۑ�����//�K�v�Ȑ�����I�яo��
	this->CreateNumber(this->ChooseNum(num));

	//�����Ԑ�������
	this->CreateStringShift();
}

/*===================================
�`�揈��
===================================*/
void SpriteNumber2D::Draw()
{

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//��O�����ȊO�Ȃ�`�悷��
		if (mUseFlag[i])
		{
			mpNumberTexture[i]->Draw();
		}		
	}
}

/*===============================================
�g�嗦��ݒ肷��
�����F�g�嗦
=================================================*/
void SpriteNumber2D::SetScale(float scale)
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mTextureScale = TEX_SCALE * DirectX::SimpleMath::Vector2(scale, scale);
		mNumShift = mTextureScale.x * STRING_SPACE;
		mpNumberTexture[i]->SetScale(mTextureScale);

		//�����Ԃ𐶐����Ȃ���
		this->CreateStringShift();
	}
}

/*===============================================
�e�ϐ��ɂق����ԍ�������:private
�����F�쐬���鐔���Q
=================================================*/
void SpriteNumber2D::CreateNumber(std::vector<int> const& num)
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//���g�p����
		mUseFlag[i] = false;
		mpNumberTexture[i]->SetRect(SPRITE_SIZE);
	}

	//�����ݒ�
	for (int i = 0; i < static_cast<int>(num.size()); i++)
	{
		if (mUseFlag[i])continue;

		mpNumberTexture[i]->Beside(static_cast<float>(SPRITE_SIZE.right), num[i]);
		mUseFlag[i] = true;
	}
}

void SpriteNumber2D::CreateStringShift()
{
	//�g�p���錅�ɍ��킹�Ĉ�ԉE�̍��W��ݒ肷��
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		if (mUseFlag[i])
		{
			switch (mAlign)
			{
				case eAlign::LEFT:
				{
					mInitPosition.x += mNumShift;
					break;
				}
				case eAlign::RIGHT:
				{
					mInitPosition.x -= mNumShift;
					break;
				}
			}
		}
	}


	//���W��ݒ肷��

	switch (mAlign)
	{
		case eAlign::LEFT:
		{
			for (int i = MAX_DIGIT_NUM - 1; i >= 0; i--)
			{
				if (mUseFlag[i])
				{
					mInitPosition.x -= mNumShift;
					mpNumberTexture[i]->SetPosition(mInitPosition);
				}
			}
			break;
		}
		case eAlign::RIGHT:
		{
			for (int i = 0; i < MAX_DIGIT_NUM; i++)
			{
				if (mUseFlag[i])
				{
					mInitPosition.x += mNumShift;
					mpNumberTexture[i]->SetPosition(mInitPosition);
				}
			}
			break;
		}
	}
}
