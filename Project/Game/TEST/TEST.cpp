/*
タイトルシーン
*/

#include "pch.h"

#include <WICTextureLoader.h>
#include <SimpleMath.h>

#include "../GameMain.h"
#include "DeviceResources.h"

#include "TEST.h"
#include <fbxsdk.h>

#include<SimpleMath.h>

#include "C:/DirectXTK/Inc/Effects.h"

#include "Libraries/MyLibraries/Camera.h"
#include "Game/PlayScene/PVInterface/PVInterface.h"
#include "Libraries/MyLibraries/GridFloor.h"
#include "Game/PlayScene/DirectXTKInterface/DirectXTKInterface.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
TESTScene::TESTScene()
	:mModel(nullptr)
	,mView()
	,mProj()
	,mState(STATE::BEGIN)
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
TESTScene::~TESTScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void TESTScene::Initialize()
{

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	ProViewIF& pPvIF = ProViewIF::GetProViewIFInstance();


	// D3Dデバイスとデバイスコンテキストの取得
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// コモンステート::D3Dレンダリング状態オブジェクト
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// スプライトバッチ::デバッグ情報の表示に必要
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	fbxsdk::FbxManager* fbx_manager = fbxsdk::FbxManager::Create();


	/*ベーシックエフェクトの管理*/
	mpBasicEffect = std::make_unique<BasicEffect>(device);


	//頂点情報を決定するために必要な情報
	mpBasicEffect->SetLightingEnabled(false);		//ライトOFF
	mpBasicEffect->SetTextureEnabled(true);			//テクスチャON
	mpBasicEffect->SetVertexColorEnabled(false);	//頂点カラーOFF


	mModel = new FbxMeshFile();
	
	mModel->GetVertexShader()->Create(device, "Resources/Shader/VertexShader.cso");
	mModel->GetPixelShader()->Create(device, "Resources/Shader/PixelShader.cso");


	mModel->Load(
		"Resources/Models/Cube02.fbx",
		device,
		mModel->GetVertexShader());


	fbx_manager->Destroy();


	// カメラの作成
	mpCamera = std::make_unique<Camera>();


	//シングルトンから取得(取得と同時にカメラから値を貰い保存する)
	pPvIF.SetView(mpCamera->GetViewMatrix());
	pPvIF.SetProjection(mpCamera->GetProjectionMatrix());
	mView = *pPvIF.GetView();
	mProj = *pPvIF.GetProjection();




	// グリッドの作成
	mpGridFloor = std::make_unique<GridFloor>(
		device,
		context,
		10,		// 分割数X
		10		// 分割数Y
		);

	
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE TESTScene::Update(const DX::StepTimer& timer)
{
	//警告よけ
	timer;


	// キー入力情報を取得する
	auto keyState = DirectX::Keyboard::Get().GetState();

	// マウス入力情報を取得する
	auto mouseState = DirectX::Mouse::Get().GetState();


	if (keyState.Z || mouseState.leftButton)
	{
		return GAME_SCENE::PLAY;
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void TESTScene::Draw()
{

	switch (mState)
	{
		case STATE::BEGIN:
		{


			mState = STATE::DRAW;
			break;
		}
		case STATE::DRAW:
		{
			
			// キー入力情報を取得する
			auto keyState = DirectX::Keyboard::Get().GetState();

			DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
			auto context = pDR->GetD3DDeviceContext();
			DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

			mpGridFloor->Draw(context, pDxIF.GetCommonStates(), mView, mProj);
			/*--------------------------------------------------------*/
			// 環境光
			//DirectX::SimpleMath::Color ambientColor = DirectX::SimpleMath::Color(0.2f, 0.2f, 0.2f);

			//// いわゆるライトの色：RGB
			//DirectX::SimpleMath::Color lightColor = DirectX::SimpleMath::Color(1.f, 1.f, 1.f);

			//// ライトが照らす方向
			//DirectX::SimpleMath::Vector3 lightDirection(-1.f, -1.0f, -1.f);

			//// エフェクトにライトの効果を設定する
			//mpBasicEffect->SetLightEnabled(0, true);				// ゼロ番目のライト
			//mpBasicEffect->SetLightDiffuseColor(0, lightColor);		// 拡散反射光
			//mpBasicEffect->SetLightDirection(0, lightDirection);	// ライトの照射方向
			////mpBasicEffect->SetAmbientLightColor(ambientColor);		// 環境光
			//mpBasicEffect->Apply(context);							// エフェクトの適用

		/*--------------------------------------------------------*/
			MSG msg;

			DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
			DirectX::SimpleMath::Vector3 degree = DirectX::SimpleMath::Vector3(0.0f, 180.0f, 0.0f);
			DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

			if (!(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)))
			{
				degree.y += 1.0f;
				//this->StartRendering();
				//this->SetUpContext();

				
				mModel->Render(pos, scale, degree);

				//this->FinishRendering();
			}

			mSpriteBatch->Begin(SpriteSortMode_Deferred, mCommonState->NonPremultiplied());

			mSpriteFont->DrawString(mSpriteBatch.get(), L"TEST Scene", DirectX::XMFLOAT2(10, 10));

			mSpriteBatch->End();


			

			
			if (keyState.X) {
				mState = STATE::END;
			}
			break;
		}
		case STATE::END:
		{
		
			break;
		}


	}

}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void TESTScene::Finalize()
{
	
	if (mModel != nullptr)
	{
		delete mModel;
		mModel = nullptr;
	}
}





void TESTScene::StartRendering()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.5f };	// RenderTarget塗りつぶしカラー(RGBA)


	

	// DirecX9ではRenderTargetとDepth、Stencilバッファのクリアは別々にする
	context->ClearRenderTargetView(
		pDR->GetRenderTargetView(),							// クリア対象のView
		clear_color);								// クリアカラー

	context->ClearDepthStencilView(
		pDR->GetDepthStencilView(),							// クリア対象のView	
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,	// クリアフラグ(今回はDepth、Stencilともにクリア)
		1.0f,										// 深度クリア値
		0);										// ステンシルクリア値
}

void TESTScene::FinishRendering()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();
	// 描画コマンドを送信する
	pDR->GetSwapChain()->Present(
		/*
			垂直同期のタイミング
				0なら即時描画
				1以上なら指定した値の垂直同期後に描画
		*/
		0,
		/*
			出力オプション
				フレーム出力を行うためのオプションで
				基本は0で問題ないと思われる
				その他のフラグはDXGI_PRESENTで確認可能
		*/
		0);	// 出力オプション
}

void TESTScene::SetUpContext()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();
	// プリミティブの形状を指定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// VerteXShader、PixelShaderを設定
	context->VSSetShader(
		mModel->GetVertexShader()->GetShaderInterface(),	// 使用するVertexShder
		/*
			ClassInstanceのポインタを設定する
				これはShader作成時のID3D11ClassLinkageを使用した場合に
				用いる項目なので今回はnullptrを指定する
		*/
		nullptr,
		0);									// ClassInstanceの数
	context->PSSetShader(mModel->GetPixelShader()->GetShaderInterface(), nullptr, 0);

	ID3D11RenderTargetView* m_RenderTargetView;
	m_RenderTargetView = pDR->GetRenderTargetView();
	// (OutputManger)RnderTagetの指定
	context->OMSetRenderTargets(
		1,							// 使用するViewの数
		&m_RenderTargetView,		// 使用するRenderTargetView
		pDR->GetDepthStencilView());		// 使用すtるDepthStencilView
}

