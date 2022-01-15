/*
敵管理クラス
*/
#pragma once


#include"../../Effect/EffectType.h"

//所持
#include"EnemyCall.h"
#include"Enemy.h"

//前方宣言
class Block;				//当たり判定
class Player;				//当たり判定
class Protecter;			//当たり判定
class Administrator;		//ポインタ(引数)
class DangerousLine;		//ポインタ(引数)
class GroundObjectManager;	//当たり判定
class BulletManager;		//当たり判定
struct AABB;				//当たり判定
class EffectSpriteTexture;	//所持
class CameraBase;				//ポインタ(引数)

class EnemyManager
{
private:

	//定数
	//初期サイズ
	static const int ENEMY_INIT_SIZE;
	 
	//未使用の敵の出現座標
	static const DirectX::SimpleMath::Vector3 NOT_SET_ENEMY_POSITION;

	//初期拡大率
	static const DirectX::SimpleMath::Vector3 ENEMY_INIT_SCALE;

	//敵の攻撃力
	static const int ENEMY_ATTACK_NUM;

	//敵が乱数出向く向きの数
	static const int ENEMY_RAND_ANGLE_NUM;

	//スコア値
	static const int ENEMY_SCORE;

	//エフェクトの出現させる座標
	static const DirectX::SimpleMath::Vector3 EFFECT_SHIFT_POSITION;

	//敵のプレイヤー捕捉範囲
	static const float ENEMY_CAPTURE_RANGE;


	//変数
	std::vector<std::unique_ptr<Enemy>> mpEnemy;

	//敵出現インターバル
	int mEnemyAppearanceInterval;

	//呼び出しクラス
	std::unique_ptr<EnemyCall> mpEnemyCall;

	//ポインタ保存
	Administrator* mpAdministrator;

	//敵の最大出現座標
	int mMaxEnemySpawnPositionZ;

	//読み込むファイル名
	std::string mLoadEnemyFileName;

	//現在のフェーズ番号
	int mNowPhaseNum;

	//最大フェーズ数
	int mMaxPhaseNum;

	//衝突判定用フラグ変数の宣言
	std::vector<bool> mEnemyBlockHitFlag;

	//現在の敵の撃破数
	int mNowEnemyBreakNum;

public:
	//関数
	//コンストラクタ
	EnemyManager();
	//デストラクタ
	~EnemyManager();
	//初期化
	void Initialize(CameraBase* camera, Administrator* pAdministrator);
	//更新
	void Update();
	//描画
	void Draw();
	//終了処理
	void Finalize();

	//敵の回数分だけ当たり判定を回す処理
	void RoolBulletManagerChackhit(BulletManager* pBulletManager);

	//ブロックと敵の当たり判定
	void ChackHitBlocklEnemy(Block* pBlock,int const& blockNum);

	//敵の回転処理
	void RotationEnemy();

	//Todo:当たり判定→Detect

	//プレイヤーと敵の当たり判定
	void ChackHitPlayerEnemy(Player* pPlayer);
	void ChackHitNormalAttackPlayerEnemy(Player* pPlayer);	//プレイヤー攻撃時の判定

	//拠点と敵の当たり判定
	void ChackHitProtecterEnemy(Protecter* pProtecter);

	//地上オブジェクトと敵の当たり判定
	void ChackHitGroundObjectEnemy(AABB* pObjectCollider);

	//柵と敵の当たり判定
	void ChackHitWallEnemy(AABB* pWallCollider);

	//危険信号ラインと敵の当たり判定
	bool ChackHitDangerousLineEnemy(DangerousLine* pDangerousLine);

	//対象と敵の距離判定
	void ChackDistanceTargetEnemy(DirectX::SimpleMath::Vector3 const& pos,bool playerFlag=false);

	//リセット処理
	void Reset();

	//読み込むファイル名の取得
	void SetLoadEnemyFileName(std::string const& filename) { mLoadEnemyFileName = filename; }

	//読み込むファイル名を作成
	std::string CreateLoadEnemyFileName(std::string const& stagenum);

	//フェーズ番号の取得
	void SetNowPhaseNum(int const& phasenumber) { mNowPhaseNum = phasenumber; }

	void SetMaxPhaseNum(int const& phasenumber) { mMaxPhaseNum = phasenumber; }


	//敵の衝突判定フラグのアクセサ
	bool GetEnemyHitFlag(int const& i) const { return mEnemyBlockHitFlag[i]; }

	//全ての敵の衝突判定フラグを降ろす処理
	void ResetEnemyHitFlag();

	//全ての敵が死亡したことを確認するフラグ
	bool AllEnemyDeathFlag();

	//敵撃破数のアクセサ
	int GetBreakEnemyNum()const { return mNowEnemyBreakNum; }

	//敵の最大数のアクセサ
	int GetMaxEnemyNum()const { return static_cast<int>(mpEnemy.size()); }

	//対象の弾番号を持つ敵の弾番号を初期化する
	void ResetBulletNum(int const& bulletIndex);

	//残っている敵を一斉に爆破させる
	void ExplosionSimultaneousEnemy();



private:

	//ファイルから情報を取得する
	void LoadFile(std::string filepath, CameraBase* camera);

	
	//エフェクトを設定する
	void SetEnemyEffect(eEffectType type,DirectX::SimpleMath::Vector3 pos,
		int index,bool flagOn=false);


	//全てのブーメラン接触フラグを下す
	void ResetBoomerangHitFlag();

};
