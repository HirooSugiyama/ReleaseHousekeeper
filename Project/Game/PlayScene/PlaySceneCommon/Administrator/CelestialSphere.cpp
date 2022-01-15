/*
�V���N���X
�쐬���F2021/06/19
*/
#include"pch.h"
#include "CelestialSphere.h"

//�V���̔��a
const DirectX::SimpleMath::Vector3 CelestialSphere::SPHERE_RADIUS(3.f, 3.f, 3.f);

//�J���[���ő�l��
const DirectX::SimpleMath::Vector3 CelestialSphere::MAX_COLOR_NUM(1.f, 1.f,1.f);

/*=========================
�R���X�g���N�^
=========================*/
CelestialSphere::CelestialSphere()
	:
	mpSphere(nullptr)
{
	mpSphere = std::make_unique<ObjectModel>();
}

/*=========================
�f�X�g���N�^
=========================*/
CelestialSphere::~CelestialSphere()
{
}

/*=======================
����������
=========================*/
void CelestialSphere::Initialize()
{

	//�g�p����ϐ��̐錾
	DirectX::SimpleMath::Vector3 scale = SPHERE_RADIUS;

	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();	//���\�[�X�}�l�[�W���[�̃C���X�^���X�擾
	auto model = pRM->GetCmoModel("SunDome");	//�L�[�w��


	//�V�����f���̐ݒ�
	mpSphere->SetModel(model);								//���f���̃Z�b�g
	mpSphere->SetPosition(DirectX::SimpleMath::Vector3::Zero);	//���W�͌��_
	mpSphere->SetScale(scale);								//�g�嗦�͓��{(�����傫��)

	//�G�t�F�N�g�̐ݒ�
	mpSphere->GetModel()->UpdateEffects([&](DirectX::IEffect* effect)
		{
			DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights) 
			{
				// ���C�g�̉e�����Ȃ���
				lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3::Zero);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_0), false);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_1), false);
				lights->SetLightEnabled(static_cast<int>(eWhichLight::_2), false);
			}

			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);

			if (basicEffect) 
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷��
				basicEffect->SetEmissiveColor(MAX_COLOR_NUM);
			}
		});
}

/*=========================
�`�揈��
=========================*/
void CelestialSphere::Draw()
{
	mpSphere->Draw();
}

/*=========================
�V����ς���
=========================*/
void CelestialSphere::ChangeSphereModelNight()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("NightDome");
	mpSphere->SetModel(model);			//���f���̃Z�b�g
}

void CelestialSphere::ChangeSphereModelDay()
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("SunDome");
	mpSphere->SetModel(model);			//���f���̃Z�b�g
}
