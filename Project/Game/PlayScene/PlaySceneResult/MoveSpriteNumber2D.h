/*
動く文字画像クラス

作成日：2021/12/17
*/
#pragma once

#include"MoveNumber.h"
#include"../../Common/SpriteNumber/SpriteNumber2D.h"

//所持

class MoveSpriteNumber2D
{
private:

	//動く数字クラス
	std::unique_ptr<MoveNumber> mpMoveNumber;

	//数字画像クラス
	std::unique_ptr<SpriteNumber2D> mpSpriteNumber2D;

	//描画座標
	DirectX::SimpleMath::Vector2 mDrawPosition;

public:

	//コンストラクタ
	MoveSpriteNumber2D();
	//デストラクタ
	~MoveSpriteNumber2D();
	//初期化処理
	void Initialize(std::string const& textureKey,int const& firstNum,
						float const& moveSecondSpeed, int const& maxNum);
	//更新処理
	int Update(DX::StepTimer const& timer);
	//描画処理
	void Draw();

	//座標を指定
	void SetPosition(DirectX::SimpleMath::Vector2 pos) { mDrawPosition = pos; }
	//拡大率指定
	void SetScale(float scale) { mpSpriteNumber2D->SetScale(scale); }

	//中心位置を変更
	void SetAlign(eAlign algin) { mpSpriteNumber2D->SetAlign(algin); }

	//値を最大値に変更する
	void ForcedChangeMoveNum() { mpMoveNumber->ForcedChangeMoveNum(); }
};
