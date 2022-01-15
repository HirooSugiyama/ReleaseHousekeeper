/*
フェーズが始まるタイミングを示すカーソルの描画を行うクラス
*/
#include"pch.h"

#include"PhaseCursorManager.h"


//取得座標のずらす量
const float PhaseCursorManager::PHASECURSOR_SHIFT_POSITION = 30.f;


/*===================================
コンストラクタ
===================================*/
PhaseCursorManager::PhaseCursorManager()
	:
	mpPhaseCursor()
{
}

/*===================================
デストラクタ
===================================*/
PhaseCursorManager::~PhaseCursorManager()
{
}

/*===================================
初期化処理
引数：最大フェーズ数
===================================*/
void PhaseCursorManager::Initialize(int const& phasemaxnum)
{
	mpPhaseCursor.resize(phasemaxnum);

	//例外的にここで動的確保を行う
	for (int i = 0; i < phasemaxnum; i++)
	{
		mpPhaseCursor[i] = std::make_unique<PhaseCursor>();
	}

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Initialize();
	}
}


/*=================================
描画処理
===================================*/
void PhaseCursorManager::Draw()
{
	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->Draw();
	}
}

/*===================================
描画する座標を決める
引数：描画開始座標、ずらす幅
===================================*/
void PhaseCursorManager::SetDrawPosition(DirectX::SimpleMath::Vector2 const& startpos, 
									float const& movepos)
{
	//一つ一つの間隔を算出
	float intervel = movepos / static_cast<int>(mpPhaseCursor.size());
	DirectX::SimpleMath::Vector2 pos =
		startpos+ DirectX::SimpleMath::Vector2(PHASECURSOR_SHIFT_POSITION,0.f);

	for (int i = 0; i < static_cast<int>(mpPhaseCursor.size()); i++)
	{
		mpPhaseCursor[i]->SetPosition(pos);
		pos.x += intervel;
	}
}




