/*
アニメーション専用モデル描画クラス
作成日：2021/09/05
*/
#pragma once

#include"../../ObjectModel/IModel.h"

namespace DirectX
{
	class SpriteBatch;
}

class AnimationModel:public IModel
{
protected:
	//定数

	//初期化時の定数
	static const DirectX::SimpleMath::Vector3 INIT_POSITION;
	//未使用時の定数
	static const DirectX::SimpleMath::Vector3 NOT_USE_POSITION;
	
	//変数

	// コモンステート
	DirectX::CommonStates* mpCommonState;
	// スプライトバッチ
	DirectX::SpriteBatch* mpSpriteBatch;
	// スプライトフォント
	DirectX::SpriteFont* mpSpriteFont;

	//モデル関係
	DirectX::SimpleMath::Matrix mWorld;

	//ビュー行列
	DirectX::SimpleMath::Matrix mView;
	//射影行列
	DirectX::SimpleMath::Matrix mProj;

	//エフェクトファクトリー
	std::unique_ptr<DirectX::IEffectFactory> mFxFactory;
	//モデルの保存先
	DirectX::Model* mModel;

	//座標
	DirectX::SimpleMath::Matrix mPosition;
	DirectX::SimpleMath::Matrix mScale;
	DirectX::SimpleMath::Matrix mRotX;
	DirectX::SimpleMath::Matrix mRotY;
	DirectX::SimpleMath::Matrix mRotZ;

	//表示フラグ:true	表示	false:非表示
	bool mDrawFlag;

	//関数
public:
	//コンストラクタ
	AnimationModel();

	//デストラクタ
	~AnimationModel();

	//モデルの指定
	void SetModel(DirectX::Model* model);
	//モデル情報のアクセサ
	DirectX::Model* GetModel()const  {return mModel;}

	//座標の指定
	void SetPosition(DirectX::SimpleMath::Vector3 const& pos);
	//拡大率の指定
	void SetScale(DirectX::SimpleMath::Vector3 const& scale);
	//回転の指定
	void SetRotationX(float const& rot);
	void SetRotationY(float const& rot);
	void SetRotationZ(float const& rot);

	//座標の取得
	DirectX::SimpleMath::Matrix GetPosition()const;

	//拡大率の取得
	DirectX::SimpleMath::Matrix GetScale()const;

	//回転の指定
	DirectX::SimpleMath::Matrix GetRotationX()const;
	DirectX::SimpleMath::Matrix GetRotationY()const;
	DirectX::SimpleMath::Matrix GetRotationZ()const;


	//ワールド座標の設定
	void SetWorld(DirectX::SimpleMath::Matrix const& world);


	//更新処理
	virtual void Update()override {};
	//描画
	virtual void Draw(DirectX::SimpleMath::Matrix* world = nullptr)override;

	//表示非表示の切り替えのアクセサ
	bool GetDrawFlag() const { return mDrawFlag; }
	void SetDrawFlag(bool const&flag) { mDrawFlag = flag; }

};
