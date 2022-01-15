/*
タイトルシーン
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

//所持
#include"Game/Common/Cloud.h"

class TitleScene : public IScene
{
private:

	//ロゴの座標
	static const DirectX::SimpleMath::Vector2 TITLE_LOGO_POSITION;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpLogo;

	std::unique_ptr<Cloud> mpCloud;

	//音楽ID
	int mBGMID;

public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 初期化
	void Initialize() override;

	// 更新
	eGameScene Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

private:
	//BGMを流す
	void PlayBGM()override;

	//BGMを止める
	void StopBGM()override;
};