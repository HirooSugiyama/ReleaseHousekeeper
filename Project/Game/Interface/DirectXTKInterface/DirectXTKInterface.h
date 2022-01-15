/*
DirectXTKの汎用処理のシングルトン
制作日：2021/04/23
*/
#pragma once


namespace DirectX 
{
	class CommonStates;
	class SpriteFont;
	class SpriteBatch;
}

class DirectXtkIF final
{
private:
	//自身
	static DirectXtkIF* sDirectXtkIF;
	
	//コモンステート
	static std::unique_ptr<DirectX::CommonStates> spCommonState;
	// スプライトバッチ
	static std::unique_ptr<DirectX::SpriteBatch> spSpriteBatch;
	// スプライトフォント
	static std::unique_ptr<DirectX::SpriteFont> spSpriteFont;



	//D3Dデバイスとデバイスコンテキスト
	ID3D11Device1* spDevice;
	ID3D11DeviceContext1* spContext;

	//コピーコンストラクタ、コピー代入演算子をdelete
	DirectXtkIF(const DirectXtkIF& dxtk) = delete;
	DirectXtkIF operator=(const DirectXtkIF& dxtk) = delete;

	//コンストラクタ
	DirectXtkIF();
	//デストラクタ	
	~DirectXtkIF() = default;

public:

	//自身のインスタンス
	static DirectXtkIF& GetDirectXtkIFInstance();
	
	void Destroy()const;
	
	//各ポインタのゲッター
	DirectX::CommonStates* GetCommonStates()const;
	DirectX::SpriteBatch* GetSpriteBatch()const;
	DirectX::SpriteFont* GetSpriteFont()const;

};