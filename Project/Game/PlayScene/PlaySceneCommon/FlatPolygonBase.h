/*
平面ポリゴン描画基底クラス
作成日：2021/11/13
*/
#pragma once
#include <SimpleMath.h>




class FlatPolygonBase
{
protected:


	//コンストラクタ
	FlatPolygonBase() = default;
	//デストラクタ
	virtual ~FlatPolygonBase() = default;

public:

	//初期化
	virtual void Initialize() = 0;

	//描画
	virtual void Draw(DirectX::SimpleMath::Vector3 pos) = 0;

	//拡大率のアクセサ
	virtual void SetScale(DirectX::SimpleMath::Vector2 scale) = 0;


};
