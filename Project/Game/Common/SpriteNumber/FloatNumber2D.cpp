/*
�����������\�����s���N���X
�쐬���F2021/10/22
*/
#include"pch.h"

#include"FloatNumber2D.h"

//�O���錾
#include"../../Common/ObjectSpriteTexture.h"
#include"Libraries/MyLibraries/CameraBase.h"

//�����x�̕ω����x
const float FloatNumber2D::NUM_ALPHA_VELOCITY = 0.06f;

//�����̈ړ����x
const float FloatNumber2D::NUM_MOVE_VELOCITY = 9.f;

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 FloatNumber2D::FLOAT_TEX_SCALE(0.25f, 0.25f);

/*==================================
�R���X�g���N�^
===================================*/
FloatNumber2D::FloatNumber2D()
	:
	SpriteNumber2D()
{
	//�摜�̏���
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		SpriteNumber2D::GetNumberTexture(i)->SetScale(FLOAT_TEX_SCALE);
	}
}

/*===================================
�f�X�g���N�^
===================================*/
FloatNumber2D::~FloatNumber2D()
{
}


/*=================================
�X�V����
===================================*/
void FloatNumber2D::Update()
{
	DirectX::SimpleMath::Vector2 movepos(DirectX::SimpleMath::Vector2::Zero);

	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//��O�����ȊO�Ȃ�`�悷��
		if (SpriteNumber2D::GetUseFlag(i))
		{
			//�ړ�����
			movepos = SpriteNumber2D::GetNumberTexture(i)->GetPosition();
			movepos.y -= NUM_MOVE_VELOCITY;
			SpriteNumber2D::GetNumberTexture(i)->SetPosition(movepos);
		}
	}
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//��O�����ȊO�Ȃ�`�悷��
		if (SpriteNumber2D::GetUseFlag(i))
		{
			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha()- NUM_ALPHA_VELOCITY);
			break;
		}
	}

	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//��O�����ȊO�Ȃ�`�悷��
		if (SpriteNumber2D::GetUseFlag(i))
		{
			//����������
			SpriteNumber2D::GetNumberTexture(i)->SetAlpha(NumberBase::GetTextureAlpha());

			//�������S�ɓ����ɂȂ�����
			if (NumberBase::GetTextureAlpha() <= 0.0f)
			{
				//���Z�b�g������ʂ�
				this->Reset();
			}
		}
	}
}



/*===============================================
���Z�b�g����
===============================================*/
void FloatNumber2D::Reset()
{
	for (int i = 0; i < SpriteNumber2D::GetMaxDigitNum(); i++)
	{
		//���g�p����
		SpriteNumber2D::SetUseFlag(i,false);
		SpriteNumber2D::GetNumberTexture(i)->SetAlpha(1.f);								//�����x�����ɖ߂�
		SpriteNumber2D::GetNumberTexture(i)->SetRect(SpriteNumber2D::GetSpriteSize());	//UV���W�����ɖ߂�
	}
	//������
	NumberBase::SetTextureAlpha(1.f);
}