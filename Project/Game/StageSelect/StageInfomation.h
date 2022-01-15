/*
各ステージの情報を管理するクラス
*/
#pragma once

//列挙型の使用
#include"StageNumer.h"
//所持
#include"../Common/ObjectTexture.h"
#include"StageLevel.h"

class StageInfomation
{
private:

	//ファイル情報
	enum class FILE_INFO :int
	{
		TEXTURE_TAG,
		PHASE_NUM,
		LEVELOCITY,
	};

	//ステージ画像の座標
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_TEXTURE_POSITION;

	//ステージ画像の拡大率
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_TEXTURE_SCALE;

	//ステージのPhase数の描画位置
	static const DirectX::SimpleMath::Vector2 STAGE_INFO_PHASENUM_POSITION;

	//ステージ情報を管理するCSVファイルのパス
	static const std::string STAGE_INFO_CSV_FILEPATH;



	//ステージ画像
	std::unique_ptr<ObjectTexture> mpStageMapTexture;

	//ステージレベル
	std::unique_ptr<StageLevel> mpStageLevel;

	//ステージ情報を保存する変数
	std::string mStageTextureTag[static_cast<int>(eSelectNum::NUM)];
	int mStagePhaseNum[static_cast<int>(eSelectNum::NUM)];
	int mStageLevelNum[static_cast<int>(eSelectNum::NUM)];


public:

	//コンストラクタ
	StageInfomation();
	//デストラクタ
	~StageInfomation();
	//初期化処理
	void Initialize();
	//描画処理
	void Draw(int const& selectStageNum);

private:
	//ステージ情報をファイルから取得する
	void LoadStageInfoCSV();

};
