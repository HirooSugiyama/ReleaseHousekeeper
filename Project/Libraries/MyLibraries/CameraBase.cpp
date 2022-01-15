/*
カメラの基底クラス
作成日：2021/10/24
*/
#include"pch.h"
#include "CameraBase.h"
#include <DeviceResources.h>


// カメラの距離
const float CameraBase::DEFAULT_CAMERA_DISTANCE = 5.0f;

/*==================================
コンストラクタ
引数：カメラ座標、ターゲットの座標
==================================*/
CameraBase::CameraBase(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target)
	:
	mView(DirectX::SimpleMath::Matrix::Identity),
	mEye(eye),
	mTarget(target),
	mUp(0.0f, 1.0f, 0.0f)
{
}

/*=========================
ビュー行列の算出
=========================*/
void CameraBase::CalculateViewMatrix()
{
	mView = DirectX::SimpleMath::Matrix::CreateLookAt(mEye, mTarget, mUp);
}

/*=========================
プロジェクション行列の算出
=========================*/
void CameraBase::CalculateProjectionMatrix()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

	// ウィンドウサイズの取得
	float width = static_cast<float>(pDR->GetOutputSize().right);
	float height = static_cast<float>(pDR->GetOutputSize().bottom);

	// 画角
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);
	// 画面縦横比
	float aspectRatio = width / height;
	// カメラから一番近い投影面
	float nearPlane = 1.0f;  
	// カメラから一番遠い投影面
	float farPlane = 1000.0f;

	//射影行列を求める
	mProjection = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);
}


void CameraBase::CalculationMatrix()
{
	this->CalculateViewMatrix();
	this->CalculateProjectionMatrix();
}
