/*
プレイヤーの状態分けステートパターン：立ち状態
作成日：2021/06/15
*/
#include"pch.h"

#include "PStateStand.h"



//返り値からの関数の取得で使用。
#include"../ObjectModel/BoxModel.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../ObjectModel/ObjectSpriteModel.h"

/*=========================
コンストラクタ
=========================*/
PStateStand::PStateStand()
	:
	PlayerStateBase(),
	mpPlayer(nullptr)
{
}

/*=========================
デストラクタ
=========================*/
PStateStand::~PStateStand()
{
}

/*=========================
初期化処理
引数：プレイヤーのポインタ
=========================*/
void PStateStand::Initialize(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

/*=========================
更新処理
=========================*/
void PStateStand::Update()
{
	if (mpPlayer->GetPlayerState() != ePlayerState::STAND) {
		mpPlayer->SetState(ePlayerState::STAND);
	}
}

/*=========================
描画処理
=========================*/
void PStateStand::Draw()
{
	mpPlayer->GetPlayerModel()->Draw();
}
