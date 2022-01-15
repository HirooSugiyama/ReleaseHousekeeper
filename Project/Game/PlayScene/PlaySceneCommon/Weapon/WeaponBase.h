/*
������N���X
�쐬���F2021/09/14
*/
#pragma once

//�񋓌^�̎g�p
#include "WeaponeType.h"
//����
#include"../ObjectModel/ObjectModel.h"

class BulletManager;	//�|�C���^�ۑ��p
class Player;			//�|�C���^�ۑ��p

class WeaponBase
{
private:

	//���탂�f��
	std::unique_ptr<ObjectModel> mpWeaponModel;

	//�|�C���^�ۑ��p�ϐ�
	BulletManager* mpBulletManager;
	Player* mpPlayer;

	//���e��
	int mMaxBulletNum;

	//�U����
	int mWeaponBulletAttackNum;

public:
	//�R���X�g���N�^
	WeaponBase();

	//�f�X�g���N�^
	virtual ~WeaponBase() = default;

	//������
	virtual void Initialize() = 0;

	//�`��
	virtual void Draw() = 0;

	//�e���ˏ���
	virtual void Shot() = 0;

	//���Z�b�g����
	virtual void Reset() {}

	//���f���̎擾
	ObjectModel* GetWeaponModel()const { return mpWeaponModel.get(); }

	//���W��ݒ肷��
	virtual void SetPosition(DirectX::SimpleMath::Vector3 const& pos);

	//�w���z��Ԃ�
	//��{�I�ɔh����ŏ㏑���B
	virtual int GetWeaponPrice()const = 0;

	//�|�C���^��ۑ�����
	void SetBulletManagerPointer(BulletManager* pBulletManager) { mpBulletManager = pBulletManager; }
	void SetPlayerPointer(Player* pPlayer) { mpPlayer = pPlayer; }

	//�e���̃A�N�Z�T
	int GetBulletNum() const { return mMaxBulletNum; }
	void SetBulletNum(int const& bulletnum) { mMaxBulletNum = bulletnum; }
	//�e��1�����炷
	void ReduceBulletNum() { mMaxBulletNum--; }

	//�U���͂̃A�N�Z�T
	void SetWeaponBulletAttackNum(int const& num) { mWeaponBulletAttackNum = num; }

	//�����j������
	bool Destroy();


protected:
	//�A�N�Z�T
	BulletManager* GetBulletManager()const { return mpBulletManager; }
	Player* GetPlayer()const { return mpPlayer; }
	int GetWeaponBulletAttackNum()const { return mWeaponBulletAttackNum; }
};
