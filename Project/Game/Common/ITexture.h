/*
画像管理クラスのインターフェースクラス

作成日：2021/12/01
*/
#pragma once




class ITexture
{
private:
	//座標
	DirectX::SimpleMath::Vector2 mPosition;
	//拡大率
	DirectX::SimpleMath::Vector2 mScale;
	//回転率
	float mRot;
	// 透明度
	float mAlpha;

	//テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

public:
	//コンストラクタ
	ITexture(DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector2 scale,
		float rot, float alpha);

	//初期化処理
	virtual void Initialize() = 0;

	//描画処理
	virtual void Draw() = 0;

	//画像の指定
	void SetTexture(ID3D11ShaderResourceView* texture) { mTexture = texture; }
	ID3D11ShaderResourceView* GetTexture() { return mTexture.Get(); }



	//座標の指定
	void SetPosition(DirectX::SimpleMath::Vector2 const& pos) { mPosition = pos; }
	//拡大率の指定
	void SetScale(DirectX::SimpleMath::Vector2 const& scale) { mScale = scale; }
	//回転率の指定
	void SetRot(float const& rot) { mRot = rot; }
	//透明度の指定
	void SetAlpha(float const& alpha) { mAlpha = alpha; }
	float GetAlpha()const { return mAlpha; }

	//座標の取得
	DirectX::SimpleMath::Vector2 GetPosition()const { return mPosition; }
	//拡大率の取得
	DirectX::SimpleMath::Vector2 GetScale()const { return mScale; }

protected:
	//回転率の取得
	float GetRot() { return mRot; }
};
