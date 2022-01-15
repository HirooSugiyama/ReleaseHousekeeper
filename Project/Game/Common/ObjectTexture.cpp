/*
目的の場所に画像を平面描画するクラス
(単一画像はこっち)
作成日：2021/06/05
*/
#include "pch.h"
#include "ObjectTexture.h"

/*=======================================
コンストラクタ
引数：	pos(座標)、scale(拡大率)
		rot(回転率)、alpha(透明度)
=======================================*/
ObjectTexture::ObjectTexture(
	DirectX::SimpleMath::Vector2 pos,
	DirectX::SimpleMath::Vector2 scale,
	float rot, float alpha)
	:
	ITexture(pos, scale,rot,alpha),
	mColor{ DirectX::SimpleMath::Vector4::One},
	mpSpriteBatch(nullptr)
{
	mColor.w = ITexture::GetAlpha();
}

/*=========================
デストラクタ
=========================*/
ObjectTexture::~ObjectTexture()
{
}

/*=========================
初期化
=========================*/
void ObjectTexture::Initialize()
{
	DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();
	
	//ポインタの保存
	mpSpriteBatch = pDxIF.GetSpriteBatch();
}

/*========================
描画
=========================*/
void ObjectTexture::Draw()
{
	//α値を設定する
	mColor.w = ITexture::GetAlpha();

	//描画
	mpSpriteBatch->Draw(ITexture::GetTexture(),
		ITexture::GetPosition(),
		nullptr,
		mColor,
		ITexture::GetRot(),
		DirectX::SimpleMath::Vector2::One,
		ITexture::GetScale());
}
