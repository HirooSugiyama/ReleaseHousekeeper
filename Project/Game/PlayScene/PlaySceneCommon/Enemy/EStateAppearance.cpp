/*
敵行動パターン
作成日：2021/08/31
*/


#include"pch.h"
#include "EStateAppearance.h"

//前方宣言
#include"Enemy.h"

//前方宣言
#include"../../Effect/Effect.h"

//関数の使用
#include"../ObjectModel/BoxModel.h"
#include"../../Effect/EffectManager.h"
#include"Libraries/MyLibraries/Camera.h"


//モデル移動スピード
const float EStateAppearance::ENEMY_MODEL_MOVE_VELOCITY = 0.02f;
//モデルY軸最大値
const float EStateAppearance::ENEMY_MODEL_MAX_POSITIONY = 1.f;

/*============================
コンストラクタ
============================*/
EStateAppearance::EStateAppearance()
	:
	EnemyStateBase(),
	mpEnemy(nullptr),
	mpCamera(nullptr),
	mpAppearanceEffect(nullptr)
{
}

/*============================
デストラクタ
============================*/
EStateAppearance::~EStateAppearance()
{
}

/*============================
初期化処理
引数：敵のポインタ
============================*/
void EStateAppearance::Initialize(Enemy* pEnemy)
{
	//ポインタの保存
	mpEnemy = pEnemy;

	//エフェクトの設定
	this->SetEffect();
}

/*============================
更新処理
============================*/
void EStateAppearance::Update()
{
	//型変換用変数の宣言
	DirectX::SimpleMath::Vector3 castpos = DirectX::SimpleMath::Vector3::Zero;
	castpos.y += ENEMY_MODEL_MOVE_VELOCITY;

	//モデルを移動させる
	mpEnemy->GetBoxModel()->Move(castpos);

	//もしY軸が最大値となったら
	if (mpEnemy->GetBoxModel()->GetPosition().y >= ENEMY_MODEL_MAX_POSITIONY)
	{
		mpEnemy->ChangeStateWalk();

		//エフェクト側のフラグを下す
		mpAppearanceEffect->SetSpriteFlag(false);
	}
}

/*============================
描画処理
============================*/
void EStateAppearance::Draw()
{
}

/*============================
State開始時の初期化処理
============================*/
void EStateAppearance::Reset()
{

}

/*============================
エフェクトの設定:private
============================*/
void EStateAppearance::SetEffect()
{
	DirectX::SimpleMath::Vector3 pos = mpEnemy->GetBoxModel()->GetPosition();
	pos.y = ENEMY_MODEL_MAX_POSITIONY;

	//エフェクトマネージャーの取得
	auto pEM = EffectManager::GetInstance();

	mpAppearanceEffect = pEM->GetEffect(eEffectType::SPAWN);
	mpAppearanceEffect->SetPosition(pos);
	mpAppearanceEffect->SetSpriteFlag(true);
}

