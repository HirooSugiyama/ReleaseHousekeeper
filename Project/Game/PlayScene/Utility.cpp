/*
汎用処理をまとめたファイル
作成日：2021/08/31
*/
#include"pch.h"
#include"Utility.h"

//文字フォントサイズ
//大
const float Utility::STRING_SIZE_BIG = 3.5f;
//中
const float Utility::STRING_SIZE_MEDIUM = 3.f;
//小
const float Utility::STRING_SIZE_SMALL = 2.f;
//極小
const float Utility::STRING_SIZE_MINIMUM = 1.f;


//文字バッファーサイズ
const size_t Utility::BUFFER_SIZE = 32;


//例外数字
const int Utility::EXCEPTION_NUM = -1;

//拡大率を半分にする
const int Utility::SCALE_HALF = 2;


/*==============================
文字列を描画する共通関数
引数：描画する数字
		座標
		色
		文字サイズ
==============================*/
void Utility::DrawString(int const& drawNum,
						DirectX::SimpleMath::Vector2 const& stringPosition,
						DirectX::FXMVECTOR const& stringColor,
						float const& stringSize,
						int const& secondNum)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	wchar_t buf[32];

	swprintf_s(buf, Utility::BUFFER_SIZE, L" %d", drawNum);
	if (secondNum != EXCEPTION_NUM)
	{
		swprintf_s(buf, Utility::BUFFER_SIZE, L" %d:%d", drawNum, secondNum);
	}

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero, 
		stringSize
	);
}

/*==============================
文字列を描画する共通関数
引数：描画する文字列
		座標
		色
		文字サイズ
==============================*/
void Utility::DrawString(wchar_t const* string,
	DirectX::SimpleMath::Vector2 const& stringPosition,
	DirectX::FXMVECTOR const& stringColor,
	float const& stringSize)
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		string,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero,
		stringSize
	);
}
