/*
汎用処理をまとめたヘッダーファイル
作成日：2021/08/31
*/
#pragma once

//3D情報を2D座標で使用する際X,Zを使用するための変換用構造体
struct Vector2XZ
{
	float x;
	float z;

};


struct Utility
{
	//文字フォントサイズ
	//大
	static const float STRING_SIZE_BIG;
	//中
	static const float STRING_SIZE_MEDIUM;
	//小
	static const float STRING_SIZE_SMALL;
	//極小
	static const float STRING_SIZE_MINIMUM;

	//文字バッファーサイズ
	static const size_t BUFFER_SIZE;
	

	//例外数字
	static const int EXCEPTION_NUM;

	//拡大率を半分にする
	static const int SCALE_HALF;

	//文字を描画する関数
	static void DrawString
	(
		int const& drawNum= EXCEPTION_NUM,
		DirectX::SimpleMath::Vector2 const& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		DirectX::FXMVECTOR const& stringColor= DirectX::Colors::White,
		float const& stringSize= STRING_SIZE_MEDIUM,
		int const& secondNum=EXCEPTION_NUM
	);
	static void DrawString
	(
		wchar_t const* string=L"none",
		DirectX::SimpleMath::Vector2 const& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		DirectX::FXMVECTOR const& stringColor= DirectX::Colors::White,
		float const& stringSize= STRING_SIZE_MEDIUM
	);

};
