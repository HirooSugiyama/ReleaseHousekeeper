/*
ビューと射影とカメラ座標を保存するためのインターフェース
*/

#pragma once
#include <SimpleMath.h>


class CameraInfoIF
{
private:
	static CameraInfoIF* sCameraInfoIF;

	static std::unique_ptr<DirectX::SimpleMath::Matrix> spView;
	static std::unique_ptr<DirectX::SimpleMath::Matrix> spProj;
	static std::unique_ptr<DirectX::SimpleMath::Vector3> spCameraPosition;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	CameraInfoIF( CameraInfoIF const& pv) = delete;
	CameraInfoIF operator=( CameraInfoIF const& pv) = delete;


	//コンストラクタ
	CameraInfoIF();
	//デストラクタ
	~CameraInfoIF()=default;
public:
	//自身のインスタンス
	static CameraInfoIF& GetCameraInfoIFInstance();

	void Destroy()const;

	//設定関数
	void SetView(DirectX::SimpleMath::Matrix const& view);
	void SetProjection(DirectX::SimpleMath::Matrix const& proj);
	void SetCameraPosition(DirectX::SimpleMath::Vector3 const& cameraPosition);

	//取得関数
	DirectX::SimpleMath::Matrix* GetView() const;
	DirectX::SimpleMath::Matrix* GetProjection() const;
	DirectX::SimpleMath::Vector3* GetCameraPosition() const;
};