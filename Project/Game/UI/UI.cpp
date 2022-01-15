/*
ユーザーインターフェース
(指定されたところに指定されたものを描画するクラス)
作成日：2021/06/23
*/

#include"pch.h"
#include"UI.h"

//ポインタの保存用
#include"../PlayScene/PlaySceneCommon/Administrator/Timer.h"
#include"../PlayScene/PlaySceneCommon/Protecter.h"


//敵情報描画位置
const DirectX::SimpleMath::Vector2 UI::STRING_ENEMY_NUM_POSITION(20.f, 80.f);

//所持金減少エフェクトの位置
const DirectX::SimpleMath::Vector2 UI::MONEY_EFFECT_POSITION(1000.f,100.f);

/*==============
コンストラクタ
==============*/
UI::UI()
	:
	mpTimeOfDay(),
	mpMoneyTexture(),
	mpPhaseCursorManager(),
	mpRedAssert(),
	mpPlayerActionInfo(),
	mpDecreaseMoney(),
	mpScoreRender(),
	mpDefeatEnemyRender(),
	mpTimer(),
	mpProtecter(),
	mpPlayer(),
	mpPhaseCountNum(),
	mpPhase(),
	mInitHP(),
	mMaxPhaseNum(),
	mScoreNum(),
	mAllEnemyNum(),
	mRemainingEnemyNum()
{
	//動的確保
	mpTimeOfDay = std::make_unique<TimeOfDay>();
	mpMoneyTexture = std::make_unique<MoneyTexture>();
	mpPhaseCursorManager = std::make_unique<PhaseCursorManager>();
	mpRedAssert = std::make_unique<RedAssert>();
	mpPlayerActionInfo = std::make_unique<PlayerActionInfo>();
	mpDecreaseMoney = std::make_unique<FloatNumber2D>();
	mpScoreRender = std::make_unique<ScoreRender>();
	mpDefeatEnemyRender = std::make_unique<DefeatEnemyRender>();

}
/*==============
デストラクタ
==============*/	
UI::~UI()
{
}


/*========================
初期化
引数：カメラのポインタ
==========================*/
void UI::Initialize()
{
	//フェーズ関係の画像の初期設定
	mpTimeOfDay->Initialize(mpTimer, mMaxPhaseNum);

	//所持金の下地画像の初期化処理
	mpMoneyTexture->Initialize();

	//フェーズのカーソルの初期化処理
	mpPhaseCursorManager->Initialize(mMaxPhaseNum);

	//カーソルの座標を設定する
	mpPhaseCursorManager->SetDrawPosition
	(
		mpTimeOfDay->GetIconStartPosition(),
		mpTimeOfDay->GetIconDistancePosition()
	);

	//危険信号の初期化処理
	mpRedAssert->Initialize();

	//プレイヤーの現在の状態の初期化処理
	mpPlayerActionInfo->Initialize();

	//所持金減少エフェクトのフォントを指定
	mpDecreaseMoney->SetTextureKey("DamageNumberFont");
	mpDecreaseMoney->Initialize();

	//スコア周りの描画クラスの初期化処理
	mpScoreRender->Initialize();

	//残り敵数の初期化処理
	mpDefeatEnemyRender->Initialize();
}

/*==============
更新処理
==============*/
void UI::Update()
{
	//現在のPhaseが防衛フェーズの場合
	if (*mpPhase == ePlayScenePhase::DEFENCE)
	{
		//フェーズ関係の画像の更新処理
		mpTimeOfDay->Update();

		//危険信号の更新処理
		mpRedAssert->Update();

		//所持金減少エフェクトの更新処理
		mpDecreaseMoney->Update();
	}
	//現在のPhaseがショップフェーズの場合
	if (*mpPhase == ePlayScenePhase::WEAPON_SHOP)
	{
		//所持金減少エフェクトの更新処理
		mpDecreaseMoney->Update();
	}

}

/*==============
描画
==============*/
void UI::Draw()
{

	//プレイヤーの現在の状態の描画処理
	mpPlayerActionInfo->Draw();
	
	//危険信号の描画処理
	mpRedAssert->Draw();
	
	//フェーズ関係の画像の描画
	mpTimeOfDay->Draw();
	
	//フェーズのカーソルの描画処理
	mpPhaseCursorManager->Draw();
	
	//所持金関係の描画
	this->DrawMoneyTexture();
	
	//スコアの描画
	mpScoreRender->Draw(mScoreNum);
	
	//残りの敵の数の描画
	mpDefeatEnemyRender->Draw(mRemainingEnemyNum, mAllEnemyNum);
}

/*============
ポインタの保存
==============*/
//引数：タイマーのポインタ
void UI::SetTimerPointer(Timer* pTimer)
{
	mpTimer = pTimer;
}

//引数：プレイヤーのポインタ
void UI::SetPlayerPointer(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

//引数：拠点のポインタ
void UI::SetProtecterPointer(Protecter* pProtecter)
{
	mpProtecter = pProtecter;
}

//引数：フェーズカウント数のポインタ
void UI::SetPhaseCountPointer(int* pPhaseCount)
{
	mpPhaseCountNum = pPhaseCount;
}

//引数：現在のフェーズのポインタ
void UI::SetPhase(ePlayScenePhase* phase)
{
	mpPhase = phase;
}

//引数：初期HP
void UI::SetInitHP(int const& pHP)
{
	mInitHP = pHP;
}

//引数：最大Phase数
void UI::SetMaxPhaseNum(int const& phasenum)
{
	mMaxPhaseNum = phasenum;
}

//引数：スコア値
void UI::SetScoreNum(int const& phasenum)
{
	mScoreNum = phasenum;
}
//引数：全ての敵の数
void UI::SetAllEnemyNum(int const& phasenum)
{
	mAllEnemyNum = phasenum;
}
//引数：倒した敵の数
void UI::SetRemainingEnemyNum(int const& phasenum)
{
	mRemainingEnemyNum = phasenum;
}


/*==========================
危険信号を操作する関数
==========================*/
void UI::RedAssertControl(bool const& flag)
{
	mpRedAssert->SetPassFlag(flag);
}

/*========================
描画する画像を変える関数
==========================*/
void UI::ChangeActionInfoTexture(ePlayerActionState const& state)
{
	mpPlayerActionInfo->SetPlayerActionState(state);
}

void UI::ChangeActionInfoTexture(eWeaponType const& type)
{
	mpPlayerActionInfo->SetPlayerWeaponType(type);
}

/*==============================
現在の武器の弾数を取得する関数
================================*/
void UI::SetActionInfoStrongBulletNum(int const& num)
{
	mpPlayerActionInfo->StrongWeaponBulletNum(num);
}

/*==============================
所持金を描画する関数
================================*/
void UI::DrawMoneyTexture()
{
	//所持金の描画
	mpMoneyTexture->Draw();

	//所持金減少エフェクトの描画
	mpDecreaseMoney->Draw();
}

/*============================================
所持金減少エフェクトを作成する
==============================================*/
void UI::CreateMoneyEffect(int const& moneynum)
{
	mpDecreaseMoney->Reset();

	mpDecreaseMoney->Create(moneynum, MONEY_EFFECT_POSITION);
}
