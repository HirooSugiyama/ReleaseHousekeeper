/*
DirectXTKの汎用処理のシングルトン化
制作日：2021/04/23
*/
#include<pch.h>
#include "DirectXTKInterface.h"


//クラス外部で初期化
DirectXtkIF* DirectXtkIF::sDirectXtkIF = nullptr;
std::unique_ptr<DirectX::CommonStates> DirectXtkIF::spCommonState = nullptr;
std::unique_ptr<DirectX::SpriteBatch> DirectXtkIF::spSpriteBatch = nullptr;
std::unique_ptr<DirectX::SpriteFont> DirectXtkIF::spSpriteFont = nullptr;

/*=========================================
コンストラクタ
=========================================*/
DirectXtkIF::DirectXtkIF()
	:
	spDevice(),
	spContext()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	// D3Dデバイスとデバイスコンテキストの取得
	spDevice = pDR->GetD3DDevice();
	spContext = pDR->GetD3DDeviceContext();

	spCommonState = std::make_unique<DirectX::CommonStates>(spDevice);
	
	spSpriteBatch = std::make_unique<DirectX::SpriteBatch>(spContext);
	
	spSpriteFont = std::make_unique<DirectX::SpriteFont>(spDevice, L"Resources/Fonts/myfile.spritefont");
}
/*=========================================
インスタンスの取得
戻り値：自身のインスタンス
=========================================*/
DirectXtkIF& DirectXtkIF::GetDirectXtkIFInstance()
{
	if (sDirectXtkIF == nullptr)
	{
		sDirectXtkIF = new DirectXtkIF();
	}
	return *sDirectXtkIF;
}
/*=========================================
自身の削除
=========================================*/
void DirectXtkIF::Destroy()const
{
	delete sDirectXtkIF;
	sDirectXtkIF = nullptr;
}


/*=========================================
コモンステートのゲッター
返り値：CommonStates型　コモンステート
=========================================*/
DirectX::CommonStates* DirectXtkIF::GetCommonStates() const 
{
	return spCommonState.get();
}
/*=========================================
スプライトバッチの取得
返り値：SpriteBatch型　スプライトバッチ
=========================================*/
DirectX::SpriteBatch* DirectXtkIF::GetSpriteBatch() const 
{
	return spSpriteBatch.get();
}
/*=========================================
スプライトフォントの取得
返り値：SpriteFont型　スプライトフォント
=========================================*/
DirectX::SpriteFont* DirectXtkIF::GetSpriteFont()const 
{
	return spSpriteFont.get();
}