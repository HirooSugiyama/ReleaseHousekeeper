/*
�I�����A�j���[�V��������
�����N���X

�쐬���F2021/11/10
*/
#pragma once


#include"EndAnimationBase.h"


//����
#include"../PlaySceneCommon/Administrator/Timer.h"
#include"../../Common/ObjectTexture.h"

class Protecter;
class ObjectTexture;

class EndAnimationLose :public EndAnimationBase
{
private:

	//�萔

	//���j�������W
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_FIRST;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_SECOND;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_THIRD;
	static const DirectX::SimpleMath::Vector3 EXPLOSION_POSITION_FORTH;

	//�����T�C�Y
	static const DirectX::SimpleMath::Vector2 EXPLOSION_SCALE_SMALL;
	static const DirectX::SimpleMath::Vector2 EXPLOSION_SCALE_BIG;

	//�J�����̃^�[�Q�b�g
	static const DirectX::SimpleMath::Vector3 ENDANIM_LOSE_CAMERA_TARGET;
	static const DirectX::SimpleMath::Vector3 ENDANIM_LOSE_CAMERA_EYE;

	//�J����Y�l�ő�l
	static const float CAMERA_MAX_POSITION_Y;

	//�唚���̓r��
	static const int EXPLOSION_FORTH_MIDDLE;

	//�ҋ@����
	static const int WAIT_TIME;


	//���݂̏��
	eLoseAnimStep mState;

	//�G�t�F�N�g�A�h���X�ۑ��p�ϐ�
	bool* mEffectAddress;

	//�^�C�}�[
	std::unique_ptr<Timer> mpTimer;

	int mMiniTimer;

	//�|�C���^�ۑ��p�ϐ�
	Protecter* mpProtecter;

	//�����摜
	std::unique_ptr<ObjectTexture> mpLoseTexture;

	//BGM��ID
	int mBGMID;

public:

	//�R���X�g���N�^
	EndAnimationLose();
	//�f�X�g���N�^
	~EndAnimationLose();


	//������
	void Initialize()override;
	//�X�V
	bool Update()override;
	//�`��
	void Draw()override;

	void SetProtecterPointer(Protecter* pProtecter) { mpProtecter = pProtecter; }

	//���݂̏�Ԃ̎擾
	eLoseAnimStep GetState() { return mState; }

private:

	//�G�t�F�N�g�ݒ�
	void SetEffect(DirectX::SimpleMath::Vector3 pos,DirectX::SimpleMath::Vector2 scale);

};