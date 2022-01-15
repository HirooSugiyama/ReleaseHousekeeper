/*
敵を読み込むためのクラス
作成日：2021/05/25
*/
#pragma once

class EnemyCall
{
private:
	//座標情報
	enum class eEnemyCSV :int
	{
		POSITION_X,		//X座標
		POSITION_Y,		//Y座標
		POSITION_Z,		//Z座標
		PHASE_NUM,	//動き出すフェーズ数
		ENEMY_TYPE,	//敵の種類
	};

	//敵情報
	struct EnemyInfo
	{
		//敵の座標
		DirectX::SimpleMath::Vector3 mVectorESPosition;	//1,2,3番目の要素
		//フェーズ番号
		int mPhaseNumber;

		//コンストラクタ
		EnemyInfo()
			:mVectorESPosition()
			, mPhaseNumber()
		{}
	};
	//定数

	//実体化
	std::vector<EnemyInfo> mEnemyInfo;

public:
	//コンストラクタ
	EnemyCall();
	//デストラクタ
	~EnemyCall();
	//ファイル情報を返す
	EnemyInfo GetEnemyStructer(int const& i)const {return mEnemyInfo[i];}
	//要素数を返す
	int GetEnemyStructerSize() const {return mEnemyInfo.size();}
	//敵情報を指定する関数
	void LoadInfo(std::string const& filepath);
	//要素を初期化
	void Reset();

private:
	//CSVファイル名を指定
	void SetCSV(std::string const& filepath);
};