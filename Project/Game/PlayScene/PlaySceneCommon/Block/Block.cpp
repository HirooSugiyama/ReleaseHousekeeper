/*
障害物クラス
*/


#include<pch.h>
#include "Block.h"


//定数
//種類別ブロックの耐久度
//Wood
const int Block::BLOCK_DURABILITY = 10;


/*===================================
コンストラクタ
===================================*/
Block::Block()
	:
	mpBlockModel(nullptr),
	mBlockUseFlag(false),
	mBlockHP(0),
	mIsGravity(false),
	mpArchitecture(nullptr),
	mpNormal(nullptr),
	mpBlockKindBase(nullptr)
{
	mpBlockModel = std::make_unique<BoxModel>();
	mpNormal = std::make_unique<BKStateNormal>();
	mpArchitecture = std::make_unique<BKStateArchitecture>();
}

/*===================================
デストラクタ
===================================*/
Block::~Block()
{
}

/*=================================
初期化
===================================*/
void Block::Initialize()
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("WBlock");
	mpBlockModel->SetModel(model);

	//Stateの初期化
	mpNormal->Initialize(this);
	mpArchitecture->Initialize(this);
}


/*===================================
更新
===================================*/
void Block::Update()
{
	//モデル描画中でないなら
	if (mpBlockModel->GetDrawFlag()==false)
	{
		//未使用状態にする
		mBlockUseFlag = false;
	}

	bool createjuge=mpBlockKindBase->Update();
	//もし建築処理が終わったら
	if (createjuge) 
	{
		this->ChangeStateNormal();
	}	

}

/*=============================================
生成処理
引数：	pos(座標)、scale(拡大処理)
===============================================*/
void Block::Create(DirectX::SimpleMath::Vector3 const& pos,
					DirectX::SimpleMath::Vector3 const& scale)
{
	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();

	//ブロックを使用中にする
	mBlockUseFlag = true;
	//使用中のためブロックを表示
	mpBlockModel->SetDrawFlag(true);

	//モデルを取得する
	auto model = pRM->GetCmoModel("WBlock");

	//モデルを再設定する
	mpBlockModel->SetModel(model);

	//資材をもとにHPを設定する
	mBlockHP = BLOCK_DURABILITY;

	//ブロックの初期設定
	mpBlockModel->SetPosition(pos);
	mpBlockModel->SetScale(scale);

	/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpBlockModel->ReturnHalfSize(scale);
	//設定
	mpBlockModel->SetAABBCollider(pos - halfsize, pos + halfsize);

	//とりあえず建築処理へ
	this->ChangeStateArchitecture();
	//リセット処理
	mpBlockKindBase->Reset();

}

/*===================================
描画
===================================*/
void Block::Draw()
{
	if (mBlockUseFlag)
	{
		mpBlockModel->Draw();
	}
}


/*===================================
終了処理
===================================*/
void Block::Finalize()
{
	mpBlockModel.reset();
}

/*===================================
自身を削除(ポインタなどは消滅しない)
===================================*/
void Block::SelfDestroy()
{
	if (mpBlockModel->GetDrawFlag())
	{
		mpBlockModel->SetDrawFlag(false);

		DirectX::SimpleMath::Vector3 pos=mpBlockModel->GetPosition();
		DirectX::SimpleMath::Vector3 scale=mpBlockModel->GetScale();


		//当たり判定を初期値に戻す
		DirectX::SimpleMath::Vector3 resetpos(DirectX::SimpleMath::Vector3::Zero);
		mpBlockModel->SetAABBCollider(resetpos, resetpos);

		//ブロックを未使用状態にする
		mBlockUseFlag = false;
	}
}