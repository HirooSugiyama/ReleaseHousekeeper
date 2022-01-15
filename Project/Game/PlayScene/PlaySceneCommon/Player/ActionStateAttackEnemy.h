/*
�v���C���[�̍s����ԕ����X�e�[�g�p�^�[��
�쐬���F2021/09/14
*/
#pragma once

//���N���X
#include"ActionStateBase.h"

//�񋓌^�̎g�p
#include"../Weapon/WeaponeType.h"

//����
#include"../Weapon/WeaponHand.h"


//���ݍs���Ă���s��
enum class eAttackState
{
	NONE,
	WEEK_ATTACK,
	STRONG_ATTACK,
};


//�O���錾
class WeaponBase;	//������N���X

class WeaponManager;//����Ǘ��N���X(�|�C���^�ۑ��p)
class BulletManager;//�e�Ǘ��N���X(�|�C���^�ۑ��p)

class ActionStateAttackEnemy :public ActionStateBase
{
private:
	//�����ł��镐��
	enum class ePositionsessionWeapon
	{
		HAND,
		STRONG_WEAPON,
	};


	//�v���C���[�̍��W�ƕ��탂�f���̍��W�̍�
	static const DirectX::SimpleMath::Vector3 WEPON_MODEL_PLAYER_SHIFT_POSITION;


	//����Ǘ��N���X
	std::unique_ptr<WeaponHand> mpHand;	//�������͌Œ�
	WeaponBase* mpStrongWeapon;			//�������͉�

	//�|�C���^�ۑ��p
	Player* mpPlayer;
	WeaponManager* mpWeaponManager;
	BulletManager* mpBulletManager;

	//���݂̏�Ԃ�\��
	eAttackState mAttackState;

	//���ݑ������Ă��镐��
	eWeaponType mUseWeapon;

	//�U������t���O(true���U���ł���)
	bool mAttackFlag;

	//�}�V���K����pSEID�ۑ��p�ϐ�
	int mMachinGunSEID;

public:

	//�R���X�g���N�^
	ActionStateAttackEnemy();
	//�f�X�g���N�^
	~ActionStateAttackEnemy();
	//����������
	void Initialize(Player* pPlayer);
	//�X�V����
	void Update();
	//State�J�n���̏���������
	void Reset();
	//�`�揈��
	void Draw();

	//��������������ς���
	void ChangeStrongWeapon(eWeaponType const& weapon);

	//��U����Ԃ�����
	WeaponHand* GetHand()const { return mpHand.get(); }
	//���U����Ԃ�����
	WeaponBase* GetStrongWeapon()const { return mpStrongWeapon; }

	//�|�C���^�ۑ��p�ϐ��̃A�N�Z�T
	void SetWeaponManagerPointer(WeaponManager* pWeaponManager) { mpWeaponManager = pWeaponManager; }
	void SetBulletManagerPointer(BulletManager* pBulletManager) { mpBulletManager = pBulletManager; }

	//�������������
	void UseStrongWeapon();

	//���݂̕����Ԃ�Ԃ��֐�
	eAttackState GetAttackState()const { return mAttackState; }


private:
	//���㕐��̐؂�ւ�
	void ChangeStrongHand();

	//�����U���̍U������
	void StrongWeaponAttack();

	//�u�[��������p����
	void BoomerangUpdate();
};
