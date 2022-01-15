/*
�t�F�[�h

�쐬���F2021/12/21
*/
#include"pch.h"

#include"Fade.h"

//�O��
const float Fade::FULL_OPEN = 1.f;
const float Fade::FULL_CLOSE = 0.f;

/*=================================
�R���X�g���N�^
===================================*/
Fade::Fade(float interval,float rate)
	:
	mInterval(interval),
	mRate (rate),
	mFlagOpen (true),
	mcbChangeEveryFrame ()
{
}

/*===================================
�f�X�g���N�^
===================================*/
Fade::~Fade()
{
}

/*===================================
����������
===================================*/
void Fade::Initialize()
{
	//�f�o�C�X�̎擾
	auto pDR = DX::DeviceResources::GetInstance();
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();


	//�E�B���h�E�T�C�Y�̎擾
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	//Resource�����t���O
	HRESULT hr = E_FAIL;

	//�萔�o�b�t�@�̍쐬=========================
	D3D11_BUFFER_DESC cBufferDesc{};

	cBufferDesc.ByteWidth = sizeof(cbChangeEveryFrame);
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	hr = device->CreateBuffer
	(
		&cBufferDesc,
		nullptr,
		mCbBuffer.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mCbBuffer�̍쐬�Ɏ��s");


	//2D�e�N�X�`���o�b�t�@�̍쐬====================
	D3D11_TEXTURE2D_DESC texDesc{};

	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.Width = w;
	texDesc.Height = h;
	texDesc.ArraySize = 1;
	texDesc.MipLevels = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.CPUAccessFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.MiscFlags = 0;

	hr = device->CreateTexture2D
	(
		&texDesc,
		nullptr,
		mTextureBuffer.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mTextureBuffer�̍쐬�Ɏ��s");

	//�V�F�[�_�\���\�[�X�r���[�̐���===========

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = device->CreateShaderResourceView
	(
		mTextureBuffer.Get(),
		&srvDesc,
		mShaderResourceView.ReleaseAndGetAddressOf()
	);

	//�V�F�[�_�̍쐬=================================================

	assert(hr == S_OK && "mShaderResouceView�̍쐬�Ɏ��s");

	std::vector<uint8_t> blob = DX::ReadData(L"Resources/Shaders/psFade.cso");

	hr = device->CreatePixelShader
	(
		blob.data(),
		blob.size(),
		nullptr,
		mpPixelShader.ReleaseAndGetAddressOf()
	);
	assert(hr == S_OK && "mPixelShader�̍쐬�Ɏ��s");
}

/*==================================
�X�V����
===================================*/
bool Fade::Update(float elaspedTime)
{
	if (mFlagOpen)
	{
		//�I�[�v��
		mRate += elaspedTime / mInterval;

		//�I��
		if (mRate >= FULL_OPEN)
		{
			return true;
		}
	}
	else
	{
		//�N���[�Y
		mRate -= elaspedTime / mInterval;

		//�I��
		if (mRate <= FULL_CLOSE)
		{
			return true;
		}

	}
	return false;
}

/*===================================
�`�揈��
===================================*/
void Fade::Draw()
{
	DirectXtkIF& DxIF = DirectXtkIF::GetDirectXtkIFInstance();

	//�̎��͕`�悵�Ȃ�
	if (mRate >= 1.f)return;

	
	//�f�o�C�X�R���e�L�X�g�̎擾
	auto pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();
	
	//�E�B���h�E�T�C�Y�̎擾
	int w = static_cast<int>(pDR->GetOutputSize().right);
	int h = static_cast<int>(pDR->GetOutputSize().bottom);

	//��ʃT�C�Y�̒Z�a��ݒ肷��
	RECT rect = {0,0,w,h};

	//�萔�o�b�t�@�̍\���̂̒l��ݒ肷��
	mcbChangeEveryFrame.alpha = 1 - mRate;

	//���C�v��Ԃ�`�悷��
	DxIF.GetSpriteBatch()->Begin
	(
		DirectX::SpriteSortMode_Deferred,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		[&]()
		{
			//�萔�o�b�t�@�ւ̏�������
			D3D11_MAPPED_SUBRESOURCE mappedResource{};
			context->Map
			(mCbBuffer.Get(),
				0,
				D3D11_MAP_WRITE_DISCARD,
				0, &mappedResource
			);

			std::memcpy
			(
				mappedResource.pData,
				&mcbChangeEveryFrame,
				sizeof(cbChangeEveryFrame)
			);
			context->Unmap(mCbBuffer.Get(), 0);

			//�s�N�Z���V�F�[�_�ɒ萔�o�b�t�@��ݒ�
			ID3D11Buffer* buffers[] = { mCbBuffer.Get() };
			context->PSSetConstantBuffers(0, 1, buffers);


			context->PSSetShader(mpPixelShader.Get(), nullptr, 0);
		}
	);

	DxIF.GetSpriteBatch()->Draw(mShaderResourceView.Get(), rect);
	DxIF.GetSpriteBatch()->End();

}

