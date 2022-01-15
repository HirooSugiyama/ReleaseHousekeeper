/*
��ʑJ�ڊǗ��N���X(Singleton)

�쐬���F2021/12/28
*/

#include"pch.h"
#include"ScreenTransitionInterface.h"
#include"Libraries/MyLibraries/Wipe.h"

//�N���X�O���ŏ�����
ScreenTransitionInterface* ScreenTransitionInterface::sTransitionInterface = nullptr;

/*===================================
�R���X�g���N�^
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
����������
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
�폜����
===================================*/
void ScreenTransitionInterface::Destroy() const
{
	if (sTransitionInterface != nullptr) {
		delete sTransitionInterface;
		sTransitionInterface = nullptr;
	}
}
