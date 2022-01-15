/*
プレイシーンからリザルトシーンへ情報を渡すためのインターフェース
*/

#include"pch.h"
#include"PtoRSceneInterface.h"

//外部で初期化
PtoRSceneInterface* PtoRSceneInterface::sPtoRIF = nullptr;

/*================
コンストラクタ
================*/
PtoRSceneInterface::PtoRSceneInterface()
{
}


/*========================
インスタンスの取得
返り値：自身のインスタンス
==========================*/
PtoRSceneInterface& PtoRSceneInterface::GetPtoRIFInstance()
{
	if (sPtoRIF == nullptr)
	{
		sPtoRIF = new PtoRSceneInterface();
	}
	return *sPtoRIF;
}
