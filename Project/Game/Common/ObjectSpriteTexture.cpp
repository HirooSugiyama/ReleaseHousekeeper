/*
�ړI�̏ꏊ�ɃX�v���C�g�摜�𕽖ʕ`�悷��N���X
(�X�v���C�g�摜�͂�����)
�쐬���F2021/06/21
*/
#include "pch.h"
#include "ObjectSpriteTexture.h"

/*=========================================================================
�R���X�g���N�^
�����Fsrc(�؂�����W)�Amaxsize(�摜�����ő�T�C�Y)�Apos(�`����W)
		scale(�g�嗦)�Arot(��]��)�Aalpha(�����x)
=========================================================================*/
ObjectSpriteTexture::ObjectSpriteTexture(RECT src,
	DirectX::SimpleMath::Vector2 pos,
	DirectX::SimpleMath::Vector2 scale,
	float rot, float alpha)
	:
	ITexture(pos,scale,rot,alpha),
	mSrc(src),
	mpSpriteBatch(),
	mSpriteSrc()
{
	//�T�C�Y�Z�o
	mSpriteSrc.x = static_cast<float>(src.right - src.left);
	mSpriteSrc.y = static_cast<float>(src.bottom - src.top);
}

/*=========================
�f�X�g���N�^
=========================*/
ObjectSpriteTexture::~ObjectSpriteTexture()
{
}

/*=====================================
������
===================================*/
void ObjectSpriteTexture::Initialize()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*=========================
�`�揈��
=========================*/
void ObjectSpriteTexture::Draw()
{
	//�F(�����x�̎w��)
	DirectX::SimpleMath::Vector4 color{ DirectX::SimpleMath::Vector4::One};
	color.w = ITexture::GetAlpha();
	//�����l�̎w��
	DirectX::SimpleMath::Vector2 center{ DirectX::SimpleMath::Vector2::Zero };

	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();


	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
	//�`��
	mpSpriteBatch->Draw
	(
		ITexture::GetTexture(),
		ITexture::GetPosition(),
		&mSrc,
		color,
		ITexture::GetRot(),
		center,
		ITexture::GetScale()
	);

}