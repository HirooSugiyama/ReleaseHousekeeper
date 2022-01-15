/*
リソースマネージャー
リソース全般を管理するクラスライブラリ
(現状、オーディオは別ライブラリを使用するため独立させています。)
*/

#include"pch.h"
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"DeviceResources.h"


#pragma warning(disable : 4996)

/*=========================================
コンストラクタ
=========================================*/
ResourceManager::ResourceManager()
	:mReadTiming(eLoadScene::NONE)
{
}

/*=========================================
デストラクタ
=========================================*/
ResourceManager::~ResourceManager()
{
	//全てのリソース情報を破棄
	this->DeleteAllData();
}

/*=========================================
初期化
引数：ファイルのパス
=========================================*/
void ResourceManager::Initialize(const wchar_t* filepath)
{
	setlocale(LC_CTYPE, "");


	//とりあえず初期化忘れ防止の初期化
	this->DeleteAllData();

	//ファイル読み込み
	this->LoadCSV(filepath);
}

/*=========================================
終了処理
=========================================*/
void ResourceManager::Finalize()
{
	//一旦最後なのですべて初期化
	this->DeleteAllData();
}


/*=======================================
テクスチャの取得
引数：テクスチャの識別名
=========================================*/
ID3D11ShaderResourceView* ResourceManager::GetTexture(const std::string& key)
{
	return mpTextureDB[key].Get();
}


/*=========================================
CMOモデルの取得
引数：CMOモデルの識別名
=========================================*/
DirectX::Model* ResourceManager::GetCmoModel(const std::string& key)
{
	return mpCmoModelDB[key].get();
}

//
//
/*==================================================================================
テクスチャの登録
引数：path(テクスチャの相対パス(ワイド文字列型))、Key(テクスチャの識別名(文字列))
==================================================================================*/
void ResourceManager::RegisterTexture(const wchar_t* path, std::string const& key)
{
	//デバイスリソースの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//テクスチャの読み込み	:SRVの作成
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

	DirectX::CreateWICTextureFromFile(device, path, nullptr, texture.ReleaseAndGetAddressOf());

	//DB(Map)にテクスチャを追加
	mpTextureDB[key] = std::move(texture);

}


/*==========================================================================
CMOモデルの登録
path(CMOモデルの相対パス(ワイド文字列型))、Key(CMOモデルの識別名(文字列))
==========================================================================*/
void ResourceManager::GetCmoModel(const wchar_t* path, std::string const& key)
{
	//デバイスリソースの取得
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	//モデルの保存座標等を保持するインスタンスの生成
	std::unique_ptr<DirectX::EffectFactory> factory =
		std::make_unique<DirectX::EffectFactory>(device);

	factory->SetDirectory(L"Resources/Models");
	std::unique_ptr<DirectX::Model> model = DirectX::Model::
		CreateFromCMO(device, path, *factory);

	//DB(Map)にテクスチャを追加
	mpCmoModelDB[key] = std::move(model);
}

/*===============================================================================================
ファイル読み込み処理
引数：ファイルのパス
※テクスチャは"Resources/Textures/"、CMOモデルは"Resources/Models/"に入れておくこと。
===============================================================================================*/
void ResourceManager::LoadCSV(const wchar_t* filepath)
{
	//ファイル名取得
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;
		//保存用
		DirectX::SimpleMath::Vector3 instantpos;

		int readtiming = 0;						//読み込むタイミング
		std::string identifier = "none";		//識別子[テクスチャかモデルか]
		std::string filename = "none";			//ファイル名
		std::string path = "none";				//Mapのキー

		const wchar_t* texturename = L"none";	//テクスチャの相対パス
		const wchar_t* cmoname = L"none";		//モデルの相対パス

		wchar_t* wcs = L"none";//変換用変数

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//読みこみタイミングが合っているか(Titleならtitleで必要なものを読み込む)
			if (j == static_cast<int>(eFileReading::READ_TIMING)) {
				//とりあえず保存
				readtiming = atoi(tileBuf.c_str());
				//読み込みタイミングが異なる場合抜ける
				if (readtiming != static_cast<int>(mReadTiming)) {
					break;
				}
			}
			//識別子を取得
			if (j == static_cast<int>(eFileReading::IDENTIFIER)) {
				identifier = tileBuf;
			}
			//ファイル名から相対パスを算出
			else if (j == static_cast<int>(eFileReading::FILE_NAME)) {

				//識別子がテクスチャなら
				if (identifier == "T") {
					std::string omission = "Resources/Textures/";
					filename = omission+tileBuf;
					//マルチバイト文字をワイド文字に変換
					wcs = new wchar_t[filename.length() + 1];
					mbstowcs(wcs, filename.c_str(), filename.length() + 1);
					texturename = wcs;

				}
				//識別子がモデルなら
				else if (identifier == "M") {
					std::string omission = "Resources/Models/";
					filename = omission + tileBuf;
					//マルチバイト文字をワイド文字に変換
					wcs = new wchar_t[filename.length() + 1];
					mbstowcs(wcs, filename.c_str(), filename.length() + 1);
					cmoname = wcs;
				}				
			}
			else if (j == static_cast<int>(eFileReading::FILE_MAPKEY)) {
				//キーの取得
				path = tileBuf;
			}
		}
		//中身が入っていたら通す
		if (path != "none") 
		{
			//識別子毎に保存先を変更
			if (identifier == "T") {
				this->RegisterTexture(texturename, path);
			}
			//識別子がモデルなら
			else if (identifier == "M") {
				this->GetCmoModel(cmoname, path);
			}
			delete[] wcs;
		}			
	}
}

/*=========================================
全てのリソースの削除
=========================================*/
void ResourceManager::DeleteAllData()
{
	mpTextureDB.clear();
	mpCmoModelDB.clear();
}
