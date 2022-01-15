/*
スプライトモデル描画クラス
作成日：2021/04/18
*/
#include<pch.h>
#include"ObjectSpriteModel.h"

// モデルのスプライト番号が最大値を超えた時反復処理をするための係数
const int ObjectSpriteModel::SPRITE_REVERSE_NUM = 2;
/*
※スプライト値が最大値を超えた場合に引くための係数
・直前でモデル要素数の最大値を超えているため範囲内に戻すための処理として[1]減らす。
・スプライト１サイクルが変わらない状態で回ってしまうためさらに[1]減らす。
*/


/*======================================
コンストラクタ
引数：スプライトの最大数
========================================*/

ObjectSpriteModel::ObjectSpriteModel(int const& maxspritenum)
	:
	IModel(),
	mpCommonState(nullptr),
	mpSpriteBatch(nullptr),
	mpSpriteFont(nullptr),
	mWorld(),
	mView(),
	mProj(),
	mFxFactory(),
	mModel{},
	mPosition(),
	mScale(),
	mRot(),
	mPosition3(),
	mScale3(),
	mDrawFlag(true),
	mSpriteTimer(0),
	mConstTimer(0),
	mSpriteFlag(true),
	mUseModelNum(0),
	mMaxSpriteNum(maxspritenum),
	mReverseFlag(false)
{
	// コモンステート::D3Dレンダリング状態オブジェクト
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


	mScale3 = DirectX::SimpleMath::Vector3::One;
	mPosition3 = DirectX::SimpleMath::Vector3::Zero;
	//未代入の回避
	mWorld = DirectX::SimpleMath::Matrix::CreateScale(mScale3);
	mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);

	//メモリ確保
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mModel.push_back(nullptr);
	}
}

/*===================================
デストラクタ
===================================*/
ObjectSpriteModel::~ObjectSpriteModel()
{
}

/*=============================================
モデルの指定
引数：スプライトの最大数、モデル情報
========================================================*/
void ObjectSpriteModel::SetSpriteModel(int const& spritenum, DirectX::Model* model)
{
	mModel[spritenum] = model;
}

/*============
座標の指定
引数：座標
==============*/
void ObjectSpriteModel::SetPosition( DirectX::SimpleMath::Vector3 const& pos)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(pos);

		mPosition3 = pos;
	}
}

/*============
拡大率の指定
引数：座標
==============*/
void ObjectSpriteModel::SetScale(DirectX::SimpleMath::Vector3 const& scale)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mScale = DirectX::SimpleMath::Matrix::CreateScale(scale);
		mScale3 = scale;
	}
}

/*============
回転の指定
引数：回転率
==============*/
void ObjectSpriteModel::SetRotationX(float const& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(rot));
	}	
}
void ObjectSpriteModel::SetRotationY(float const& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(rot));
	}	
}
void ObjectSpriteModel::SetRotationZ(float const& rot)
{
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mRot = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rot));
	}
}


/*================================
座標の取得
返り値：座標(x,y,z)
==================================*/
DirectX::SimpleMath::Vector3 ObjectSpriteModel::GetPosition()const 
{
	return mPosition3;
}

/*================================
拡大率の取得
返り値：拡大率(x,y,z)
==================================*/
DirectX::SimpleMath::Vector3 ObjectSpriteModel::GetScale()const
{
	return mScale3;
}


/*===================
移動
引数：力ベクトル
=====================*/
void ObjectSpriteModel::Move(DirectX::SimpleMath::Vector3 const& vel)
{
	//変数の宣言
	DirectX::SimpleMath::Vector3 vel3 = vel;

	
	for (int i = 0; i < mMaxSpriteNum; i++)
	{
		mPosition = DirectX::SimpleMath::Matrix::CreateTranslation(mPosition3);
		//現在の座標に引数の座標を追加する
		mPosition3 += vel3;
	}	
}

/*============
更新処理
==============*/
void ObjectSpriteModel::SpriteUpdate() 
{
	//もしスプライトを回すフラグが立っていなかったら処理を通さない
	if (!mSpriteFlag)
	{
		return;
	}

	//スプライトタイマーを回す
	mSpriteTimer++;
	if (!mReverseFlag)
	{
		//もしスプライトを回すタイミングが来たら
		if (mSpriteTimer == mConstTimer)
		{
			//タイマーは初期化する
			mSpriteTimer = 0;
			mUseModelNum++;
			//もし使用モデルがモデル最大数を越えたら
			if (mUseModelNum >= mMaxSpriteNum) 
			{
				mUseModelNum = mMaxSpriteNum - SPRITE_REVERSE_NUM;
				mReverseFlag = true;
			}
		}
	}
	else
	{
		//もしスプライトを回すタイミングが来たら
		if (mSpriteTimer == mConstTimer)
		{
			//タイマーは初期化する
			mSpriteTimer = 0;
			mUseModelNum--;
			//もし使用モデルがモデル最大数を越えたら
			if (mUseModelNum <= 0) 
			{
				mReverseFlag = false;
			}
		}
	}
}


/*==================================
描画
引数：ワールド座標(無くても可)
======================================*/
void ObjectSpriteModel::Draw(DirectX::SimpleMath::Matrix* world)
{
	if (mDrawFlag)
	{
		//インスタンスの取得
		DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();


		DirectXtkIF& pDI = DirectXtkIF::GetDirectXtkIFInstance();
		CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();


		mView = *pCiIF.GetView();

		mProj = *pCiIF.GetProjection();

		if (world == nullptr)
		{
			//いろいろ反映
			mWorld = mRot * mScale * mPosition;
		}

		ID3D11DeviceContext1* pContext = pDR->GetD3DDeviceContext();

		mModel[mUseModelNum]->Draw
		(pContext, *pDI.GetCommonStates(), mWorld, mView, mProj);
	}
}
