/*
各ステージの情報を管理するクラス
*/
#include"pch.h"

#include"StageInfomation.h"

//ステージ画像の座標
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_POSITION(655.f,144.f);

//ステージ画像の拡大率
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_TEXTURE_SCALE(0.43f,0.36f);

//ステージのPhase数の描画位置
const DirectX::SimpleMath::Vector2 StageInfomation::STAGE_INFO_PHASENUM_POSITION(855.f, 480.f);

//ステージ情報を管理するCSVファイルのパス
const std::string StageInfomation::STAGE_INFO_CSV_FILEPATH =
	"Resources/CSV/StageInfomation.csv";


/*===================================
コンストラクタ
===================================*/
StageInfomation::StageInfomation()
	:
	mpStageMapTexture(),
	mpStageLevel(),
	mStageTextureTag{},
	mStagePhaseNum{},
	mStageLevelNum{}
{
	mpStageMapTexture = std::make_unique<ObjectTexture>();
	mpStageLevel = std::make_unique<StageLevel>();
	//ファイル読み込み
	this->LoadStageInfoCSV();
}

/*===================================
デストラクタ
===================================*/
StageInfomation::~StageInfomation()
{
}

/*===================================
初期化処理
===================================*/
void StageInfomation::Initialize()
{
	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture("StageCursor");
	//画像初期化処理
	mpStageMapTexture->Initialize();

	//画像を設定する
	mpStageMapTexture->SetTexture(textute);

	//拡大率の設定
	mpStageMapTexture->SetPosition(STAGE_INFO_TEXTURE_POSITION);

	//拡大率の設定
	mpStageMapTexture->SetScale(STAGE_INFO_TEXTURE_SCALE);

	//ステージレベル管理クラスの初期化処理
	mpStageLevel->Initialize();
}


/*===================================
描画処理
===================================*/
void StageInfomation::Draw(int const& selectStageNum)
{

	//ステージ情報の描画
	Utility::DrawString
	(
		mStagePhaseNum[selectStageNum],
		STAGE_INFO_PHASENUM_POSITION,
		DirectX::Colors::Black,
		Utility::STRING_SIZE_MEDIUM
	);



	//リソースの確保
	auto pRM = ResourceManager::GetInstance();
	auto textute = pRM->GetTexture(mStageTextureTag[selectStageNum]);
	//画像を設定する
	mpStageMapTexture->SetTexture(textute);
	mpStageMapTexture->Draw();

	//ステージレベル管理クラスの描画処理
	int starnum = mStageLevelNum[selectStageNum];
	mpStageLevel->Draw(starnum);
}

/*===================================
ステージ情報をファイルから取得する
===================================*/
void StageInfomation::LoadStageInfoCSV()
{
	//ファイル変換
	std::ifstream ifs(STAGE_INFO_CSV_FILEPATH);
	//1行の情報を保存する変数
	std::string lineBuf;

	//1行の読み込み処理_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1行の情報をstreamにする
		std::stringstream lineStream(lineBuf);
		//1マスの情報保存用
		std::string tileBuf;

		//1マスの情報読み込み処理
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//ステージ画像のタグを保存
			if (j == static_cast<int>(FILE_INFO::TEXTURE_TAG))
			{
				mStageTextureTag[i] = tileBuf;
			}
			//フェーズ番号を保存
			if (j == static_cast<int>(FILE_INFO::PHASE_NUM))
			{
				mStagePhaseNum[i] = atoi(tileBuf.c_str());
			}
			//フェーズのレベルを保存
			if (j == static_cast<int>(FILE_INFO::LEVELOCITY))
			{
				mStageLevelNum[i] = atoi(tileBuf.c_str());
			}
		}
	}
}




