/*
ビューと射影とカメラ座標を保存するためのインターフェース
*/

#include<pch.h>
#include "CameraInfoInterface.h"
//クラス外部で初期化
CameraInfoIF* CameraInfoIF::sCameraInfoIF = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoIF::spView = nullptr;
std::unique_ptr<DirectX::SimpleMath::Matrix> CameraInfoIF::spProj = nullptr;
std::unique_ptr<DirectX::SimpleMath::Vector3> CameraInfoIF::spCameraPosition = nullptr;

/*=========================================
コンストラクタ
=========================================*/
CameraInfoIF::CameraInfoIF()
{
	spView = std::make_unique<DirectX::SimpleMath::Matrix>();
	spProj = std::make_unique<DirectX::SimpleMath::Matrix>();
	spCameraPosition = std::make_unique<DirectX::SimpleMath::Vector3>();
}

/*=========================================
インスタンスを取得
返り値：自身のインスタンス
=========================================*/
CameraInfoIF& CameraInfoIF::GetCameraInfoIFInstance()
{
	if (sCameraInfoIF == nullptr)
	{
		sCameraInfoIF = new CameraInfoIF();
	}
	return *sCameraInfoIF;
}

/*=========================================
自身の内容削除処理
=========================================*/
void CameraInfoIF::Destroy() const
{
	if (sCameraInfoIF != nullptr) {
		delete sCameraInfoIF;
		sCameraInfoIF = nullptr;
	}
}

/*==========================
ビュー行列を設定する関数
引数：Matrix型	ビュー行列
===========================*/
void CameraInfoIF::SetView(DirectX::SimpleMath::Matrix const& view)
{
	*spView = view;
}

/*=========================================
射影行列を設定する関数
引数：Matrix型　射影行列
=========================================*/
void CameraInfoIF::SetProjection(DirectX::SimpleMath::Matrix const& proj)
{
	*spProj = proj;
}

/*=========================================
現在のカメラの座標を設定する関数
引数：Vector型　カメラの座標
=========================================*/
void CameraInfoIF::SetCameraPosition(DirectX::SimpleMath::Vector3 const& cameraPosition)
{
	*spCameraPosition = cameraPosition;
}

/*=================
取得関数
=================*/
DirectX::SimpleMath::Matrix* CameraInfoIF::GetView() const
{
	return spView.get();
}

DirectX::SimpleMath::Matrix* CameraInfoIF::GetProjection() const
{
	return spProj.get();
}

DirectX::SimpleMath::Vector3* CameraInfoIF::GetCameraPosition() const
{
	return spCameraPosition.get();
}
