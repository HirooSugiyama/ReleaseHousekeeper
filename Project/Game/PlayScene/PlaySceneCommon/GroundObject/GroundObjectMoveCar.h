/*
動き出す車のモデルを管理するクラス
作成日：2021/08/19
*/
#pragma once

//基底クラス
#include"IGroundObject.h"

//所持
#include"../ObjectModel/ObjectModel.h"


class GroundObjectMoveCar :public IGroundObject
{
private:

	//モデルの拡大率
	static const DirectX::SimpleMath::Vector3 MOVE_CAR_SCALE;

	//動く車モデルのY座標
	static const float MOVE_CAR_MODEL_POSITION_Y;

	//動く車モデル
	std::unique_ptr<ObjectModel> mpMoveCarModel;

public:
	//コンストラクタ
	GroundObjectMoveCar();

	//デストラクタ
	~GroundObjectMoveCar()override;

	//初期化
	void Initialize()override;

	//更新処理
	void Update()override;

	//描画
	void Draw()override;

	//モデルの座標を設定する
	void SetMoveCarModelPosition(DirectX::SimpleMath::Vector3 const& pos);

	//Y座標を変換する
	float GetMoveCarModelPositionY() const { return MOVE_CAR_MODEL_POSITION_Y; };

	//拡大率を取得
	DirectX::SimpleMath::Vector3 GetMoveCarScale()const { return MOVE_CAR_SCALE; }
};