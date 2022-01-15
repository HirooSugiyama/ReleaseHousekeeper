/*
壁クラス
*/

#include<pch.h>
#include"Wall.h"

/*===================================
コンストラクタ
===================================*/
Wall::Wall()
	:
	mpWallModel(nullptr)
{
	//モデルのメモリ確保
	mpWallModel = std::make_unique<BoxModel>();
}

/*===================================
デストラクタ
===================================*/
Wall::~Wall()
{
}
/*===================================
初期化処理
引数：pos(座標)、scale(拡大率)
===================================*/
void Wall::Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 scale)
{

	//リソースマネージャの準備
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel("Wall");
	mpWallModel->SetModel(model);
	mpWallModel->SetPosition(pos);
	mpWallModel->SetScale(scale);

		/*当たり判定生成*/
	//拡大率の半分の値を生成
	DirectX::SimpleMath::Vector3 halfsize = mpWallModel->ReturnHalfSize(scale);
	//設定
	mpWallModel->SetAABBCollider(pos - halfsize, pos + halfsize);
}

/*===================================
描画処理
===================================*/
void Wall::Draw()
{
	mpWallModel->Draw();
}