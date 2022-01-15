/*
敵行動パターン
作成日：2021/08/31
*/


#include"pch.h"
#include "EStateBuried.h"

//前方宣言
#include"Enemy.h"

//関数の使用
#include"../Shadow.h"
#include"../ObjectModel/BoxModel.h"


//影を拡大描画
const DirectX::SimpleMath::Vector2 EStateBuried::ENEMY_SHADOW_SCLAE_UP(1.5f, 1.5f);

//影の高さを調節
const float EStateBuried::ENEMY_SHADOW_SHIFT_POSITIONY = 1.f;

/*============================
コンストラクタ
============================*/
EStateBuried::EStateBuried()
	:
	EnemyStateBase(),
	mpEnemy(nullptr)
{
}

/*============================
デストラクタ
============================*/
EStateBuried::~EStateBuried()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateBuried::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;

	//簡略化変数の宣言
	DirectX::SimpleMath::Vector2 baseScale= DirectX::SimpleMath::Vector2::Zero;

	//XZ平面に変換
	baseScale.x = mpEnemy->GetBoxModel()->GetScale().x;
	baseScale.y = mpEnemy->GetBoxModel()->GetScale().z;

	//影をサイズを変える
	mpEnemy->GetShadow()->SetScale(baseScale * ENEMY_SHADOW_SCLAE_UP);	//XZ平面
}

/*============================
描画処理
============================*/
void EStateBuried::Draw()
{
	//簡略化変数の宣言
	DirectX::SimpleMath::Vector3 pos = mpEnemy->GetBoxModel()->GetPosition();
	pos.y = ENEMY_SHADOW_SHIFT_POSITIONY;

	mpEnemy->GetShadow()->Draw(pos);
}

/*============================
次の処理へ動かす関数
============================*/
void EStateBuried::ChangeNextState()
{

	//簡略化変数の宣言
	DirectX::SimpleMath::Vector2 baseScale = DirectX::SimpleMath::Vector2::Zero;

	//XZ平面に変換
	baseScale.x = mpEnemy->GetBoxModel()->GetScale().x;
	baseScale.y = mpEnemy->GetBoxModel()->GetScale().z;

	//影をサイズを変える
	mpEnemy->GetShadow()->SetScale(baseScale);	//XZ平面

	//次の処理へ
	mpEnemy->ChangeStateAppearance();
}
