/*
スコア管理クラス
作成日：2021/06/28
*/
#pragma once


class Score
{
private:

	//スコア数
	int mScore;

public:
	//コンストラクタ
	Score()
		:mScore(0)
	{};
	//デストラクタ
	~Score()
	{
	};

	//ゲージ数のアクセサ
	int GetScoreNum()const { return mScore; }
	void SetScoreInit(int const& overwrite) { mScore = overwrite; }
	void SetScoreUp(int const& upnum) { mScore += upnum; }
	void SetScoreDown(int const& downnum) { mScore -= downnum; }

};
