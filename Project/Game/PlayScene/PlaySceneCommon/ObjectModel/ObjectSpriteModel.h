/*
スプライトモデル描画クラス
作成日：2021/04/18
*/
#pragma once

#include"IModel.h"

namespace DirectX
{
	class SpriteBatch;
}

class ObjectSpriteModel:public IModel
{
protected:
	//定数
	// モデルのスプライト番号が最大値を超えた時反復処理をするための係数
	static const int SPRITE_REVERSE_NUM;	//詳しくはCPPにて
	
	//変数

	// コモンステート
	DirectX::CommonStates* mpCommonState;
	// スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;
	// スプライトフォント
	DirectX::SpriteFont* mpSpriteFont;

	//モデル関係
	DirectX::SimpleMath::Matrix mWorld;

	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	std::unique_ptr<DirectX::IEffectFactory> mFxFactory;
	std::vector<DirectX::Model*> mModel;

	//座標
	DirectX::SimpleMath::Matrix mPosition;
	DirectX::SimpleMath::Matrix mScale;
	DirectX::SimpleMath::Matrix mRot;

	DirectX::SimpleMath::Vector3 mPosition3;
	DirectX::SimpleMath::Vector3 mScale3;

	//表示フラグ:true	表示	false:非表示
	bool mDrawFlag;

	//スプライトタイマー
	int mSpriteTimer;
	//タイマー(固定値)
	int mConstTimer;
	//スプライトタイマー稼働フラグ
	bool mSpriteFlag;
	//現在使用しているモデルの番号
	int mUseModelNum;

	//スプライト最大数
	int mMaxSpriteNum;

	//スプライト反転フラグ
	bool mReverseFlag;

	//関数
public:
	//コンストラクタ
	ObjectSpriteModel(int const& maxspritenum);

	//デストラクタ
	~ObjectSpriteModel();

	//モデルの指定
	void SetSpriteModel(int const& spritenum,DirectX::Model* model);
	//座標の指定
	void SetPosition( DirectX::SimpleMath::Vector3 const& pos);
	//拡大率の指定
	void SetScale( DirectX::SimpleMath::Vector3 const& scale);
	//回転の指定
	void SetRotationX(float const& rot);
	void SetRotationY(float const& rot);
	void SetRotationZ(float const& rot);

	//座標の取得
	DirectX::SimpleMath::Vector3 GetPosition()const;
	//拡大率の取得
	DirectX::SimpleMath::Vector3 GetScale()const;

	//移動
	void Move(DirectX::SimpleMath::Vector3 const& vel);

	//更新処理
	virtual void Update()override {}
	void SpriteUpdate();
	//描画
	virtual void Draw(DirectX::SimpleMath::Matrix* world = nullptr)override;

	//表示非表示の切り替えのアクセサ
	bool GetDrawFlag() const { return mDrawFlag; }
	void SetDrawFlag(bool const& flag) { mDrawFlag = flag; }

	//現在のモデルの番号を返す
	int GetUseModelNum()const { return mUseModelNum; }

	//スプライトの周期の指定
	void SetConstTimer(int const& timer) { mConstTimer = timer; }

	//スプライトモデルを回すかどうかのアクセサ
	void SetSpriteFlag(bool const& flag) { mSpriteFlag = flag; }
		
	//スプライトモデルの最大数
	void SetMaxSpriteNum(int const& num) { mMaxSpriteNum = num; }

};
