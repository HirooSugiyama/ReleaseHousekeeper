/*
�e�̈ړ������̊��N���X
�쐬���F2021/10/16
*/
#pragma once

class Bullet;
class BulletStateBase
{
private:
	//������
	Bullet* mpBullet;

protected:
	//�R���X�g���N�^
	BulletStateBase()
		:mpBullet(nullptr)
	{}

	//�f�X�g���N�^
	virtual ~BulletStateBase() = default;

public:
	//�A�N�Z�T
	void SetBuletPointer(Bullet* pBullet) { mpBullet = pBullet; }
	Bullet* GetBullet() { return mpBullet; }

	//�ړ�����
	virtual bool Move() = 0;

	//�`�揈��
	virtual void Draw(){}
};
