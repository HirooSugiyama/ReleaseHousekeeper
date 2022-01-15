/*
ステージセレクト画面からプレイシーンへ情報を渡すためのインターフェース
*/

#include"pch.h"
#include"StoPSceneInterface.h"


//外部で初期化
StoPSceneInterface* StoPSceneInterface::sStoPIF = nullptr;


/*================
コンストラクタ
================*/
StoPSceneInterface::StoPSceneInterface()
	:
	mCSVFileName("none"),
	mStageNumber("-1")
{
}


/*================================
インスタンスの取得
返り値：自身のインスタンス
================================*/
StoPSceneInterface& StoPSceneInterface::GetStoPIFInstance()
{
	if (sStoPIF == nullptr)
	{
		sStoPIF = new StoPSceneInterface();
	}
	return *sStoPIF;
}
