/*
�ړI�̏ꏊ�ɉ摜�𕽖ʕ`�悷��N���X
(�P��摜�͂�����)
�쐬���F2021/06/05
*/
#include "pch.h"
#include "ObjectTexture.h"

/*=======================================
�R���X�g���N�^
�����F	pos(���W)�Ascale(�g�嗦)
		rot(��]��)�Aalpha(�����x)
=======================================*/
ObjectTexture::ObjectTexture(
	DirectX::SimpleMath::Vector2 pos,
	DirectX::SimpleMath::Vector2 scale,
	float rot, float alpha)
	:
	ITexture(pos, scale,rot,alpha),
	mColor{ DirectX::SimpleMath::Vector4::One},
	mpSpriteBatch(nullptr)
{
	mColor.w = ITexture::GetAlpha();
}

/*=========================
�f�X�g���N�^
=========================*/
ObjectTexture::~ObjectTexture()
{
}

/*=========================
������
=========================*/
void ObjectTexture::Initialize()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	
	//�|�C���^�̕ۑ�
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*========================
�`��
=========================*/
void ObjectTexture::Draw()
{
	//���l��ݒ肷��
	mColor.w = ITexture::GetAlpha();

	//�`��
	mpSpriteBatch->Draw(ITexture::GetTexture(),
		ITexture::GetPosition(),
		nullptr,
		mColor,
		ITexture::GetRot(),
		DirectX::SimpleMath::Vector2::One,
		ITexture::GetScale());
}
