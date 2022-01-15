/*
カメラ旋回フェーズ
作成日：2021/10/11
*/
#pragma once

//列挙型の使用
#include"../PlaySceneRotationCamera/RotationState.h"

//基底クラス
#include"PlayScenePhaseBase.h"

//所持
#include"Libraries/MyLibraries/RotationCamera.h"
#include"../../Common/Blinking.h"

//前方宣言
class Timer;			//カウントダウン用タイマー
class ObjectTexture;	//Skipボタン

class PScenePhaseRotationCamera :public PlayScenePhaseBase
{
private:
	//スキップボタンの座標
	static const DirectX::SimpleMath::Vector2 SKIPBOTTON_POSITION;
	//スキップボタンの拡大率
	static const DirectX::SimpleMath::Vector2 SKIPBOTTON_SCALE;

	//カウントダウン時間
	static const int COUNTDOWN_MAX_NUM;

	//PlaySceneオブジェクトへ保存用のポインタ
	PlayScene* mpPlayScene;

	//カウントダウン用タイマー
	std::unique_ptr<Timer> mpCountDownTimer;

	//旋回カメラを準備
	std::unique_ptr<RotationCamera> mpRotationCamera;

	//Skipボタン画像
	std::unique_ptr<ObjectTexture> mpSkipButton;

	//点滅クラス
	std::unique_ptr<Blinking> mpSkipButtonBlinking;

	//現在の状態
	eRotationState mState;

public:
	//コンストラクタ
	PScenePhaseRotationCamera();

	//デストラクタ
	~PScenePhaseRotationCamera();
	
	//初期化
	void Initialize(PlayScene* pPlayScene)override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//リセット処理
	void Reset()override;

private:

	//スキップ処理
	bool Skip();

};