/*
画面遷移管理クラス(Singleton)

作成日：2021/12/28
*/

#include"pch.h"
#include"ScreenTransitionInterface.h"
#include"Libraries/MyLibraries/Wipe.h"

//クラス外部で初期化
ScreenTransitionInterface* ScreenTransitionInterface::sTransitionInterface = nullptr;

/*===================================
コンストラクタ
===================================*/
ScreenTransitionInterface::ScreenTransitionInterface()
	:
	mpWipe(),
	mWipeUseFlag(false),
	mpFade(),
	mFadeUseFlag(false)
{
	mpWipe = std::make_unique<Wipe>();
	mpFade = std::make_unique<Fade>();
}



/*===================================
初期化処理
===================================*/
ScreenTransitionInterface& ScreenTransitionInterface::GetScreenTransitionInstance()
{

	if (sTransitionInterface == nullptr)
	{
		sTransitionInterface = new ScreenTransitionInterface();
	}
	return *sTransitionInterface;
}



/*===================================
削除処理
===================================*/
void ScreenTransitionInterface::Destroy() const
{
	if (sTransitionInterface != nullptr) {
		delete sTransitionInterface;
		sTransitionInterface = nullptr;
	}
}
