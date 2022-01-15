/*
�ԐF�_�Ńe�N�X�`���Ǘ��N���X
�쐬���F2021/10/07
*/
#include"pch.h"

#include"RedAssert.h"


//���W
const DirectX::SimpleMath::Vector2 RedAssert::DANGEROUSUI_TEXTURE_POSITION(0.f,0.f);
//�g�嗦
const DirectX::SimpleMath::Vector2 RedAssert::DANGEROUSUI_TEXTURE_SCALE(1.f,1.f);

//�����x����
const float RedAssert::DANGEROUSUI_SIN_NUM = 3.5f;
//�����x�̒l����
const float RedAssert::DANGEROUSUI_SIN_SHIFT = 0.45f;

/*===================================
�R���X�g���N�^
===================================*/
RedAssert::RedAssert()
	:
	mpDangerousUI(),
	mSin(0.f),
	mPassFlag(false)
{
	mpDangerousUI = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
RedAssert::~RedAssert()
{
}

/*===================================
����������
===================================*/
void RedAssert::Initialize()
{
	auto pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture("DangerousTexture");

	//�摜�̏�����
	mpDangerousUI->SetTexture(texture);
	mpDangerousUI->Initialize();
	mpDangerousUI->SetPosition(DANGEROUSUI_TEXTURE_POSITION);
	mpDangerousUI->SetScale(DANGEROUSUI_TEXTURE_SCALE);
	mpDangerousUI->SetAlpha(0.f);	//�ŏ��͓����ŕۑ����Ă���
}

/*=================================
�X�V����
===================================*/
void RedAssert::Update()
{
	//�t���O�������Ă�����ʂ�
	if (mPassFlag)
	{
		//�l���擾
		float sinf = std::sinf(DirectX::XMConvertToRadians(mSin));

		//���l�Ƃ��Ďg�p����
		mpDangerousUI->SetAlpha(sinf - DANGEROUSUI_SIN_SHIFT);

		//�l���X�V����
		mSin += DANGEROUSUI_SIN_NUM;
	}
}

/*===================================
�`�揈��
===================================*/
void RedAssert::Draw()
{
	//�t���O�������Ă�����ʂ�
	if (mPassFlag)
	{
		mpDangerousUI->Draw();
	}	
}




