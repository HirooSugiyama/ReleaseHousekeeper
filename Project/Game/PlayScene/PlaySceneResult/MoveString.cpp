/*
�w�肵���ꏊ�Ɉړ����镶��
�쐬���F2021/10/13
*/
#include"pch.h"

#include"MoveString.h"

//���C 
const float MoveString::FRICTION_FORCE = 0.97f;

//���C��������͈�
const float MoveString::FRICTION_RANGE = 100.f;

/*===============================================
�R���X�g���N�^

===============================================*/
MoveString::MoveString()
	:
	mPosition(),
	mFinishPosition(),
	mMoveVelocityNum(),
	mpDrawString(),
	mStringSize(),
	mRightFlag(false)	//��{�͍�������
{
}

/*===================================
�f�X�g���N�^
===================================*/
MoveString::~MoveString()
{
}

/*===================================
����������
�����F	�ŏ��̍��W�A�Ō�̍��W�A
		�ړ����x�A�`�悷�镶��
		�����T�C�Y
===================================*/
void MoveString::Initialize(DirectX::SimpleMath::Vector2 const& firstpos,		//�ŏ��̍��W
							DirectX::SimpleMath::Vector2 const& finishpos,		//�ŏI�I�ȍ��W
							float const& velnum,								//�ړ����x
							const wchar_t* drawString,							//�`�悷�镶��
							float const& stringSize)							//�����T�C�Y				
{
	//�e�����̕ۑ�
	mPosition = firstpos;
	mFinishPosition = finishpos;
	mMoveVelocityNum = velnum;
	mpDrawString = drawString;
	mStringSize = stringSize;

	//�����ŏI���W��菉�����W���傫��������
	if (mFinishPosition.x < mPosition.x)
	{
		//�������E������o��������
		mRightFlag = true;
	}
}

/*===================================
�X�V����
�Ԃ�l�F�������������Ă��Ȃ���
===================================*/
bool MoveString::Update()
{
	//�E������̏o���̏ꍇ
	if (mRightFlag)
	{
		//���݂̍��W���ړI�n�ɂ��܂�
		if (mPosition.x >= mFinishPosition.x && mPosition.y >= mFinishPosition.y)
		{
			//�����̈ړ�
			this->StringMove();
		}
		else
		{
			return true;
		}
	}
	else
	{
		//���݂̍��W���ړI�n�ɂ��܂�
		if (mPosition.x <= mFinishPosition.x && mPosition.y <= mFinishPosition.y)
		{
			//�����̈ړ�
			this->StringMove();
		}
		else
		{
			return true;
		}
	}
	return false;
}

/*===================================
�`�揈��
===================================*/
void MoveString::Draw()
{
	//�����l�̕`��
	Utility::DrawString
	(
		mpDrawString,
		mPosition,
		DirectX::Colors::White,
		mStringSize
	);
}

/*===================================
�����̈ړ��Fprivate
===================================*/
void MoveString::StringMove()
{
	//�E������̏o���̏ꍇ
	if (mRightFlag)
	{
		//������x�͈̔͂ɓ������疀�C���N����
		if (mPosition.x - FRICTION_RANGE <= mFinishPosition.x)
		{
			mMoveVelocityNum *= FRICTION_FORCE;
		}

		//�ړ�����
		mPosition.x -= mMoveVelocityNum;
	}
	//��������̏o���̏ꍇ
	else
	{
		//������x�͈̔͂ɓ������疀�C���N����
		if (mPosition.x + FRICTION_RANGE >= mFinishPosition.x)
		{
			mMoveVelocityNum *= FRICTION_FORCE;
		}

		//�ړ�����
		mPosition.x += mMoveVelocityNum;
	}

	
}




