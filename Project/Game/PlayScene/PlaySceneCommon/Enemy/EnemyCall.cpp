/*
敵を読み込むためのクラス
作成日：2021/05/25
*/
#include"pch.h"
#include "EnemyCall.h"

/*========================
コンストラクタ
========================*/
EnemyCall::EnemyCall()
	:
	mEnemyInfo()
{
}

/*===================================
デストラクタ
===================================*/
EnemyCall::~EnemyCall()
{
}


/*==============================
敵情報を指定する関数
引数：ファイルのパス
==============================*/
void EnemyCall::LoadInfo(std::string const& filepath)
{
	//ここはチュートリアル専用読み込みクラスなのでファイルから読み込む
	this->SetCSV(filepath);
}

/*=============================
保存用変数を初期化
==============================*/
void EnemyCall::Reset()
{
	mEnemyInfo.resize(0);
}


/*==============================
ファイル読み込み処理：private
引数：ファイルのパス
==============================*/
void EnemyCall::SetCSV(std::string const& filepath)
{
	//列挙型を簡素化
	const int csv_pos_x = static_cast<int>(eEnemyCSV::POSITION_X);
	const int csv_pos_y = static_cast<int>(eEnemyCSV::POSITION_Y);
	const int csv_pos_z = static_cast<int>(eEnemyCSV::POSITION_Z);
	const int phasenum = static_cast<int>(eEnemyCSV::PHASE_NUM);

	//ファイル変換
	std::ifstream ifs(filepath);
	//1行の情報を保存する変数
	std::string lineBuf;
	//一時的に保存用
	EnemyInfo instantpos;

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
			//座標の保存
			if (j == csv_pos_x) {
				instantpos.mVectorESPosition.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_pos_y) {
				instantpos.mVectorESPosition.y = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == csv_pos_z) {
				instantpos.mVectorESPosition.z = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == phasenum) {
				instantpos.mPhaseNumber = static_cast<int>(atof(tileBuf.c_str()));
			}
		}

		if (instantpos.mPhaseNumber != 0)
		{
			//サイズを増やす
			mEnemyInfo.push_back(instantpos);

			instantpos.mPhaseNumber = 0;
			instantpos.mVectorESPosition = DirectX::SimpleMath::Vector3::Zero;
		}		
	}
}