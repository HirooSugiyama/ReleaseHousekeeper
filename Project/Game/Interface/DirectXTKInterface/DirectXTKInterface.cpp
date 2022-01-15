/*
DirectXTK�̔ėp�����̃V���O���g����
������F2021/04/23
*/
#include<pch.h>
#include "DirectXTKInterface.h"


//�N���X�O���ŏ�����
DirectXtkIF* DirectXtkIF::sDirectXtkIF = nullptr;
std::unique_ptr<DirectX::CommonStates> DirectXtkIF::spCommonState = nullptr;
std::unique_ptr<DirectX::SpriteBatch> DirectXtkIF::spSpriteBatch = nullptr;
std::unique_ptr<DirectX::SpriteFont> DirectXtkIF::spSpriteFont = nullptr;

/*=========================================
�R���X�g���N�^
=========================================*/
DirectXtkIF::DirectXtkIF()
	:
	spDevice(),
	spContext()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	spDevice = pDR->GetD3DDevice();
	spContext = pDR->GetD3DDeviceContext();

	spCommonState = std::make_unique<DirectX::CommonStates>(spDevice);
	
	spSpriteBatch = std::make_unique<DirectX::SpriteBatch>(spContext);
	
	spSpriteFont = std::make_unique<DirectX::SpriteFont>(spDevice, L"Resources/Fonts/myfile.spritefont");
}
/*=========================================
�C���X�^���X�̎擾
�߂�l�F���g�̃C���X�^���X
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
���g�̍폜
=========================================*/
void DirectXtkIF::Destroy()const
{
	delete sDirectXtkIF;
	sDirectXtkIF = nullptr;
}


/*=========================================
�R�����X�e�[�g�̃Q�b�^�[
�Ԃ�l�FCommonStates�^�@�R�����X�e�[�g
=========================================*/
DirectX::CommonStates* DirectXtkIF::GetCommonStates() const 
{
	return spCommonState.get();
}
/*=========================================
�X�v���C�g�o�b�`�̎擾
�Ԃ�l�FSpriteBatch�^�@�X�v���C�g�o�b�`
=========================================*/
DirectX::SpriteBatch* DirectXtkIF::GetSpriteBatch() const 
{
	return spSpriteBatch.get();
}
/*=========================================
�X�v���C�g�t�H���g�̎擾
�Ԃ�l�FSpriteFont�^�@�X�v���C�g�t�H���g
=========================================*/
DirectX::SpriteFont* DirectXtkIF::GetSpriteFont()const 
{
	return spSpriteFont.get();
}