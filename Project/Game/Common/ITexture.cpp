/*
画像管理クラスのインターフェースクラス

作成日：2021/12/01
*/

#include"pch.h"
#include"ITexture.h"

/*===============================================
コンストラクタ
引数：座標、拡大率、回転率、透明度
===============================================*/
ITexture::ITexture(DirectX::SimpleMath::Vector2 pos,
				DirectX::SimpleMath::Vector2 scale,
				float rot, float alpha)
	:
	mPosition(pos),
	mScale(scale),
	mRot(rot),
	mAlpha(alpha),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}
