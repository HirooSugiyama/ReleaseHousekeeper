/*
�G�s���p�^�[���̊��N���X
�쐬���F2021/08/31
*/
#pragma once



//�񋓌^�̎g�p
#include"StateEnemy.h"
#include"AngleEnemy.h"


class Enemy;
class EnemyStateBase
{
protected:
	//�R���X�g���N�^
	EnemyStateBase() = default;

	//�f�X�g���N�^
	virtual ~EnemyStateBase() = default;

public:
	//����������
	virtual void Initialize(Enemy* pEnemy) = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw() {}

	//State�J�n���̏���������
	virtual void Reset() = 0;


protected:
	//�����蔻���ݒ肷��
	virtual void SetAABBCollider() = 0;

};
