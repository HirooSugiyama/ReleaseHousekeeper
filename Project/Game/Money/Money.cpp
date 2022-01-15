/*
所持金管理ファイル
*/
#include"pch.h"
#include"Money.h"


//クラス外部で初期化
Money* Money::sMoney = nullptr;

/*===================================
コンストラクタ
===================================*/
Money::Money()
	:
	mFilepath("none"),
	mPossessionMoney()
{
}

/*=================================
自身のインスタンス
===================================*/
Money& Money::GetMoneyInstance()
{
	if (sMoney == nullptr)
	{
		sMoney = new Money();
	}
	return *sMoney;
}

/*=================================
ファイル名の設定
引数：ファイルパス
===================================*/
void Money::LoadFileSet(std::string filepath)
{
	//引数の保存
	mFilepath = filepath;

	//金額の初期設定
	this->MoneyInit();
}

/*=================================
削除処理
===================================*/
void Money::Destroy()
{
	if (sMoney != nullptr)
	{
		delete sMoney;
		sMoney=nullptr;
	}
}

/*===================================
所持金の初期設定:private
===================================*/
void Money::MoneyInit()
{
	//ファイル変換
	std::ifstream ifs(mFilepath);
	//1行の情報を保存する変数
	std::string lineBuf;

	//引き出す
	std::getline(ifs, lineBuf);

	mPossessionMoney = static_cast<int>(atof(lineBuf.c_str()));
}

