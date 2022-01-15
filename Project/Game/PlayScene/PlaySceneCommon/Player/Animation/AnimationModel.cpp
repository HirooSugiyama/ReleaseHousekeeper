/*
�A�j���[�V������p���f���`��N���X

�쐬���F2021/09/05
*/
#include<pch.h>
#include"AnimationModel.h"

//���������̒萔
const DirectX::SimpleMath::Vector3 AnimationModel::INIT_POSITION= DirectX::SimpleMath::Vector3::Zero;
//���g�p���̒萔
const DirectX::SimpleMath::Vector3 AnimationModel::NOT_USE_POSITION(-20.f, -20.f, -20.f);

/*==============
�R���X�g���N�^
==============*/

AnimationModel::AnimationModel()
	:
	IModel(),
	mpCommonState(nullptr),
	mpSpriteBatch(nullptr),
	mpSpriteFont(nullptr),
	mWorld(),
	mView(),
	mProj(),
	mFxFactory(nullptr),
	mModel(nullptr),
	mPosition(),
	mScale(),
	mRotX(),
	mRotY(),
	mRotZ(),
	mDrawFlag(true)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	mpCommonState = pDxIF.GetCommonStates();
	mpSpriteBatch = pDxIF.GetSpriteBatch();
	mpSpriteFont = pDxIF.GetSpriteFont();
	//�C���X�^���X�̎擾
		//�r���[�s��A�v���W�F�N�V�����s��̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	ID3D11Device1* pDevice = pDR->GetD3DDevice();
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	mView = *pCiIF.GetView();
	mProj = *pCiIF.GetProjection();

	// ���f���f�[�^�̓����Ă���t�H���_�̎w��
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(pDevice);
	factory->SetDirectory(L"Resources/Models/");


	mFxFactory = std::make_unique<DirectX::EffectFactory>(pDevice);
	mWorld = DirectX::SimpleMath::Matrix::Identity;



	//������̉��
	mScale = DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3::Zero);
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(INIT_POSITION);
}

/*===================================
�f�X�g���N�^
===================================*/
AnimationModel::~AnimationModel()
{
}

/*========================
���f���̎w��
�����F���f�����
============================*/
void AnimationModel::SetModel(DirectX::Model* model)
{
	mModel = model;
}

/*============
���W�̎w��
�����F���W
==============*/
void AnimationModel::SetPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
}

/*============
�g�嗦�̎w��
�����F�g�嗦
==============*/
void AnimationModel::SetScale(DirectX::SimpleMath::Vector3 const& scale)
{
	mScale = DirectX::SimpleMath::Matrix::CreateScale(scale);
}

/*============
��]�̎w��
�����F�p�x
==============*/
void AnimationModel::SetRotationX(float const& rot)
{
	mRotX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rot));
}
void AnimationModel::SetRotationY(float const& rot)
{
	mRotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rot));
}
void AnimationModel::SetRotationZ(float const& rot)
{
	mRotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rot));
}

/*============
���W�̎擾
�Ԃ�l�F���W
==============*/
DirectX::SimpleMath::Matrix AnimationModel::GetPosition()const
{
	return mPosition;
}

/*============
�g�嗦�̎擾
�Ԃ�l�F�g�嗦
==============*/
DirectX::SimpleMath::Matrix AnimationModel::GetScale()const
{
	return mScale;
}

/*============
��]�̎擾
�Ԃ�l�F�p�x
==============*/
DirectX::SimpleMath::Matrix AnimationModel::GetRotationX()const
{
	return mRotX;
}
DirectX::SimpleMath::Matrix AnimationModel::GetRotationY()const
{
	return mRotY;
}
DirectX::SimpleMath::Matrix AnimationModel::GetRotationZ()const
{
	return mRotZ;
}
/*=================
���[���h���W�̐ݒ�
===================*/
void AnimationModel::SetWorld(DirectX::SimpleMath::Matrix const& world)
{
	mWorld = world;
}


/*====================================
�`��
�����F���[���h���W(�����Ă���)
========================================*/
void AnimationModel::Draw(DirectX::SimpleMath::Matrix* world)
{
	
	if (mDrawFlag)
	{
		//�C���X�^���X�̎擾
		DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
		DirectXtkIF& pDI = DirectXtkIF::GetDirectXtkIFInstance();
		CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();


		mView = *pCiIF.GetView();

		mProj = *pCiIF.GetProjection();

		ID3D11DeviceContext1* pContext = pDR->GetD3DDeviceContext();

		if (world == nullptr)
		{
			//���낢�딽�f
			mWorld = mScale * mRotX * mRotY * mRotZ * mPosition;
		}
		else
		{
			mWorld = *world;
		}

		mModel->Draw(pContext, *pDI.GetCommonStates(), mWorld, mView, mProj);
	}
}