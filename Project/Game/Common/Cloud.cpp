/*
��ɕ����_���Ǘ�����N���X
*/
#include"pch.h"
#include "Cloud.h"

//�O���錾
//����
#include"../Common/ObjectTexture.h"



	//�_�̏������W
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION1(20.f, 50.f);
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION2(400.f, 200.f);
const DirectX::SimpleMath::Vector2 Cloud::CLOUD_POSITION3(700.f, 80.f);


//�_�̈ړ����x
const float Cloud::CLOUD_VELOCITY = 0.5f;
//�_�̉�ʊO���W
const float Cloud::CLOUD_OVER_POSITION = 1200.f;
const float Cloud::CLOUD_RESET_POSITION = -200.f;

/*===================
�R���X�g���N�^
===================*/
Cloud::Cloud()
	:
	mpClouds{}
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i] = std::make_unique<ObjectTexture>();
	}	
}

/*===================
�f�X�g���N�^
===================*/
Cloud::~Cloud()
{
}

/*===================
����������
===================*/
void Cloud::Initialize()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->Initialize();
	}

	auto pRM = ResourceManager::GetInstance();
	auto texture=pRM->GetTexture("Cloud");

	//�摜���Z�b�g����
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->SetTexture(texture);
	}

	//���ꂼ��̍��W��ݒ肷��
	mpClouds[0]->SetPosition(CLOUD_POSITION1);
	mpClouds[1]->SetPosition(CLOUD_POSITION2);
	mpClouds[2]->SetPosition(CLOUD_POSITION3);
}

/*===================
�X�V����
===================*/
void Cloud::Update()
{
	//�ړ�����
	this->Move();
	//Warp����
	this->Warp();
}

/*===================
�`�揈��
===================*/
void Cloud::Draw()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->Draw();
	}
}

/*===================
�ړ�����
===================*/
void Cloud::Move()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		mpClouds[i]->SetPosition
		(
			DirectX::SimpleMath::Vector2
			(
				mpClouds[i]->GetPosition().x + CLOUD_VELOCITY,
				mpClouds[i]->GetPosition().y
			)
		);
	}
}

/*===================
���[�v����
===================*/
void Cloud::Warp()
{
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		if (mpClouds[i]->GetPosition().x >= CLOUD_OVER_POSITION)
		{
			mpClouds[i]->SetPosition(DirectX::SimpleMath::Vector2(CLOUD_RESET_POSITION, mpClouds[i]->GetPosition().y));
		}		
	}
}
