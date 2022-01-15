/*
�J�E���g�_�E���t�F�[�Y
�쐬���F2021/09/30
*/
#pragma once

//���N���X
#include"PlayScenePhaseBase.h"

//����
#include"../../Common/SpriteNumber/SpriteNumber2D.h"
#include"../PlaySceneCommon/Administrator/Timer.h"

class PScenePhaseCountDown :public PlayScenePhaseBase
{
private:

	//�J�E���g�_�E������
	static const int CountDown_MAX_NUM;

	//��ʒ����l
	static const DirectX::SimpleMath::Vector2 WINDOW_CENTER;


	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//�J�E���g�_�E���p�^�C�}�[
	std::unique_ptr<Timer> mpCountDownTimer;

	std::unique_ptr<SpriteNumber2D> mpCountDownString;


public:
	//�R���X�g���N�^
	PScenePhaseCountDown();

	//�f�X�g���N�^
	~PScenePhaseCountDown();
	
	//������
	void Initialize(PlayScene* pPlayScene)override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

	//State�ύX�O�̃��Z�b�g����
	void Reset()override;
};