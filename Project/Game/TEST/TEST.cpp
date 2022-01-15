/*
�^�C�g���V�[��
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
�R���X�g���N�^
--------------------------------------------------*/
TESTScene::TESTScene()
	:mModel(nullptr)
	,mView()
	,mProj()
	,mState(STATE::BEGIN)
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
TESTScene::~TESTScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void TESTScene::Initialize()
{

	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	ProViewIF& pPvIF = ProViewIF::GetProViewIFInstance();


	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto device = pDR->GetD3DDevice();
	auto context = pDR->GetD3DDeviceContext();

	// �R�����X�e�[�g::D3D�����_�����O��ԃI�u�W�F�N�g
	mCommonState = std::make_unique<DirectX::CommonStates>(device);

	// �X�v���C�g�o�b�`::�f�o�b�O���̕\���ɕK�v
	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	mSpriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Fonts/SegoeUI_18.spritefont");

	fbxsdk::FbxManager* fbx_manager = fbxsdk::FbxManager::Create();


	/*�x�[�V�b�N�G�t�F�N�g�̊Ǘ�*/
	mpBasicEffect = std::make_unique<BasicEffect>(device);


	//���_�������肷�邽�߂ɕK�v�ȏ��
	mpBasicEffect->SetLightingEnabled(false);		//���C�gOFF
	mpBasicEffect->SetTextureEnabled(true);			//�e�N�X�`��ON
	mpBasicEffect->SetVertexColorEnabled(false);	//���_�J���[OFF


	mModel = new FbxMeshFile();
	
	mModel->GetVertexShader()->Create(device, "Resources/Shader/VertexShader.cso");
	mModel->GetPixelShader()->Create(device, "Resources/Shader/PixelShader.cso");


	mModel->Load(
		"Resources/Models/Cube02.fbx",
		device,
		mModel->GetVertexShader());


	fbx_manager->Destroy();


	// �J�����̍쐬
	mpCamera = std::make_unique<Camera>();


	//�V���O���g������擾(�擾�Ɠ����ɃJ��������l��Ⴂ�ۑ�����)
	pPvIF.SetView(mpCamera->GetViewMatrix());
	pPvIF.SetProjection(mpCamera->GetProjectionMatrix());
	mView = *pPvIF.GetView();
	mProj = *pPvIF.GetProjection();




	// �O���b�h�̍쐬
	mpGridFloor = std::make_unique<GridFloor>(
		device,
		context,
		10,		// ������X
		10		// ������Y
		);

	
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE TESTScene::Update(const DX::StepTimer& timer)
{
	//�x���悯
	timer;


	// �L�[���͏����擾����
	auto keyState = DirectX::Keyboard::Get().GetState();

	// �}�E�X���͏����擾����
	auto mouseState = DirectX::Mouse::Get().GetState();


	if (keyState.Z || mouseState.leftButton)
	{
		return GAME_SCENE::PLAY;
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
�`��
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
			
			// �L�[���͏����擾����
			auto keyState = DirectX::Keyboard::Get().GetState();

			DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
			auto context = pDR->GetD3DDeviceContext();
			DirectXtkIF& pDxIF = DirectXtkIF::GetDirectXtkIFInstance();

			mpGridFloor->Draw(context, pDxIF.GetCommonStates(), mView, mProj);
			/*--------------------------------------------------------*/
			// ����
			//DirectX::SimpleMath::Color ambientColor = DirectX::SimpleMath::Color(0.2f, 0.2f, 0.2f);

			//// �����郉�C�g�̐F�FRGB
			//DirectX::SimpleMath::Color lightColor = DirectX::SimpleMath::Color(1.f, 1.f, 1.f);

			//// ���C�g���Ƃ炷����
			//DirectX::SimpleMath::Vector3 lightDirection(-1.f, -1.0f, -1.f);

			//// �G�t�F�N�g�Ƀ��C�g�̌��ʂ�ݒ肷��
			//mpBasicEffect->SetLightEnabled(0, true);				// �[���Ԗڂ̃��C�g
			//mpBasicEffect->SetLightDiffuseColor(0, lightColor);		// �g�U���ˌ�
			//mpBasicEffect->SetLightDirection(0, lightDirection);	// ���C�g�̏Ǝ˕���
			////mpBasicEffect->SetAmbientLightColor(ambientColor);		// ����
			//mpBasicEffect->Apply(context);							// �G�t�F�N�g�̓K�p

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
�I������
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

	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.5f };	// RenderTarget�h��Ԃ��J���[(RGBA)


	

	// DirecX9�ł�RenderTarget��Depth�AStencil�o�b�t�@�̃N���A�͕ʁX�ɂ���
	context->ClearRenderTargetView(
		pDR->GetRenderTargetView(),							// �N���A�Ώۂ�View
		clear_color);								// �N���A�J���[

	context->ClearDepthStencilView(
		pDR->GetDepthStencilView(),							// �N���A�Ώۂ�View	
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,	// �N���A�t���O(�����Depth�AStencil�Ƃ��ɃN���A)
		1.0f,										// �[�x�N���A�l
		0);										// �X�e���V���N���A�l
}

void TESTScene::FinishRendering()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();
	// �`��R�}���h�𑗐M����
	pDR->GetSwapChain()->Present(
		/*
			���������̃^�C�~���O
				0�Ȃ瑦���`��
				1�ȏ�Ȃ�w�肵���l�̐���������ɕ`��
		*/
		0,
		/*
			�o�̓I�v�V����
				�t���[���o�͂��s�����߂̃I�v�V������
				��{��0�Ŗ��Ȃ��Ǝv����
				���̑��̃t���O��DXGI_PRESENT�Ŋm�F�\
		*/
		0);	// �o�̓I�v�V����
}

void TESTScene::SetUpContext()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();
	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// VerteXShader�APixelShader��ݒ�
	context->VSSetShader(
		mModel->GetVertexShader()->GetShaderInterface(),	// �g�p����VertexShder
		/*
			ClassInstance�̃|�C���^��ݒ肷��
				�����Shader�쐬����ID3D11ClassLinkage���g�p�����ꍇ��
				�p���鍀�ڂȂ̂ō����nullptr���w�肷��
		*/
		nullptr,
		0);									// ClassInstance�̐�
	context->PSSetShader(mModel->GetPixelShader()->GetShaderInterface(), nullptr, 0);

	ID3D11RenderTargetView* m_RenderTargetView;
	m_RenderTargetView = pDR->GetRenderTargetView();
	// (OutputManger)RnderTaget�̎w��
	context->OMSetRenderTargets(
		1,							// �g�p����View�̐�
		&m_RenderTargetView,		// �g�p����RenderTargetView
		pDR->GetDepthStencilView());		// �g�p��t��DepthStencilView
}

