/*
�V�K���s�t�@�C��

*/
#include"pch.h"

#include"MoveSpriteNumber2D.h"

/*===================================
�R���X�g���N�^
===================================*/
MoveSpriteNumber2D::MoveSpriteNumber2D()
	:
	mpMoveNumber(),
	mpSpriteNumber2D(),
	mDrawPosition()
{
	mpMoveNumber = std::make_unique<MoveNumber>();
	mpSpriteNumber2D = std::make_unique<SpriteNumber2D>();
}

/*===================================
�f�X�g���N�^
===================================*/
MoveSpriteNumber2D::~MoveSpriteNumber2D()
{
}

/*===================================
����������
�����F	�摜�p�X
		�ŏ��̒l
		�ړ����x(�b)
		�ő�l
===================================*/
void MoveSpriteNumber2D::Initialize(std::string const& textureKey,
									int const& firstNum,
									float const& moveSecondSpeed,
									int const& maxNum)
{

	//�摜�N���X�̏���������
	mpSpriteNumber2D->SetTextureKey(textureKey);
	mpSpriteNumber2D->Initialize();

	//�ړ������̏���������
	mpMoveNumber->Initialize(firstNum, moveSecondSpeed, maxNum);
}

/*=================================
�X�V����
�����F�^�C�}�[
�Ԃ�l�F���݂̒l
===================================*/
int MoveSpriteNumber2D::Update(DX::StepTimer const& timer)
{
	mpMoveNumber->Update(timer);

	return mpMoveNumber->GetMoveNum();
}

/*===================================
�`�揈��
===================================*/
void MoveSpriteNumber2D::Draw()
{
	//�摜�`��
	mpSpriteNumber2D->Create(mpMoveNumber->GetMoveNum(), mDrawPosition);
	mpSpriteNumber2D->Draw();
}
