/*
ステージセレクト画面からプレイシーンへ情報を渡すためのインターフェース
*/
#pragma once

class StoPSceneInterface
{
private:
	//自分自身
	static StoPSceneInterface* sStoPIF;


	//読み込むステージCSVファイル
	std::string mCSVFileName;

	//ステージ番号
	std::string mStageNumber;	//後々String型で使用するためあらかじめString型で準備

	//コピーコンストラクタ、コピー代入演算子をdelete。
	StoPSceneInterface(const StoPSceneInterface& dr) = delete;
	StoPSceneInterface operator=(const StoPSceneInterface& dr) = delete;

	//コンストラクタ
	StoPSceneInterface();
	//デストラクタ
	~StoPSceneInterface()=default;
public:
	//自身のインスタンス
	static StoPSceneInterface& GetStoPIFInstance();


	//各種アクセサ
	//CSVファイル
	void SetStageCSV(std::string const& filepath) { mCSVFileName = filepath; }
	std::string GetStageCSV() const { return mCSVFileName; }

	//ステージ番号
	void SetStageNumber(std::string const& number) { mStageNumber = number; }
	std::string GetStageNumber()const { return mStageNumber; }
	const
	//削除処理
	void Destroy()
	{
		if (sStoPIF != nullptr) {
			delete sStoPIF;
			sStoPIF = nullptr;
		}
	}
};
