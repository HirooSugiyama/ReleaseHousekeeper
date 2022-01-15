/*
���_�N���X
�쐬���F2021/05/21
*/

#include<pch.h>
#include"Protecter.h"

//���f���̍��W
const float Protecter::PROTECTER_MODEL_POSITION_X = -0.51f;
const float Protecter::PROTECTER_MODEL_POSITION_Y = 0.7f;
const float Protecter::PROTECTER_MODEL_POSITION_Z = 16.f;
//���f���̊g�嗦
	//�����ڗp
const float Protecter::PROTECTER_MODEL_SCALE_X = 30.0f;
const float Protecter::PROTECTER_MODEL_SCALE_Y = 10.5f;
const float Protecter::PROTECTER_MODEL_SCALE_Z = 5.5f;

//���f�������~�X�̊p�x����
const float Protecter::PROTECTER_DEBUG_SHIFT_ANGLE = 180.f;


/*==============
�R���X�g���N�^
==============*/
Protecter::Protecter()
	:
	mpProtecterModel(nullptr),
	mDamageFlag(false)
{

	mpProtecterModel = std::make_unique<BoxModel>();
}

/*===================================
�f�X�g���N�^
===================================*/
Protecter::~Protecter()
{
}

/*==============
������
==============*/
void Protecter::Initialize()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("House");
	mpProtecterModel->SetModel(model);


	DirectX::SimpleMath::Vector3 pos, scale;
	pos.x = PROTECTER_MODEL_POSITION_X;
	pos.y = PROTECTER_MODEL_POSITION_Y;
	pos.z = PROTECTER_MODEL_POSITION_Z;

	mpProtecterModel->SetPosition(pos);
	mpProtecterModel->SetScale(scale);
	mpProtecterModel->SetScale(DirectX::SimpleMath::Vector3::One);
	mpProtecterModel->SetRotationY(PROTECTER_DEBUG_SHIFT_ANGLE);

	/*�����蔻�萶��*/
	//�g�嗦�̔����̒l�𐶐�
	DirectX::SimpleMath::Vector3 halfsize = mpProtecterModel->ReturnHalfSize
	(
		DirectX::SimpleMath::Vector3
		(
			PROTECTER_MODEL_SCALE_X,
			PROTECTER_MODEL_SCALE_Y,
			PROTECTER_MODEL_SCALE_Z
		)
	);
	//�ݒ�
	mpProtecterModel->SetAABBCollider(pos - halfsize, pos + halfsize);
}

/*==============
�`��
==============*/
void Protecter::Draw()
{
	mpProtecterModel->Draw();
}

/*==========================
�ڂ뉮�ɐ؂�ւ�
==========================*/
void Protecter::ChangeOldHouse()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("OldHouseSet");
	mpProtecterModel->SetModel(model);
}

