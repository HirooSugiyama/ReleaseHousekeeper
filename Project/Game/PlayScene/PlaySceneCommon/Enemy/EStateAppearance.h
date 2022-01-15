/*
�G�s���p�^�[���`�G�o�����̉��o�`
�쐬���F2021/08/31
*/
#pragma once

#include"EnemyStateBase.h"

//�O���錾
class EffectSpriteTexture;
class Camera;

class EStateAppearance :public EnemyStateBase
{
private:

	//���f���ړ��X�s�[�h
	static const float ENEMY_MODEL_MOVE_VELOCITY;
	//���f��Y���ő�l
	static const float ENEMY_MODEL_MAX_POSITIONY;

	//�o���G�t�F�N�g�p�萔


	//�ۑ��p�ϐ�
	Enemy* mpEnemy;
	Camera* mpCamera;

	//�t���O�Ǘ��p�ϐ�
	EffectSpriteTexture* mpAppearanceEffect;


public:
	//�R���X�g���N�^
	EStateAppearance();

	//�f�X�g���N�^
	~EStateAppearance()override;

	//����������
	void Initialize(Enemy* pEnemy)override;

	//�X�V����
	void Update()override;

	//�`�揈��
	void Draw()override;

	//State�J�n���̏���������
	void Reset()override;

	//�J�����̃|�C���^��ۑ�
	void SetCameraPointer(Camera* pCamera)
	{
		mpCamera = pCamera;
	}

private:
	//�����蔻���ݒ肷��
	virtual void SetAABBCollider() {}

	//�G�t�F�N�g�̐ݒ�
	void SetEffect();

};