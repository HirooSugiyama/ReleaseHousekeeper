/*
プレイシーンからリザルトシーンへ情報を渡すためのインターフェース
*/
#pragma once

class PtoRSceneInterface
{
private:
	//自分自身
	static PtoRSceneInterface* sPtoRIF;

	//スコア
	int mScoreNum;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	PtoRSceneInterface( PtoRSceneInterface const& pr) = delete;
	PtoRSceneInterface operator=( PtoRSceneInterface const& pr) = delete;


	//コンストラクタ
	PtoRSceneInterface();
	//デストラクタ
	~PtoRSceneInterface()=default;
public:
	//自身のインスタンス
	static PtoRSceneInterface& GetPtoRIFInstance();



	//各種アクセサ
	//スコア
	void SetScoreNum(int score) { mScoreNum = score; }
	int GetScoreNum() { return mScoreNum; }


	//削除処理
	void Destroy()
	{
		if (sPtoRIF != nullptr) 
		{
			delete sPtoRIF;
			sPtoRIF = nullptr;
		}
	}
};
