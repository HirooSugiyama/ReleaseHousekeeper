/*
�����蔻����񂷂��߂����̃N���X
*/
#pragma once





//�~���\����
struct Circle
{
	//���W
	Vector2XZ mCenter;
	//���a
	float mRadius;

	//�R���X�g���N�^
	//center(�����S���W)�Aradius(���̔��a)
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


//�������\����
struct LineSegment
{
	//�����̊J�n�_
	DirectX::SimpleMath::Vector2 mStart;
	//�����̏I�~�_
	DirectX::SimpleMath::Vector2 mEnd;

	//�R���X�g���N�^
	//�����Fstart(�����̊J�n�_���W)�Aend(�����̏I�~�_���W)
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

//�����\����
struct Sphere
{
	//���̒��S���W
	DirectX::SimpleMath::Vector3 mCenter;
	//���̔��a
	float mRadius;

	//�R���X�g���N�^
	//center(�����S���W)�Aradius(���̔��a)
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


//AABB�Ǘ��\����
struct AABB
{
	//BOX�̍ŏ����W
	DirectX::SimpleMath::Vector3 mMin;
	//BOX�̍ő���W
	DirectX::SimpleMath::Vector3 mMax;

	//�R���X�g���N�^
	//�����Fmin(BOX�̍ŏ����W)�Amax(BOX�̍ő���W)
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
	//�����蔻���ݒ肷��
	//�����Fmin(BOX�̍ŏ����W)�Amax(BOX�̍ő���W)
	void SetCollider(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		mMin = min;
		mMax = max;
	}

	//������2������߂鏈��
	float MinDistSq(const DirectX::SimpleMath::Vector3& point) const;
};

//�����蔻����܂Ƃ߂�Singleton
class Collider
{
private:
	//���g
	static Collider* sCollider;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete
	Collider(Collider const& collider) = delete;
	Collider operator=( Collider const& collider) = delete;

	//�R���X�g���N�^
	Collider() = default;

	//�f�X�g���N�^
	~Collider() = default;

public:

	//���g�̃C���X�^���X
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
