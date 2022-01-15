/*
旋回カメラ
作成日：2021/10/11
*/
#include "pch.h"
#include "RotationCamera.h"
#include"CameraBase.h"


//カメラの移動スピード
const float RotationCamera::CAMERA_MOVE_SPEED = 0.3f;


//カメラ初期座標
const DirectX::SimpleMath::Vector3 RotationCamera::CAMERA_INIT_EYE_POSITION(0.f, 30.f, 61.f);
//ターゲット座標
const DirectX::SimpleMath::Vector3 RotationCamera::CAMERA_INIT_TARGET(0.0f, 1.0f, -15.0f);
//カメラの回転速度
const float RotationCamera::CAMERA_ROT_SPEED = 0.005f;

//注視点とカメラ座標の距離
const DirectX::SimpleMath::Vector3 RotationCamera::ROT_CAMERA_DISTANCE(0.0f, 1.0f, 6.0f);

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
RotationCamera::RotationCamera()
	: 
	MoveCamera(CAMERA_INIT_EYE_POSITION, CAMERA_INIT_TARGET),
	mRefEye(CAMERA_INIT_EYE_POSITION),
	mRefTarget(CAMERA_INIT_TARGET),
	mRot()
{
	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
}


//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
RotationCamera::~RotationCamera()
{
}

//-------------------------------------------------------------------
// 更新処理
//-------------------------------------------------------------------
void RotationCamera::Update()
{
	DirectX::SimpleMath::Vector3 addPosition =
		DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION,
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);
	mRot += CAMERA_ROT_SPEED;
	CameraBase::SetEyePosition(CameraBase::GetTargetPosition() + addPosition);
	
	
	CameraBase::CalculateViewMatrix();
	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();
	//シングルトンへ情報を保存
	pCiIF.SetView(CameraBase::GetViewMatrix());
	pCiIF.SetProjection(CameraBase::GetProjectionMatrix());
}

//-------------------------------------------------------------------
// 移動処理
//-------------------------------------------------------------------
void RotationCamera::Move()
{
	// キー入力情報を取得する
	auto pKey = KeyTracker::GetKeyTrackerInstance();

	//移動用変数
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 addPosition = DirectX::SimpleMath::Vector3::Zero;

	//各移動方向への入力処理
	if (pKey->WalkForward())
	{
		vel.z = -CAMERA_MOVE_SPEED;
	}
	if (pKey->WalkBack())
	{
		vel.z = CAMERA_MOVE_SPEED;
	}
	//左へ移動
	if (pKey->WalkLeft())
	{
		vel.x = -CAMERA_MOVE_SPEED;
	}
	//右へ移動
	if (pKey->WalkRight())
	{
		vel.x = CAMERA_MOVE_SPEED;
	}

	//回転処理
	if (pKey->LeftRotation())
	{
		mRot -= CAMERA_ROT_SPEED;
		addPosition = DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION,
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);

	}
	if (pKey->RightRotation())
	{
		mRot += CAMERA_ROT_SPEED;
		addPosition = DirectX::SimpleMath::Vector3::Transform
		(
			CAMERA_INIT_EYE_POSITION, 
			DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
		);
	}


	// 速度加算
	vel = DirectX::SimpleMath::Vector3::Transform
	(
		vel,
		DirectX::SimpleMath::Matrix::CreateRotationY(mRot)
	);

	//もし移動していたら
	if (addPosition != DirectX::SimpleMath::Vector3::Zero)
	{
		this->SetRefEyePosition(this->GetRefTargetPosition() + addPosition);
	}
	if (vel != DirectX::SimpleMath::Vector3::Zero)
	{
		mRefEye += vel;
		mRefTarget += vel;
	}

	CameraInfoIF& pPvIF = CameraInfoIF::GetCameraInfoIFInstance();
	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition() +
		(mRefTarget - CameraBase::GetTargetPosition()) 
		* 0.05f
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition())
		* 0.05f
	);


	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
	//シングルトンへ情報を保存
	pPvIF.SetView(CameraBase::GetViewMatrix());
	pPvIF.SetProjection(CameraBase::GetProjectionMatrix());
}

//-------------------------------------------------------------------
// リセット処理
//-------------------------------------------------------------------
void RotationCamera::Reset(DirectX::SimpleMath::Vector3 pos)
{

	CameraInfoIF& pCiIF = CameraInfoIF::GetCameraInfoIFInstance();

	//注視点とカメラ位置を調節
	this->SetRefTargetPosition(pos - ROT_CAMERA_DISTANCE);

	CameraBase::SetTargetPosition
	(
		CameraBase::GetTargetPosition()+
		(mRefTarget - CameraBase::GetTargetPosition()) * MoveCamera::GetSpringPower()
	);

	this->SetRefEyePosition
	(
		pos + CAMERA_INIT_EYE_POSITION - ROT_CAMERA_DISTANCE
	);

	CameraBase::SetEyePosition
	(
		CameraBase::GetEyePosition() +
		(mRefEye - CameraBase::GetEyePosition()) * MoveCamera::GetSpringPower()
	);

	//回転角度をリセットする
	mRot = 0.f;

	CameraBase::CalculateViewMatrix();
	CameraBase::CalculateProjectionMatrix();
	//シングルトンへ情報を保存
	pCiIF.SetView(GetViewMatrix());
	pCiIF.SetProjection(GetProjectionMatrix());
}
