/*
���f���`��N���X
�쐬���F2021/04/18
*/
#include<pch.h>
#include"ObjectModel.h"


//���������̒萔
const DirectX::SimpleMath::Vector3 ObjectModel::INIT_POSITION= DirectX::SimpleMath::Vector3::Zero;
//���g�p���̒萔
const DirectX::SimpleMath::Vector3 ObjectModel::NOT_USE_POSITION(-20.f, -20.f, -20.f);

/*==============
�R���X�g���N�^
==============*/

ObjectModel::ObjectModel()
	:
	IModel(),
	mpCommonState(nullptr),
	mpSpriteBatch(nullptr),
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
	mPosition3(),
	mScale3(),
	mRotAngleX(),
	mRotAngleY(),
	mRotAngleZ(),
	mDrawFlag(true),
	mModelUseFlag(false)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	mpCommonState = pDxIF.GetCommonStates();
	mpSpriteBatch = pDxIF.GetSpriteBatch();
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
	mScale3 = DirectX::SimpleMath::Vector3::Zero;
	mPosition3 = INIT_POSITION;	//������
	mPosition3 = NOT_USE_POSITION;//���g�p�p���W�̎w��
	mScale = DirectX::SimpleMath::Matrix::CreateScale(mScale3);
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);
}

/*===================================
�f�X�g���N�^
===================================*/
ObjectModel::~ObjectModel()
{
}

/*========================
���f���̎w��
�����F���f�����
============================*/
void ObjectModel::SetModel(DirectX::Model* model)
{
	mModel = model;
}

/*============
���W�̎w��
�����F���W
==============*/
void ObjectModel::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(pos);

	mPosition3 = pos;

}

/*============
�g�嗦�̎w��
�����F�g�嗦
==============*/
void ObjectModel::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	mScale = DirectX::SimpleMath::Matrix::CreateScale(scale);
	mScale3 = scale;
}

/*============
��]�̎w��
�����F�p�x
==============*/
void ObjectModel::SetRotationX(const float& rot)
{
	mRotAngleX = rot;
	mRotX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rot));
}
void ObjectModel::SetRotationY(const float& rot)
{
	mRotAngleY = rot;
	mRotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rot));
}
void ObjectModel::SetRotationZ(const float& rot)
{
	mRotAngleZ = rot;
	mRotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rot));
}


/*========================
���W�̎擾
�Ԃ�l�F���W(X,Y,Z)
============================*/
DirectX::SimpleMath::Vector3 ObjectModel::GetPosition()const
{
	return mPosition3;
}

/*========================
�g�嗦�̎擾
�Ԃ�l�F�g�嗦(X,Y,Z)
============================*/
DirectX::SimpleMath::Vector3 ObjectModel::GetScale()const
{
	return mScale3;
}



/*========================
�ړ�
�����F�ړ��x�N�g��
============================*/
void ObjectModel::Move(DirectX::SimpleMath::Vector3 const& vel)
{
	DirectX::SimpleMath::Vector3 vel3 = vel;

	mPosition3 += vel3;
	
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);
}

/*============
�`��
==============*/
void ObjectModel::Draw(DirectX::SimpleMath::Matrix* world)
{
	if (mDrawFlag)
	{
		//�C���X�^���X�̎擾
		DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
		DirectXtkIF& pDI = DirectXtkIF::GetDirectXtkIFInstance();
		CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();


		mView = *pCiIF.GetView();

		mProj = *pCiIF.GetProjection();

		if (world == nullptr)
		{
			//���낢�딽�f
			mWorld = mScale * mRotX * mRotY * mRotZ * mPosition;
		}
		else
		{
			mWorld = *world;
		}

		ID3D11DeviceContext1* pContext = pDR->GetD3DDeviceContext();

		mModel->Draw(pContext, *pDI.GetCommonStates(), mWorld, mView, mProj);
	}
}

