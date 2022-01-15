/*
アニメーション専用モデル描画クラス

作成日：2021/09/05
*/
#include<pch.h>
#include"AnimationModel.h"

//初期化時の定数
const DirectX::SimpleMath::Vector3 AnimationModel::INIT_POSITION= DirectX::SimpleMath::Vector3::Zero;
//未使用時の定数
const DirectX::SimpleMath::Vector3 AnimationModel::NOT_USE_POSITION(-20.f, -20.f, -20.f);

/*==============
コンストラクタ
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
	//インスタンスの取得
		//ビュー行列、プロジェクション行列の取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	ID3D11Device1* pDevice = pDR->GetD3DDevice();
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	mView = *pCiIF.GetView();
	mProj = *pCiIF.GetProjection();

	// モデルデータの入っているフォルダの指定
	std::unique_ptr<DirectX::EffectFactory> factory = std::make_unique<DirectX::EffectFactory>(pDevice);
	factory->SetDirectory(L"Resources/Models/");


	mFxFactory = std::make_unique<DirectX::EffectFactory>(pDevice);
	mWorld = DirectX::SimpleMath::Matrix::Identity;



	//未代入の回避
	mScale = DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3::Zero);
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(INIT_POSITION);
}

/*===================================
デストラクタ
===================================*/
AnimationModel::~AnimationModel()
{
}

/*========================
モデルの指定
引数：モデル情報
============================*/
void AnimationModel::SetModel(DirectX::Model* model)
{
	mModel = model;
}

/*============
座標の指定
引数：座標
==============*/
void AnimationModel::SetPosition(DirectX::SimpleMath::Vector3 const& pos)
{
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(pos);
}

/*============
拡大率の指定
引数：拡大率
==============*/
void AnimationModel::SetScale(DirectX::SimpleMath::Vector3 const& scale)
{
	mScale = DirectX::SimpleMath::Matrix::CreateScale(scale);
}

/*============
回転の指定
引数：角度
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
座標の取得
返り値：座標
==============*/
DirectX::SimpleMath::Matrix AnimationModel::GetPosition()const
{
	return mPosition;
}

/*============
拡大率の取得
返り値：拡大率
==============*/
DirectX::SimpleMath::Matrix AnimationModel::GetScale()const
{
	return mScale;
}

/*============
回転の取得
返り値：角度
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
ワールド座標の設定
===================*/
void AnimationModel::SetWorld(DirectX::SimpleMath::Matrix const& world)
{
	mWorld = world;
}


/*====================================
描画
引数：ワールド座標(無くても可)
========================================*/
void AnimationModel::Draw(DirectX::SimpleMath::Matrix* world)
{
	
	if (mDrawFlag)
	{
		//インスタンスの取得
		DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
		DirectXtkIF& pDI = DirectXtkIF::GetDirectXtkIFInstance();
		CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();


		mView = *pCiIF.GetView();

		mProj = *pCiIF.GetProjection();

		ID3D11DeviceContext1* pContext = pDR->GetD3DDeviceContext();

		if (world == nullptr)
		{
			//いろいろ反映
			mWorld = mScale * mRotX * mRotY * mRotZ * mPosition;
		}
		else
		{
			mWorld = *world;
		}

		mModel->Draw(pContext, *pDI.GetCommonStates(), mWorld, mView, mProj);
	}
}