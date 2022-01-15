/*
�J�[�\�����Ǘ�����N���X
�쐬���F2021 / 10 / 13
*/
#include"pch.h"

#include"Cursor.h"

//�O���錾
#include"../Common/ObjectTexture.h"

/*=================================
�R���X�g���N�^
===================================*/
Cursor::Cursor()
	:
	mpCursorTexture(nullptr),
	mShiftNum(0.f),
	mSaveInitPosition(DirectX::SimpleMath::Vector2::Zero)
{
	mpCursorTexture = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
Cursor::~Cursor()
{
}

/*===================================
����������
�����F	�摜�̏������W�A�摜�g�嗦
		�ړ����A��]��[default 0.f]
===================================*/
void Cursor::Initialize(
	DirectX::SimpleMath::Vector2 const& initPosition,
	DirectX::SimpleMath::Vector2 const& scale,
	float const& shiftPosition,
	float const& rot)
{
	//����������
	mpCursorTexture->Initialize();

	//���\�[�X�̊m��
	auto pRM = ResourceManager::GetInstance();
	auto Textute = pRM->GetTexture("StageCursor");

	//�摜�̐ݒ�
	mpCursorTexture->SetTexture(Textute);

	//�g�嗦�̐ݒ�
	mpCursorTexture->SetPosition(initPosition);
	mSaveInitPosition = initPosition;

	//�g�嗦�̐ݒ�
	mpCursorTexture->SetScale(scale);

	//��]���̐ݒ�
	mpCursorTexture->SetRot(rot);

	//�ړ����̕ۑ�
	mShiftNum = shiftPosition;
}

/*=========================================
�`�揈��
�����F�`��t���O(true�ŕ`��)(default:true)
===========================================*/
void Cursor::Draw(bool const& flag)
{
	if (!flag)return;

	//�摜�̕`��
	mpCursorTexture->Draw();
}

/*=================================
�J�[�\������Ɉړ�����
===================================*/
void Cursor::CursorUp()
{
	//��Ɉړ�������
	mpCursorTexture->SetPosition
	(
		mpCursorTexture->GetPosition() - 
		DirectX::SimpleMath::Vector2(0.f, mShiftNum)
	);
}

/*===================================
�J�[�\���������ʒu�Ƀ��Z�b�g����
===================================*/
void Cursor::CursorReset()
{
	//��Ɉړ�������
	mpCursorTexture->SetPosition(mSaveInitPosition);
}

/*===================================
�J�[�\������ԉ��ɃZ�b�g����
�����F1��ʂ̍ő�X�e�[�W��
===================================*/
void Cursor::CursorSetUnder(int const& screenMaxStageNum)
{
	//���Ɉړ�������
	mpCursorTexture->SetPosition
	(
		mSaveInitPosition +
		DirectX::SimpleMath::Vector2(0.f, mShiftNum *(screenMaxStageNum +(Utility::EXCEPTION_NUM)))
	);
}

/*===================================
�J�[�\�������Ɉړ�����
===================================*/
void Cursor::CursorDown()
{
	//���Ɉړ�������
	mpCursorTexture->SetPosition(mpCursorTexture->GetPosition() + DirectX::SimpleMath::Vector2(0.f, mShiftNum));
}