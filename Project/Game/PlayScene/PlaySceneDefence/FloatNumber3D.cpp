/*
�����������\�����s���N���X
�쐬���F2021/10/22
*/
#include"pch.h"

#include"FloatNumber3D.h"

//�O���錾
#include"../../Common/ObjectSpriteTexture.h"
#include"../Effect/Effect.h"
#include"Libraries/MyLibraries/CameraBase.h"

//�������m�̕�
const float FloatNumber3D::NUM_SHIFT = 0.9f;

//�����̈ړ����x
const float FloatNumber3D::NUM_MOVE_VELOCITY = 0.05f;


//�����x�̕ω����x
const float FloatNumber3D::NUM_ALPHA_VELOCITY = 0.03f;

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 FloatNumber3D::TEX_SCALE(0.5f, 1.f);

/*==================================
�R���X�g���N�^
===================================*/
FloatNumber3D::FloatNumber3D()
	:
	NumberBase(),
	mpNumberTexture(),
	mpCamera(),
	mInitPosition(),
	mUseFlag(false)
{
	//�摜�̏���
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i] = std::make_unique<EffectSpriteTexture>
			(
				1,											//�摜�����s��		
				DirectX::SimpleMath::Vector3::Zero,			//���W
				TEX_SCALE									//�g�嗦
			);
	}
}

/*===================================
�f�X�g���N�^
===================================*/
FloatNumber3D::~FloatNumber3D()
{
}

/*===================================
����������
�����F�J�����̃|�C���^
===================================*/
void FloatNumber3D::Initialize(CameraBase* pCamera)
{
	//���\�[�X�̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture("DamageNumberFont");

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetTexture(texture);
		mpNumberTexture[i]->Initialize();
		mpNumberTexture[i]->SetHorizontalCutNum(10);		//����[�Œ�]
		mpNumberTexture[i]->SetCameraEyePosition(pCamera->GetEyePosition());
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//��O����
	}	
}

/*==================================
�쐬����
�����F�\�����鐔���A�\��������W
===================================*/
void FloatNumber3D::Create(int num, DirectX::SimpleMath::Vector3 pos)
{
	mInitPosition = pos;

	//�e�퐔����ۑ�����//�K�v�Ȑ�����I�яo��
	this->CreateNumber(NumberBase::ChooseNum(num));

	//���W��ݒ肷��
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//��O�����Ȃ�`�悷��
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			mpNumberTexture[i]->SetPosition(mInitPosition+ DirectX::SimpleMath::Vector3((i*NUM_SHIFT),0.f,0.f));
		}
	}

	//�g�p��ԂƂ���
	mUseFlag = true;
}

/*=================================
�X�V����
===================================*/
void FloatNumber3D::Update()
{	
	//�g�p���Ă��Ȃ������珈�������Ȃ�
	if (!mUseFlag)return;

	DirectX::SimpleMath::Vector3 movepos = DirectX::SimpleMath::Vector3::Zero;

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//��O�����Ȃ�`�悷��
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			//�ړ�����
			movepos = mpNumberTexture[i]->GetPosition();
			movepos.y += NUM_MOVE_VELOCITY;
			mpNumberTexture[i]->SetPosition(movepos);

			//����������
			mpNumberTexture[i]->SetAlpha(NumberBase::GetTextureAlpha());
		}
	}

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//��O�����ȊO�Ȃ�`�悷��
		if (mpNumberTexture[i]->GetWidthNum() != Utility::EXCEPTION_NUM)
		{
			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha() - NUM_ALPHA_VELOCITY);

			NumberBase::SetTextureAlpha(NumberBase::GetTextureAlpha()-NUM_ALPHA_VELOCITY);

			//�������S�ɓ����ɂȂ�����
			if (NumberBase::GetTextureAlpha() <= 0.0f)
			{
				//���Z�b�g������ʂ�
				this->Reset();
			}

			break;
		}
	}
}

/*===================================
�`�揈��
===================================*/
void FloatNumber3D::Draw()
{
	//�g�p���Ă��Ȃ������珈�������Ȃ�
	if (!mUseFlag)return;

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		//��O�����Ȃ�`�悷��
		if (mpNumberTexture[i]->GetWidthNum()!= Utility::EXCEPTION_NUM)
		{
			mpNumberTexture[i]->ExtendDraw();
		}
	}	
}


/*===============================================
���Z�b�g����
===============================================*/
void FloatNumber3D::Reset()
{
	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//��O�����ŏ�����
		mpNumberTexture[i]->SetAlpha(NumberBase::GetInitAlpha());			//�����x�����ɖ߂�
	}
	NumberBase::SetTextureAlpha(NumberBase::GetInitAlpha());

	//�g�p���Ă��Ȃ������珈�������Ȃ�
	mUseFlag = false;
}


/*===============================================
�e�ϐ��ɂق����ԍ�������:private
�����F�쐬���鐔���Q
=================================================*/
void FloatNumber3D::CreateNumber(std::vector<int> num)
{
	//-1�ŏ�����

	for (int i = 0; i < MAX_DIGIT_NUM; i++)
	{
		mpNumberTexture[i]->SetWidthNum(Utility::EXCEPTION_NUM);				//��O����
	}


	for (int i = 0; i < static_cast<int>(num.size()); i++)
	{
		mpNumberTexture[i]->SetWidthNum(num[i]);
	}
}
