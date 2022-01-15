/*
�J��������t�F�[�Y
�쐬���F2021/10/11
*/
#pragma once

//�񋓌^�̎g�p
#include"../PlaySceneRotationCamera/RotationState.h"

//���N���X
#include"PlayScenePhaseBase.h"

//����
#include"Libraries/MyLibraries/RotationCamera.h"
#include"../../Common/Blinking.h"

//�O���錾
class Timer;			//�J�E���g�_�E���p�^�C�}�[
class ObjectTexture;	//Skip�{�^��

class PScenePhaseRotationCamera :public PlayScenePhaseBase
{
private:
	//�X�L�b�v�{�^���̍��W
	static const DirectX::SimpleMath::Vector2 SKIPBOTTON_POSITION;
	//�X�L�b�v�{�^���̊g�嗦
	static const DirectX::SimpleMath::Vector2 SKIPBOTTON_SCALE;

	//�J�E���g�_�E������
	static const int COUNTDOWN_MAX_NUM;

	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//�J�E���g�_�E���p�^�C�}�[
	std::unique_ptr<Timer> mpCountDownTimer;

	//����J����������
	std::unique_ptr<RotationCamera> mpRotationCamera;

	//Skip�{�^���摜
	std::unique_ptr<ObjectTexture> mpSkipButton;

	//�_�ŃN���X
	std::unique_ptr<Blinking> mpSkipButtonBlinking;

	//���݂̏��
	eRotationState mState;

public:
	//�R���X�g���N�^
	PScenePhaseRotationCamera();

	//�f�X�g���N�^
	~PScenePhaseRotationCamera();
	
	//������
	void Initialize(PlayScene* pPlayScene)override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

	//���Z�b�g����
	void Reset()override;

private:

	//�X�L�b�v����
	bool Skip();

};