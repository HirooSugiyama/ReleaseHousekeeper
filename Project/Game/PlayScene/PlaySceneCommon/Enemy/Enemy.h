/*
敵クラス
*/

#pragma once


//列挙型の使用
#include"StateEnemy.h"
#include"AngleEnemy.h"

//所持
#include"../ObjectModel/BoxModel.h"
#include"EStateRotation.h"
#include"EStateWalk.h"
#include"EStateKnockBack.h"
#include"EStateAppearance.h"
#include"EStateAttack.h"
#include"EStateBuried.h"
#include"EStateBlinking.h"
#include"../Shadow.h"
#include"../../PlaySceneDefence/FloatNumber3D.h"

//前方宣言
class EnemyStateBase;	//状態分け基底クラス

struct AABB;			//関数の返り値で使用

class CameraBase;			//所持
class Enemy
{
private:
	//定数
		//移動速度
	static const float ENEMY_MOVE_SPEED;
	//拡大率
	static const DirectX::SimpleMath::Vector3 ENEMY_SCALE;
	//モデルに合わせて当たり判定用の拡大率を定める
	static const float ENEMY_COLLIDER_EXTEND_Y;
	static const float ENEMY_COLLIDER_EXTEND_Z;
	//モデル生成時ミスの修正
	static const float ENMEY_MODELMISS_FIX_ROT;

	//モデル描画範囲指定
	static const float ENEMY_MDEL_DROW_AREA;

	//ブロック番号保存数
	static const int ENEMY_SAVE_BLOCKNUMBER_MAX_NUM = 3;
		//ブロック番号例外数字
	static const int ENEMY_SAVE_BLOCKNUMBER_EXCE_NUM;


	//敵モデルを強制的に横に向ける(向き反転する際に使用)
	static const float ENEMY_MODEL_FORCED_BESIDE;

	//敵のHP
	static const int ENEMY_HP;

	//敵の最大反転回数
	static const int ENEMY_REVERSE_MAX_NUM;

	//エフェクト表示座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//ダメージ値の描画座標
	static const DirectX::SimpleMath::Vector3 FLOATNUMBER_DISTANCE_POSITION;


	//変数

	//モデル描画クラス
	std::unique_ptr<BoxModel> mpEnemyModel;

	//使用フラグ
	bool mEnemyUseFlag;

	//動き始めるフェーズ番号
	int mMovePhaseNumber;

	//行動State管理用変数
	EnemyStateBase* mpEnemyMoveState;
	eStateEnemy mStateEnemy;

	//State分け
	std::unique_ptr<EStateRotation> mpRotation;
	std::unique_ptr<EStateWalk> mpWalk;
	std::unique_ptr<EStateKnockBack> mpKnockBack;
	std::unique_ptr<EStateAppearance> mpAppearance;
	std::unique_ptr<EStateAttack> mpAttack;
	std::unique_ptr<EStateBuried> mpBuried;
	std::unique_ptr<EStateBlinking> mpBlinking;

	//現在のモデルの向きを表す
	eAngleEnemy mEnemyModelAngle;

	//現在のHP
	int mEnemyDamage;

	//エフェクト稼働フラグ
	bool mEffectFlag;

	//影
	std::unique_ptr<Shadow> mpEnemyShadow;

	//数字エフェクト
	std::unique_ptr<FloatNumber3D> mpFloatNumber;

	//反転数
	int mReverseNum;

	//エフェクトのアドレス保存用変数
	bool* mEffectAddressFlag;

	//地上オブジェクトとの衝突フラグ
	bool mEnemyGroundObjectHitFlag;

	//ブーメランとの接触フラグ
	bool mBoomerangHitFlag;

	//接触した弾の番号を保存する変数
	int mSaveBulletNumber;

	//現在の歩行状態を表す
	eEnemyWalkState mWalkState;

	//接触した案山子の番号を保存する
	int mSaveScarecrowNumber;

	//プレイヤー追いかけフラグ
	bool mPlayerChaseFlag;


public:
	//関数
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(DirectX::SimpleMath::Vector3 const& pos,CameraBase* camera);
	//更新
	void Update();
	//描画
	void Draw();
	//終了処理
	void Finalize();

	//自身を削除する。
	void SelfDestroy();

	
	//アクセサ関連
	//状態分け
	void ChangeStateWalk() 
			{mpEnemyMoveState = (EnemyStateBase*)mpWalk.get(); mStateEnemy = eStateEnemy::WALK;}
	void ChangeStateRotation()
			{ mpEnemyMoveState = (EnemyStateBase*)mpRotation.get();  mStateEnemy = eStateEnemy::ROTATION;}
	void ChangeStateKnockBack()
			{ mpEnemyMoveState = (EnemyStateBase*)mpKnockBack.get();  mStateEnemy = eStateEnemy::KNOCK_BACK;}
	void ChangeStateAppearance()
			{ mpEnemyMoveState = (EnemyStateBase*)mpAppearance.get();  mStateEnemy = eStateEnemy::APPEARANCE;}
	void ChangeStateAttack()
			{ mpEnemyMoveState = (EnemyStateBase*)mpAttack.get();  mStateEnemy = eStateEnemy::ATTACK;}
	void ChangeStateBuried()
			{ mpEnemyMoveState = (EnemyStateBase*)mpBuried.get();  mStateEnemy = eStateEnemy::BURIED;}
	void ChangeStateBlinking()
			{ mpEnemyMoveState = (EnemyStateBase*)mpBlinking.get();  mStateEnemy = eStateEnemy::BLINKING;}
	EStateRotation* GetStateRotation() const { return mpRotation.get(); }
	EStateWalk* GetStateWalk()const { return mpWalk.get(); }
	EStateKnockBack* GetStateKnockBack() const { return mpKnockBack.get(); }
	EStateAppearance* GetStateAppearance() const { return mpAppearance.get(); }
	EStateAttack* GetStateAttack()const { return mpAttack.get(); }
	EStateBuried* GetStateBuried() const { return mpBuried.get(); }


	AABB* GetWalkCollider()const;
	AABB* GetRotationCollider()const;

	//現在の状態のアクセサ
	eStateEnemy GetStateEnemy() const { return mStateEnemy; }

	//当たり判定を返す
	BoxModel* GetBoxModel()const {return mpEnemyModel.get();}

	//使用フラグを返す関数
	bool GetEnemyUseFlag() const { return mEnemyUseFlag; }

	//始動するフェーズ番号のアクセサ
	void SetMovePhaseNumber(int const& num){ mMovePhaseNumber = num; }
	int GetMovePhaseNumber()const {return mMovePhaseNumber;}

	//反転数のアクセサ
	void SetReverseNumUp()
	{
		mReverseNum++;
	}
	int GetRecerseNum()const { return mReverseNum; }

	//モデルを設定する
	void SetEnemyModel(float const& posy);


	//モデルの向きのアクセサ
	eAngleEnemy GetAngleEnemy()const { return mEnemyModelAngle; }
	void SetAngleEnemy(eAngleEnemy const& angle) { mEnemyModelAngle = angle; }

	//移動処理
	void Move();

	//現在のHPのアクセサ
	int GetEnemyDamage()const { return mEnemyDamage; }
	//ダメージを与える処理
	bool Damage(int const& damagenum);


	//エフェクト稼働フラグのアクセサ
	bool GetEffectFlag() const { return mEffectFlag; }
	void SetEffectFlag(bool const& flag) { mEffectFlag=flag; }

	//エフェクトのアドレスを貰う
	void SetSpriteFlagAddress(bool* flagAddress) { mEffectAddressFlag = flagAddress; }

	//影のアクセサ
	Shadow* GetShadow()const { return mpEnemyShadow.get(); }

	//地上オブジェクトとの接触フラグのアクセサ
	void SetEnemyGroundObjectHitFlag(bool const& flag) { mEnemyGroundObjectHitFlag = flag; }
	bool GetEnemyGroundObjectHitFlag() const { return mEnemyGroundObjectHitFlag; }


	//ブーメラン接触フラグのアクセサ
	void SetBoomerangHitFlag(bool const& flag) { mBoomerangHitFlag = flag; }
	bool GetBoomerangHitFlag() const { return mBoomerangHitFlag; }


	//接触した弾の番号を保存する変数のアクセサ
	int GetSaveBulletNumber()const { return mSaveBulletNumber; }
	void SetSaveBulletNumber(int const& num) { mSaveBulletNumber = num; }

	//エフェクトを作成する
	void CreateNumberEffect(int damageNum);
	//エフェクトをリセットする
	void ResetNumberEffect();


	void SetEnemyWalkState(eEnemyWalkState state) { mWalkState = state; }
	eEnemyWalkState GetEnemyWalkState() { return mWalkState; }

	//接触した案山子の番号を保存する
	int GetSaveScarecrowNumber()const { return mSaveScarecrowNumber; }
	void SetSaveScarecrowNumber(int const& num) { mSaveScarecrowNumber = num; }
	void ResetSaveScarecrowNumber() { mSaveScarecrowNumber = Utility::EXCEPTION_NUM; }

	//プレイヤー追いかけフラグ
	bool GetPlayerChaseFlag()const { return mPlayerChaseFlag; }
	void SetPlayerChaseFlag(bool const& flag) { mPlayerChaseFlag = flag; }
};
