/*
敵行動パターン～敵出現時の演出～
作成日：2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

//前方宣言
class EffectSpriteTexture;
class Camera;

class EStateAppearance :public EnemyStateBase
{
private:

	//モデル移動スピード
	static const float ENEMY_MODEL_MOVE_VELOCITY;
	//モデルY軸最大値
	static const float ENEMY_MODEL_MAX_POSITIONY;

	//出現エフェクト用定数


	//保存用変数
	Enemy* mpEnemy;
	Camera* mpCamera;

	//フラグ管理用変数
	EffectSpriteTexture* mpAppearanceEffect;


public:
	//コンストラクタ
	EStateAppearance();

	//デストラクタ
	~EStateAppearance()override;

	//初期化処理
	void Initialize(Enemy* pEnemy)override;

	//更新処理
	void Update()override;

	//描画処理
	void Draw()override;

	//State開始時の初期化処理
	void Reset()override;

	//カメラのポインタを保存
	void SetCameraPointer(Camera* pCamera)
	{
		mpCamera = pCamera;
	}

private:
	//当たり判定を設定する
	virtual void SetAABBCollider() {}

	//エフェクトの設定
	void SetEffect();

};