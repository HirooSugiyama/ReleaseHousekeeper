/*
�e���Ǘ��t�@�C��
�쐬���F2021/10/10
*/
#pragma once


//�񋓌^�̎g�p
#include"../Weapon/WeaponeType.h"


//�O���錾
namespace DirectX
{
	class Model;	//�\���̂ŏ���
}

//�e���\����
struct BulletInfomation
{
	//�e�̃��f��
	DirectX::Model* mBulletModel;
	//�e�̑��x
	float mBulletVelocityZ;
	//�e�̊g�嗦
	DirectX::SimpleMath::Vector3 mBulletScale;
	//�e�̍U����
	int mBulletAttackNum;
	//�e�̃C���^�[�o��
	int mBulletIntervalNum;

};

class BulletType
{
private:

	//�ǂݍ��ޏ��
	enum eReadInfo
	{
		MODEL_TAG,
		SPEED,
		SCALE_X,
		SCALE_Y,
		SCALE_Z,
		ATTACK_NUM,
		INTERVAL
	};

	//�e�̎�ނ��Ƃ̏��Ǘ��p�ϐ�
	std::unordered_map<eWeaponType, std::unique_ptr<BulletInfomation>> mpBulletInfomation;

public:

	//�R���X�g���N�^
	BulletType();
	//�f�X�g���N�^
	~BulletType();

	//��ނɉ������e�̏���Ԃ��֐�
	BulletInfomation* GetBulletInfomation(eWeaponType const& weaponType)
	{
		return mpBulletInfomation[weaponType].get();
	}


	//CSV�t�@�C���ǂݍ���
	void SetCSV(std::string const& filepath);

};
