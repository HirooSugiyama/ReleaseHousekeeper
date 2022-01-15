/*
�I�����o�t�F�[�Y
�쐬���F2021/10/11
*/
#pragma once


//���N���X
#include"PlayScenePhaseBase.h"

//�񋓌^�̎g�p
#include"../PlaySceneEndAnimation/EndAnimationState.h"

//����
#include"../PlaySceneEndAnimation/EndAnimationLose.h"
#include"../PlaySceneEndAnimation/EndAnimationWin.h"

//�O���錾
class EndAnimationBase;

class PScenePhaseEndAnimation :public PlayScenePhaseBase
{
private:

	//PlayScene�I�u�W�F�N�g�֕ۑ��p�̃|�C���^
	PlayScene* mpPlayScene;

	//�g�p����A�j���[�V�����̎��
	eUseEndAnim mUseAnim;

	//�A�j���[�V�������
	std::unique_ptr<EndAnimationWin> mpWinAnim;
	std::unique_ptr<EndAnimationLose> mpLoseAnim;


public:
	//�R���X�g���N�^
	PScenePhaseEndAnimation();

	//�f�X�g���N�^
	~PScenePhaseEndAnimation();
	
	//������
	void Initialize(PlayScene* pPlayScene)override;

	//�X�V
	void Update()override;

	//�`��
	void Draw()override;

	//���Z�b�g����
	void Reset()override;


	void SetUseAnim(eUseEndAnim anim) { mUseAnim = anim; }

	

};