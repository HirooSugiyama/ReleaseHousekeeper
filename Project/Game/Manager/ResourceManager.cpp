/*
���\�[�X�}�l�[�W���[
���\�[�X�S�ʂ��Ǘ�����N���X���C�u����
(����A�I�[�f�B�I�͕ʃ��C�u�������g�p���邽�ߓƗ������Ă��܂��B)
*/

#include"pch.h"
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"DeviceResources.h"


#pragma warning(disable : 4996)

/*=========================================
�R���X�g���N�^
=========================================*/
ResourceManager::ResourceManager()
	:mReadTiming(eLoadScene::NONE)
{
}

/*=========================================
�f�X�g���N�^
=========================================*/
ResourceManager::~ResourceManager()
{
	//�S�Ẵ��\�[�X����j��
	this->DeleteAllData();
}

/*=========================================
������
�����F�t�@�C���̃p�X
=========================================*/
void ResourceManager::Initialize(const wchar_t* filepath)
{
	setlocale(LC_CTYPE, "");


	//�Ƃ肠�����������Y��h�~�̏�����
	this->DeleteAllData();

	//�t�@�C���ǂݍ���
	this->LoadCSV(filepath);
}

/*=========================================
�I������
=========================================*/
void ResourceManager::Finalize()
{
	//��U�Ō�Ȃ̂ł��ׂď�����
	this->DeleteAllData();
}


/*=======================================
�e�N�X�`���̎擾
�����F�e�N�X�`���̎��ʖ�
=========================================*/
ID3D11ShaderResourceView* ResourceManager::GetTexture(const std::string& key)
{
	return mpTextureDB[key].Get();
}


/*=========================================
CMO���f���̎擾
�����FCMO���f���̎��ʖ�
=========================================*/
DirectX::Model* ResourceManager::GetCmoModel(const std::string& key)
{
	return mpCmoModelDB[key].get();
}

//
//
/*==================================================================================
�e�N�X�`���̓o�^
�����Fpath(�e�N�X�`���̑��΃p�X(���C�h������^))�AKey(�e�N�X�`���̎��ʖ�(������))
==================================================================================*/
void ResourceManager::RegisterTexture(const wchar_t* path, std::string const& key)
{
	//�f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//�e�N�X�`���̓ǂݍ���	:SRV�̍쐬
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	//DB(Map)�Ƀe�N�X�`����ǉ�
	mpTextureDB[key] = std::move(texture);

}


/*==========================================================================
CMO���f���̓o�^
path(CMO���f���̑��΃p�X(���C�h������^))�AKey(CMO���f���̎��ʖ�(������))
==========================================================================*/
void ResourceManager::GetCmoModel(const wchar_t* path, std::string const& key)
{
	//�f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//���f���̕ۑ����W����ێ�����C���X�^���X�̐���
	std::unique_ptr<DirectX::EffectFactory> factory =
		std::make_unique<DirectX::EffectFactory>(device);

	factory->SetDirectory(L"Resources/Models");
	std::unique_ptr<DirectX::Model> model = DirectX::Model::
		CreateFromCMO(device, path, *factory);

	//DB(Map)�Ƀe�N�X�`����ǉ�
	mpCmoModelDB[key] = std::move(model);
}

/*===============================================================================================
�t�@�C���ǂݍ��ݏ���
�����F�t�@�C���̃p�X
���e�N�X�`����"Resources/Textures/"�ACMO���f����"Resources/Models/"�ɓ���Ă������ƁB
===============================================================================================*/
void ResourceManager::LoadCSV(const wchar_t* filepath)
{
	//�t�@�C�����擾
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//1�s�̓ǂݍ��ݏ���_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;
		//�ۑ��p
		DirectX::SimpleMath::Vector3 instantpos;

		int readtiming = 0;						//�ǂݍ��ރ^�C�~���O
		std::string identifier = "none";		//���ʎq[�e�N�X�`�������f����]
		std::string filename = "none";			//�t�@�C����
		std::string path = "none";				//Map�̃L�[

		const wchar_t* texturename = L"none";	//�e�N�X�`���̑��΃p�X
		const wchar_t* cmoname = L"none";		//���f���̑��΃p�X

		wchar_t* wcs = L"none";//�ϊ��p�ϐ�

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//�ǂ݂��݃^�C�~���O�������Ă��邩(Title�Ȃ�title�ŕK�v�Ȃ��̂�ǂݍ���)
			if (j == static_cast<int>(eFileReading::READ_TIMING)) {
				//�Ƃ肠�����ۑ�
				readtiming = atoi(tileBuf.c_str());
				//�ǂݍ��݃^�C�~���O���قȂ�ꍇ������
				if (readtiming != static_cast<int>(mReadTiming)) {
					break;
				}
			}
			//���ʎq���擾
			if (j == static_cast<int>(eFileReading::IDENTIFIER)) {
				identifier = tileBuf;
			}
			//�t�@�C�������瑊�΃p�X���Z�o
			else if (j == static_cast<int>(eFileReading::FILE_NAME)) {

				//���ʎq���e�N�X�`���Ȃ�
				if (identifier == "T") {
					std::string omission = "Resources/Textures/";
					filename = omission+tileBuf;
					//�}���`�o�C�g���������C�h�����ɕϊ�
					wcs = new wchar_t[filename.length() + 1];
					mbstowcs(wcs, filename.c_str(), filename.length() + 1);
					texturename = wcs;

				}
				//���ʎq�����f���Ȃ�
				else if (identifier == "M") {
					std::string omission = "Resources/Models/";
					filename = omission + tileBuf;
					//�}���`�o�C�g���������C�h�����ɕϊ�
					wcs = new wchar_t[filename.length() + 1];
					mbstowcs(wcs, filename.c_str(), filename.length() + 1);
					cmoname = wcs;
				}				
			}
			else if (j == static_cast<int>(eFileReading::FILE_MAPKEY)) {
				//�L�[�̎擾
				path = tileBuf;
			}
		}
		//���g�������Ă�����ʂ�
		if (path != "none") 
		{
			//���ʎq���ɕۑ����ύX
			if (identifier == "T") {
				this->RegisterTexture(texturename, path);
			}
			//���ʎq�����f���Ȃ�
			else if (identifier == "M") {
				this->GetCmoModel(cmoname, path);
			}
			delete[] wcs;
		}			
	}
}

/*=========================================
�S�Ẵ��\�[�X�̍폜
=========================================*/
void ResourceManager::DeleteAllData()
{
	mpTextureDB.clear();
	mpCmoModelDB.clear();
}
