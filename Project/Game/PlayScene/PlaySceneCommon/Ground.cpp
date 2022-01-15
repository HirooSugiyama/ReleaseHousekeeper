/*
�n�ʂ̃N���X
�쐬���F2021/06/28
*/
#include"pch.h"
#include "Ground.h"

//�萔
//�n�ʂ̒��S���W
const DirectX::SimpleMath::Vector3 Ground::GROUND_POSITION(0.f,0.5f,-15.f);
//�n�ʂ̊g�嗦
const DirectX::SimpleMath::Vector3 Ground::GROUND_SCALE(40.f, 0.5f, 60.f);


/*===================================
�R���X�g���N�^
===================================*/
Ground::Ground()
	:
	mpGroundModel()
{
	//����
	mpGroundModel = std::make_unique<ObjectModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
Ground::~Ground()
{
}

/*===================================
����������
===================================*/
void Ground::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Ground");
	mpGroundModel->SetModel(model);
	mpGroundModel->SetPosition(GROUND_POSITION);
	mpGroundModel->SetScale(GROUND_SCALE);
}

/*===================================
�`�揈��
===================================*/
void Ground::Draw()
{
	mpGroundModel->Draw();
}
