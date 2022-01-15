/*
�I�����A�j���[�V��������
�����N���X

�쐬���F2021/11/10
*/
#pragma once


#include"EndAnimationBase.h"

//����
#include"../PlaySceneCommon/Administrator/Timer.h"


class EnemyManager;
class Administrator;

class EndAnimationWin :public EndAnimationBase
{
private:

	//�J�����̃^�[�Q�b�g
	static const DirectX::SimpleMath::Vector3 ENDANIM_WIN_CAMERA_TARGET;
	static const DirectX::SimpleMath::Vector3 ENDANIM_WIN_CAMERA_EYE;

	//�J����Z�l�ŏ��l
	static const float CAMERA_MIN_POSITION_Z;


	//�ϐ�
	//���݂̏��
	eWinAnimStep mState;

	//�^�C�}�[
	std::unique_ptr<Timer> mpTimer;

	//�|�C���^�ۑ��p�ϐ�
	EnemyManager* mpEnemyManager;
	Administrator* mpAdministrator;

public:

	//�R���X�g���N�^
	EndAnimationWin();
	//�f�X�g���N�^
	~EndAnimationWin();


	//������
	void Initialize()override;
	//�X�V
	bool Update()override;
	//�`��
	void Draw()override;

	//�|�C���^�ۑ�
	void SetPointer(EnemyManager* pEnemyManager, Administrator* pAdministrator)
	{
		mpEnemyManager = pEnemyManager; 
		mpAdministrator = pAdministrator;
	}

};