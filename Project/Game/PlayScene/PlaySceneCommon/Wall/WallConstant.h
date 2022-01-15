/*===================================================
壁の座標や拡大率などをまとめた定数用ヘッダーファイル
===================================================*/
#pragma once


//どこの壁か
enum class eWallPosition
{
	LEFT,
	RIGHT,
	GROUND,
	NUM,	//壁の数
};

struct WallConstant
{
	//左の壁
		//拡大率
	static const float WALL_LEFT_SCALE_X;
	static const float WALL_LEFT_SCALE_Y;
	static const float WALL_LEFT_SCALE_Z;
		//座標
	static const float WALL_LEFT_POSITION_X;
	static const float WALL_LEFT_POSITION_Y;
	static const float WALL_LEFT_POSITION_Z;

	//右の壁
		//拡大率
	static const float WALL_RIGHT_SCALE_X;
	static const float WALL_RIGHT_SCALE_Y;
	static const float WALL_RIGHT_SCALE_Z;
		//座標				  
	static const float WALL_RIGHT_POSITION_X;
	static const float WALL_RIGHT_POSITION_Y;
	static const float WALL_RIGHT_POSITION_Z;

};




