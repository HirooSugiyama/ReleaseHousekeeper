/*
弾の移動処理の基底クラス
作成日：2021/10/16
*/
#pragma once

class Bullet;
class BulletStateBase
{
private:
	//持ち主
	Bullet* mpBullet;

protected:
	//コンストラクタ
	BulletStateBase()
		:mpBullet(nullptr)
	{}

	//デストラクタ
	virtual ~BulletStateBase() = default;

public:
	//アクセサ
	void SetBuletPointer(Bullet* pBullet) { mpBullet = pBullet; }
	Bullet* GetBullet() { return mpBullet; }

	//移動処理
	virtual bool Move() = 0;

	//描画処理
	virtual void Draw(){}
};
