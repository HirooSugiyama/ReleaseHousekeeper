/*
所持金管理ファイル
*/
#pragma once



class Money final
{
private:

	////自身
	static Money* sMoney;

	//コピーコンストラクタ、コピー代入演算子をdelete。
	Money( Money const& money) = delete;
	Money operator=( Money const& money) = delete;

	//ファイル名
	std::string mFilepath;
	//所持金額
	int mPossessionMoney;

	//コンストラクタ
	Money();

	//デストラクタ
	~Money() = default;

public:

	//自身のインスタンス
	static Money& GetMoneyInstance();

	//ファイル名の設定
	void LoadFileSet(std::string filepath);

	//金額を引数分引く
	void ReduceMoney(int const& moneynum) { mPossessionMoney -= moneynum; }
	//金額の上書き
	void SetMoney(int const& moneynum) { mPossessionMoney = moneynum; }

	//金額を取得
	int GetMoney()const { return mPossessionMoney; }

	//削除処理
	void Destroy();

private:

	//金額の初期化
	void MoneyInit();

};
