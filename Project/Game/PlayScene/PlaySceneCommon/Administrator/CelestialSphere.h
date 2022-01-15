/*
�V���N���X
�쐬���F2021/06/19
*/
#pragma once



//����
#include"../../PlaySceneCommon/ObjectModel/ObjectModel.h"


class CelestialSphere
{
	
private:
	//�萔
	enum class eWhichLight:int
	{
		_0,
		_1,
		_2,
	};

	//�V���̔��a
	static const DirectX::SimpleMath::Vector3 SPHERE_RADIUS;

	//�J���[���ő�l��
	static const DirectX::SimpleMath::Vector3 MAX_COLOR_NUM;

	//�V�����f��
	std::unique_ptr<ObjectModel> mpSphere;

public:
	//�R���X�g���N�^
	CelestialSphere();
	//�f�X�g���N�^
	~CelestialSphere();

	//������
	void Initialize();

	//�`��
	void Draw();

	//�V����ς���
	void ChangeSphereModelNight();
	void ChangeSphereModelDay();

};