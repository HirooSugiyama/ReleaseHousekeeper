/*
タイトルシーン
*/
#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"
#include "Game/TEST/FbxMeshFile.h"




enum class STATE
{
	BEGIN,
	DRAW,
	END,
};


namespace DirectX
{
	class BasicEffect;
}

class Camera;
class GridFloor;

class TESTScene :public IScene
{
private:
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;
	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;
	//モデル
	FbxMeshFile* mModel;

	// デバッグカメラ
	std::unique_ptr<Camera> mpCamera;

	// グリッド床
	std::unique_ptr<GridFloor> mpGridFloor;

	//行列
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;


	//現在の描画状態
	STATE mState;

public:
	//コンストラクタ
	TESTScene();
	//デストラクタ
	~TESTScene();
	//初期化
	void Initialize()override;
	//更新
	GAME_SCENE Update(const DX::StepTimer& timer)override;
	//描画
	void Draw()override;
	//終了処理
	void Finalize()override;



	//描画開始と終了
	/**
	* @brief 描画開始関数@n
	* 描画処理を行う場合、必ずこの関数の後に実行する@n
	* 実行しないと描画されない
	*/
	void StartRendering();

	/**
	* @brief 描画終了関数@n
	* 描画処理が完了した場合、必ずこの関数を実行する
	* 実行しないと描画内容が反映されない
	*/
	void FinishRendering();


	void SetUpContext();

};
