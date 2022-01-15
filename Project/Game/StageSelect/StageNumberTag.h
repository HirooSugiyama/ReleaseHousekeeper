/*
ステージ選択タグ
作成日：2021/10/21
*/
#pragma once

//所持
#include"../Common/ObjectTexture.h"

class StageNumberTag
{
private:
	//画像拡大率
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//画像描画位置から数字描画位置を算出するための定数
	static const DirectX::SimpleMath::Vector2 NUM_SHIFT;


	//画像描画位置
	DirectX::SimpleMath::Vector2 mDrawPosition;


	//ユニークポインタ
	std::unique_ptr<ObjectTexture> mpBackGround;

	//描画文字
	int mDrawStageString;

public:

	//コンストラクタ
	StageNumberTag();
	//デストラクタ
	~StageNumberTag();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw(bool const& flag=true);

	//描画位置の指定
	void SetPosition(DirectX::SimpleMath::Vector2 const& pos);

	//ステージ番号のアクセサ
	void SetStageNum(int const& i) { mDrawStageString = i; }

};
