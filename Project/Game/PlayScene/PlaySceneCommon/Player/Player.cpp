/*
プレイヤークラス
*/

#include<pch.h>

#include "Player.h"

//前方宣言
//State処理分け
#include"PStateStand.h"
#include"PStateWalk.h"
#include"PStateDamage.h"

//ActionState処理分け
#include"ActionStateDefenseHouse.h"
#include"ActionStateAttackEnemy.h"


//ポインタ保存用
#include"../Block/BlockManager.h"
#include"../Administrator/Administrator.h"
#include"../../PlaySceneDefence/PreparingBlock.h"
#include"../../../UI/UI.h"

//初期座標
const DirectX::SimpleMath::Vector3 Player::PLYAER_INIT_POSITION(0.5f,1.f,1.f);

//モデルの拡大率
	//見た目用
const DirectX::SimpleMath::Vector3 Player::PLAYER_MODEL_SCALE(0.5f, 0.5f, 0.5f);

//プレイヤーは縦長なので当たり判定を縦に伸ばす
const float Player::PLAYER_COLLIDER_EXTEND_Y = 3.f;
//実際のプレイヤーのZ値はとても小さいので小さくする
const float Player::PLAYER_COLLIDER_EXTEND_Z = 0.2f;

//シールドパニッシュ用ゲージ必要量
const int Player::BLOCKBREAK_USE_GAUGENUM = 50;


//シールドパニッシュ用拡大率
const DirectX::SimpleMath::Vector3 Player::BLOCKBREAK_SCALE(30.f, 5.f, 0.5f);


/*===================================
コンストラクタ
===================================*/
Player::Player()
	: 
	mpPlayerModel(),
	mpPreparingBlock(nullptr),
	mpBlockManager(nullptr),
	mpAdministrator(nullptr),
	mpUI(nullptr),
	mpStand(nullptr),
	mpWalk(nullptr),
	mpDamage(nullptr),
	mpPlayerState(nullptr),
	mState(ePlayerState::STAND),
	mpDefenseHouse(nullptr),
	mpAttackEnemy(nullptr),
	mpPlayerActionState(nullptr),
	mActionState(ePlayerActionState::BLOCK_CREATE),
	mOneFrameBeforePosition(DirectX::SimpleMath::Vector3::Zero),
	mpPlayerShadow(nullptr),
	mPlayerAttackWorldMatrix(DirectX::SimpleMath::Matrix::Identity)
{
	//状態オブジェクトを生成
	mpPlayerModel = std::make_unique<BoxModel>();

	mpStand = std::make_unique<PStateStand>();
	mpWalk = std::make_unique<PStateWalk>();
	mpDamage = std::make_unique<PStateDamage>();



	mpDefenseHouse = std::make_unique<ActionStateDefenseHouse>();
	mpAttackEnemy = std::make_unique<ActionStateAttackEnemy>();
	mpPlayerShadow = std::make_unique<Shadow>();
}

/*===================================
デストラクタ
===================================*/
Player::~Player()
{
}

/*===================================
初期化処理
引数	：pBlockManager(ブロック管理クラスのポインタ)、pAdministrator(管理者クラスのポインタ)
		　pPreparingBlock(見本ブロックのポインタ)
===================================*/
void Player::Initialize
(
	BlockManager* pBlockManager,
	Administrator* pAdministrator,
	PreparingBlock* pPreparingBlock,
	UI* pUI
)
{
	//ポインタの保存
	mpBlockManager = pBlockManager;
	mpAdministrator = pAdministrator;
	mpPreparingBlock = pPreparingBlock;
	mpUI = pUI;

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();

		//プレイヤー
	auto palyermodel = pRM->GetCmoModel("Player0");
	mpPlayerModel->SetModel(palyermodel);

	//変数の宣言
	DirectX::SimpleMath::Vector3 rot;
		//プレイヤー
	mpPlayerModel->SetScale(PLAYER_MODEL_SCALE);
	mpPlayerModel->SetPosition(PLYAER_INIT_POSITION);

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpPlayerModel->ReturnHalfSize(PLAYER_MODEL_SCALE);
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	halfsize.z *= PLAYER_COLLIDER_EXTEND_Z;

	//設定
	mpPlayerModel->SetAABBCollider(PLYAER_INIT_POSITION - halfsize, PLYAER_INIT_POSITION + halfsize);

	//状態オブジェクトの初期化処理
	mpStand->Initialize(this);
	mpWalk->Initialize(this);
	mpDamage->Initialize(this);

	//行動状態オブジェクトの初期化処理
	mpDefenseHouse->Initialize(this);
	mpDefenseHouse->SetCreateBlockPointer(mpPreparingBlock, mpBlockManager);
	mpAttackEnemy->Initialize(this);

	//影クラスの初期化処理
	mpPlayerShadow->WrapInitialize();

	//影のサイズ指定
	mpPlayerShadow->SetScale(DirectX::SimpleMath::Vector2(PLAYER_MODEL_SCALE.x, PLAYER_MODEL_SCALE.z));



	//最初は立ち状態に設定
	this->ChangeStateStand();

	//最初は壁建て処理で設定
	this->ChangePlayerActionStateDefenseHouse();
}

/*===================================
更新処理
===================================*/
void Player::Update()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	//モデルの更新処理
	mpPlayerModel->Update();

	//立ち状態ならば
	if (mState == ePlayerState::STAND)	//モデル描画の都合上ここで移動処理をする。
	{

		//入力があれば	
		if (pKey->Walk()||pGamePad->Move())//コントローラー上の操作
		{
			this->ChangeStateWalk();//歩き状態へ移行
		}
	}

	//現在の状態の更新処理
	mpPlayerState->Update();
	mpPlayerActionState->Update();

	//行動State変更処理
	this->ChangeAction();

	//攻撃用ワールド座標計算
	this->CalculationAttackMat();
}

/*===================================
描画処理
===================================*/
void Player::Draw()
{

	//歩き状態の時はスプライトのモデルを描画する
	if (mState!=ePlayerState::STAND)
	{
		//現在の状態の描画処理
		mpPlayerState->Draw();
	}
	else 
	{
		mpPlayerModel->Draw();
	}

	//影クラスの描画処理
	mpPlayerShadow->Draw(mpPlayerModel->GetPosition());
}


/*===================================
終了処理
===================================*/
void Player::Finalize()
{
	//状態オブジェクトをリセット
	mpStand.reset();
	mpWalk.reset();
	mpDamage.reset();
}


/*===================================
当たり判定更新処理:pirivate
===================================*/
void Player::UpdateCollider()
{
	/*当たり判定の更新*/
	//ここでは保存してないためモデルから呼び出す。
	DirectX::SimpleMath::Vector3 modelpos, modelscale;
	modelpos = mpPlayerModel->GetPosition();
	modelscale = mpPlayerModel->GetScale();

	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpPlayerModel->ReturnHalfSize(modelscale);
	halfsize.y *= PLAYER_COLLIDER_EXTEND_Y;
	//設定
	mpPlayerModel->SetAABBCollider(modelpos - halfsize, modelpos + halfsize);
}

/*===========================
行動State変更:pirivate
============================*/
void Player::ChangeAction()
{
	// キー入力情報を取得する
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();


	if (mActionState == ePlayerActionState::ATTACK_ENEMY &&
		( pKey->SwitchToDefenseHouse())|| pGamePad->ChangePlayerActionDown())
	{
		this->ChangePlayerActionStateDefenseHouse();
		mpUI->ChangeActionInfoTexture(mActionState);
	}
	else if (mActionState == ePlayerActionState::BLOCK_CREATE &&
		(pKey->SwitchToAttack())|| pGamePad->ChangePlayerActionUp())
	{
		this->ChangePlayerActionStateAttackEnemy();
		mpUI->ChangeActionInfoTexture(mActionState);
	}
}

/*==========================================
攻撃用ワールド座標の計算:pirivate
===========================================*/
void Player::CalculationAttackMat()
{
	mPlayerAttackWorldMatrix = mpPlayerModel->GetRotationX() *
		mpPlayerModel->GetRotationY() *
		mpPlayerModel->GetRotationX() *
		DirectX::SimpleMath::Matrix::CreateTranslation(mpPlayerModel->GetPosition());
}
