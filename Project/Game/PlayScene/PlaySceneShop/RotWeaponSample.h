/*
���탂�f������]�����邾���̃N���X
�쐬���F2021/10/15
*/


//����
#include"../PlaySceneCommon/ObjectModel/ObjectModel.h"

class RotWeaponSample
{
private:
	//���W
	static const DirectX::SimpleMath::Vector3 ROTMODEL_POSITION;
	//�g�嗦
	static const DirectX::SimpleMath::Vector3 ROTMODEL_SCALE;

	//��]���x
	static const float ROT_SPEED;


	//��]�����郂�f��
	std::unique_ptr<ObjectModel> mpRotModel;

	//���݂̊p�x
	float mModelRot;
	

public:

	//�R���X�g���N�^
	RotWeaponSample();
	//�f�X�g���N�^
	~RotWeaponSample();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//���Z�b�g����
	void Reset();

	//���f�������擾����
	void SetWeaponModel(DirectX::Model* model);

};

