/*
当たり判定を回すためだけのクラス
*/
#pragma once





//円情報構造体
struct Circle
{
	//座標
	Vector2XZ mCenter;
	//半径
	float mRadius;

	//コンストラクタ
	//center(球中心座標)、radius(球の半径)
	Circle(const Vector2XZ& center, float radius)
		: mCenter(center)
		, mRadius(radius)
	{
	}

	Circle()
		: mCenter()
		, mRadius()
	{
	}
};


//線分情報構造体
struct LineSegment
{
	//線分の開始点
	DirectX::SimpleMath::Vector2 mStart;
	//線分の終止点
	DirectX::SimpleMath::Vector2 mEnd;

	//コンストラクタ
	//引数：start(線分の開始点座標)、end(線分の終止点座標)
	LineSegment(const DirectX::SimpleMath::Vector2& start, const DirectX::SimpleMath::Vector2& end)
		:mStart(start)
		, mEnd(end)
	{}
	LineSegment()
		: mStart()
		, mEnd()
	{
	}
};

//球情報構造体
struct Sphere
{
	//球の中心座標
	DirectX::SimpleMath::Vector3 mCenter;
	//球の半径
	float mRadius;

	//コンストラクタ
	//center(球中心座標)、radius(球の半径)
	Sphere(const DirectX::SimpleMath::Vector3& center, float radius)
		: mCenter(center)
		, mRadius(radius)
	{
	}

	Sphere()
		: mCenter()
		, mRadius()
	{
	}
};


//AABB管理構造体
struct AABB
{
	//BOXの最小座標
	DirectX::SimpleMath::Vector3 mMin;
	//BOXの最大座標
	DirectX::SimpleMath::Vector3 mMax;

	//コンストラクタ
	//引数：min(BOXの最小座標)、max(BOXの最大座標)
	AABB::AABB(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
		: mMin(min)
		, mMax(max)
	{
	}

	AABB::AABB()
		: mMin()
		, mMax()
	{
	}
	//当たり判定を設定する
	//引数：min(BOXの最小座標)、max(BOXの最大座標)
	void SetCollider(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		mMin = min;
		mMax = max;
	}

	//距離の2乗を求める処理
	float MinDistSq(const DirectX::SimpleMath::Vector3& point) const;
};

//当たり判定をまとめたSingleton
class Collider
{
private:
	//自身
	static Collider* sCollider;

	//コピーコンストラクタ、コピー代入演算子をdelete
	Collider(Collider const& collider) = delete;
	Collider operator=( Collider const& collider) = delete;

	//コンストラクタ
	Collider() = default;

	//デストラクタ
	~Collider() = default;

public:

	//自身のインスタンス
	static Collider& GetColliderInstance();

	void Destroy()const;
	bool Intersect(AABB* box1, AABB* box2);
	bool Intersect(Sphere* s,AABB* box);

	bool Intersect(Circle const& circle, DirectX::SimpleMath::Vector2 const& pixel);
	bool Intersect(Circle const& circle1, Circle const& circle2);

	bool Intersect(LineSegment const& line1,LineSegment const& line2,DirectX::SimpleMath::Vector2& returnpos);



private:
	float Dot(DirectX::SimpleMath::Vector3 const&vel1, DirectX::SimpleMath::Vector3 const& vel2);
	float Sqrt(float const& num);
	float Cross( DirectX::SimpleMath::Vector2 const& a,  DirectX::SimpleMath::Vector2 const& b);
};
