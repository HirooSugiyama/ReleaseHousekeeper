/*
�e�N���X
�쐬���F2021/09/17
*/
#pragma once

//�񋓌^�̎g�p
#include"../Weapon/WeaponeType.h"

//����
#include"../ObjectModel/SphereModel.h"
#include"BulletStateNormalBullet.h"
#include"BulletStateExplosion.h"

//�O���錾
struct BulletInfomation;		//�����Ŏg�p
struct Sphere;					//�Ԃ�l�Ŏg�p

class BulletStateBase;			//��ԕ������N���X
class BulletStateNormalBullet;	//��ԕ������N���X
class BulletStateBoomerang;		//��ԕ������N���X
class BulletStateExplosion;		//��ԕ������N���X
	
class Bullet
{
private:

	//�����蔻��̔��a
	static const float COLLIDER_RADIUS;

	//�����蔻��g��W��
	static const float COLLIDER_RADIUS_EXPANSION;

	//���j�[�N�|�C���^
	std::unique_ptr<SphereModel> mpBulletModel;

	//�e�̍U����
	int mBulletAttackNum;

	//�e�̑��x
	float mBulletVelocity;

	//���݂̒e�̎�����
	eWeaponType mWeaponType;

	//��ԕ���
	BulletStateBase* mpStateBase;
	std::unique_ptr<BulletStateNormalBullet> mpNormalBullet;
	std::unique_ptr<BulletStateExplosion> mpExplosion;
	BulletStateBoomerang* mpBoomerangBullet;			//�B��̕��̂��ߊǗ��N���X����擾����

	//�e�����t���O
	bool mExplosionFlag;

public:

	//�R���X�g���N�^
	Bullet();
	//�f�X�g���N�^
	~Bullet();
	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�쐬����
	void Create(DirectX::SimpleMath::Vector3 const& pos, eWeaponType const& type);

	//���g�p��Ԃւ̕ύX�֐�
	void SelfDestroy();


	//�g�p�����ǂ�����Ԃ��A�N�Z�T
	bool GetUseFlag()const;

	//Z���W��Ԃ�
	float GetBulletPositionZ()const;

	//�e���ۑ��p�֐�
	void SetBulletInfomation( BulletInfomation const& pBulletInfomation);

	//�U���͂̃A�N�Z�T
	int GetBulletAttackNum()const { return mBulletAttackNum; }

	//�����蔻��̃A�N�Z�T
	Sphere* GetBulletModelCollider()const;

	//�e�̎�ނ̃A�N�Z�T
	eWeaponType GetBulletWeaponType() const { return mWeaponType; }

	//���f���̍��W�̃A�N�Z�T
	SphereModel* GetBulletModel()const { return mpBulletModel.get(); }

	//�e�̑��x�̃A�N�Z�T
	float GetBulletVelocity()const { return mBulletVelocity; }

	//�|�C���^���󂯎��
	void SetBoomerangPointer(BulletStateBoomerang* pBoomerang) { mpBoomerangBullet = pBoomerang; }

	//�e�����t���O�̃A�N�Z�T
	void SetExplosionFlag(bool const& flag) { mExplosionFlag = flag; }
	bool GetExplosionFlag() const { return mExplosionFlag; }

	//�����蔻���{�ɂ���
	void SetDoubleCollider();

private:
	//��ԕύX�֐�
	void ChangeStateNormalBullet() { mpStateBase = (BulletStateBase*)mpNormalBullet.get(); }
	void ChangeStateBoomerang() { mpStateBase = (BulletStateBase*)mpBoomerangBullet; }
	void ChangeStateExplosion() { mpStateBase = (BulletStateBase*)mpExplosion.get(); }

	//�����蔻�萶������
	void SetCollider();
};

