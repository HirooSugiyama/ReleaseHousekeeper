
/*
画面遷移管理クラス(Singleton)

作成日：2021/12/28
*/
#pragma once
#include <Libraries/MyLibraries/Wipe.h>
#include <Libraries/MyLibraries/Fade.h>

#include"../../Common/ObjectTexture.h"

class ScreenTransitionInterface
{
private:
	//自分自身
	static ScreenTransitionInterface* sTransitionInterface;

	//ワイプ
	std::unique_ptr<Wipe> mpWipe;
	//使用フラグ
	bool mWipeUseFlag;

	//フェード
	std::unique_ptr<Fade> mpFade;
	//使用フラグ
	bool mFadeUseFlag;


	//コピーコンストラクタ、コピー代入演算子をdelete。
	ScreenTransitionInterface(ScreenTransitionInterface const& sti) = delete;
	ScreenTransitionInterface operator=(ScreenTransitionInterface const& sti) = delete;

	//コンストラクタ
	ScreenTransitionInterface();
	//デストラクタ
	~ScreenTransitionInterface() = default;

public:
	//生成処理
	static ScreenTransitionInterface& GetScreenTransitionInstance();

	//削除処理
	void Destroy() const;

	//ワイプの取得
	Wipe* GetWipe() { return mpWipe.get(); }	
	//使用フラグのアクセサ
	bool GetWipeUseFlag() { return mWipeUseFlag; }
	void SetWipeUseFlag(bool flag) { mWipeUseFlag = flag; }

	//フェードの取得
	Fade* GetFade() { return mpFade.get(); }
	//使用フラグのアクセサ
	bool GetFadeUseFlag() { return mFadeUseFlag; }
	void SetFadeUseFlag(bool flag) { mFadeUseFlag = flag; }

};
