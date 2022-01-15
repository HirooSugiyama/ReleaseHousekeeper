/*
�^�C�g���V�[��
*/
#pragma once

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "../IScene.h"
#include "Game/GameMain.h"
#include "Game/TEST/FbxMeshFile.h"




enum class STATE
{
	BEGIN,
	DRAW,
	END,
};


namespace DirectX
{
	class BasicEffect;
}

class Camera;
class GridFloor;

class TESTScene :public IScene
{
private:
	std::unique_ptr<DirectX::CommonStates> mCommonState;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> mSpriteFont;
	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> mpBasicEffect;
	//���f��
	FbxMeshFile* mModel;

	// �f�o�b�O�J����
	std::unique_ptr<Camera> mpCamera;

	// �O���b�h��
	std::unique_ptr<GridFloor> mpGridFloor;

	//�s��
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;


	//���݂̕`����
	STATE mState;

public:
	//�R���X�g���N�^
	TESTScene();
	//�f�X�g���N�^
	~TESTScene();
	//������
	void Initialize()override;
	//�X�V
	GAME_SCENE Update(const DX::StepTimer& timer)override;
	//�`��
	void Draw()override;
	//�I������
	void Finalize()override;



	//�`��J�n�ƏI��
	/**
	* @brief �`��J�n�֐�@n
	* �`�揈�����s���ꍇ�A�K�����̊֐��̌�Ɏ��s����@n
	* ���s���Ȃ��ƕ`�悳��Ȃ�
	*/
	void StartRendering();

	/**
	* @brief �`��I���֐�@n
	* �`�揈�������������ꍇ�A�K�����̊֐������s����
	* ���s���Ȃ��ƕ`����e�����f����Ȃ�
	*/
	void FinishRendering();


	void SetUpContext();

};
