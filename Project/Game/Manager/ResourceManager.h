/*
リソースマネージャー
リソース全般を管理するクラスライブラリ
(現状、オーディオは別ライブラリを使用するため独立させています。)
*/
#pragma once



//読み込み分け
enum class eLoadScene
{
	NONE = -1,
	TITLE = 1,
	MODE_SELECT,
	STAGE_SELECT,
	PLAY,
	WIN,
	LOSE,
};

//ファイルの順番をまとめた列挙体
enum class eFileReading
{
	READ_TIMING,
	IDENTIFIER,
	FILE_NAME,
	FILE_MAPKEY,
};

//リソースマネージャ
class ResourceManager
{
public:
	//インスタンスの取得
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}
private:

	//変数
	//テクスチャ保持用マップ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr
					<ID3D11ShaderResourceView>> mpTextureDB;

	//CMOモデル保持用マップ
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>
		mpCmoModelDB;

	//読み込みタイミング保存用文字列変数
	eLoadScene mReadTiming;


	//コピーコンストラクタ、コピー代入演算子をdelete。
	ResourceManager(const ResourceManager& rm) = delete;
	ResourceManager operator=(const ResourceManager& rm) = delete;


	//コンストラクタ
	ResourceManager();
	//デストラクタ
	~ResourceManager();


public:

	//初期化
	void Initialize(const wchar_t* filepath);

	//シーンの指定
	void SetuseScene(eLoadScene const& scene) { mReadTiming = scene; }

	//終了処理
	void Finalize();

	//リソースの取得
	ID3D11ShaderResourceView* GetTexture(std::string const& key);
	DirectX::Model* GetCmoModel(std::string const& key);

private:
	//リソースの登録
	void RegisterTexture(const wchar_t* path,  std::string const& key);
	void GetCmoModel(const wchar_t* path,  std::string const& key);

	//リソースデータを読み込む
	void LoadCSV(const wchar_t* filepath);

	//すべてのリソースの削除
	void DeleteAllData();
};