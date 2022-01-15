/*
確認画面
作成日：2021/10/21
*/
#pragma once

//前方宣言
#include"../Common/ObjectTexture.h"
#include"../Common/Cursor.h"

class ConfirmationScreen
{
private:

	//画像拡大率
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_SCALE;
	//初期座標
	static const DirectX::SimpleMath::Vector2 CONFI_TEX_INIT_POSITION;

	//文字描画
	//共通処理
	//拡大率
	static const float STRING_SCALE;
	//YES
	//座標
	static const  DirectX::SimpleMath::Vector2 STRING_YES_POSITION;
	//No
	//座標
	static const  DirectX::SimpleMath::Vector2 STRING_NO_POSITION;

	//確認画面用カーソルの基本情報
	//拡大率
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_SCALE;
	//初期座標
	static const DirectX::SimpleMath::Vector2 CONFI_CURSOR_INIT_POSITION;
	//移動幅
	static const float CONFI_CURSOR_SHIFT;

	//文字テクスチャ
	//拡大率
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_SCALE;
	//座標
	static const  DirectX::SimpleMath::Vector2 STRING_TEXTURE_POSITION;

	//画像
	std::unique_ptr<ObjectTexture> mpConfirTexture;

	//選択カーソル
	std::unique_ptr<Cursor> mpCursor;

	//現在選択している選択肢
	bool mSelectFlag;

	//文字テクスチャ
	std::unique_ptr<ObjectTexture> mpStringTexture;

public:

	//コンストラクタ
	ConfirmationScreen();
	//デストラクタ
	~ConfirmationScreen();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw(bool const& blinkingFlag);

	//選択フラグのアクセサ
	bool GetSelectFlag() const { return mSelectFlag; }


private:

	//文字の描画
	void DrawString(bool const& blinkingFlag);

};

