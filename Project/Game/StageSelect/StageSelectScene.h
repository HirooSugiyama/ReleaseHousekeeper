/*
�X�e�[�W�I���V�[��
*/
#pragma once


#include "../IScene.h"
#include "Game/GameMain.h"

//�I�����������v���C�V�[����(�\���̂��g�p)
#include"Game/Interface/SceneInterface/StoPSceneInterface.h"

//�񋓌^�̎g�p
#include"StageNumer.h"

//����
#include"../Common/Cursor.h"
#include"StageInfomation.h"
#include"StageNumberTag.h"
#include"ConfirmationScreen.h"
#include"../Common/Blinking.h"
#include"../Common/Cloud.h"
#include"../Common/ObjectTexture.h"

class StageSelectScene : public IScene
{
private:
	//�ԍ��̏c�ړ�
	static const int SELECTNUM_VERTICAL_SHIFT;

	//1��ʓ�����̍ő�X�e�[�W��
	static const int SCREEN_STEGE_MAX_NUM = 6;

	//�J�[�\���̊g�嗦
	static const DirectX::SimpleMath::Vector2 CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 CURSOR_INIT_POSITION;
	//�ړ���
	static const DirectX::SimpleMath::Vector2 CURSOR_VELOCITY;

	//�^�O�̏������W
	static const DirectX::SimpleMath::Vector2 TAG_INIT_POSITION;
	//��
	static const float TAG_SHIFT;

	//�m�F��ʗp�J�[�\���̊�{���
	//�g�嗦
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_SCALE;
	//�������W
	static const DirectX::SimpleMath::Vector2 SELECT_CURSOR_INIT_POSITION;
	//�ړ���
	static const float SELECT_CURSOR_SHIFT;

	//��̈ʒu
	static const DirectX::SimpleMath::Vector2 NAME_POSITION;
	static const DirectX::SimpleMath::Vector2 NAME_SCALE;



	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;

	//�J�[�\��
	std::unique_ptr<Cursor> mpCursor;

	//�X�e�[�W�e����
	std::unique_ptr<StageInfomation> mpStageInfo;

	//�^�O
	std::unique_ptr<StageNumberTag> mpTag[SCREEN_STEGE_MAX_NUM];

	//�m�F���
	std::unique_ptr<ConfirmationScreen> mpConfirScreen;

	//�_��
	std::unique_ptr<Blinking> mpTextureBlinking;

	//��
	std::unique_ptr<ObjectTexture> mpStageSelectNameTexture;

	//�_
	std::unique_ptr<Cloud> mpCloud;

	//���ݑI�𒆂̔ԍ�
	int mSelectNum;

	//�I���t���O
	bool mSelectFlag;

	//BGM��ID
	int mBGMID;

public:

	// �R���X�g���N�^
	StageSelectScene();

	// �f�X�g���N�^
	~StageSelectScene();

	// ������
	void Initialize() override;

	// �X�V
	eGameScene Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:
	//���[�h�I��
	void StageSelect();

	//�t�@�C�����Z�o
	std::string SetFileName();

	//�J�[�\����������
	void CursorUp();

	//�J�[�\����������
	void CursorDown();


	//�ԍ���ݒ肷��
	void SetNumberTag();

private:
	//BGM�𗬂�
	void PlayBGM()override;

	//BGM���~�߂�
	void StopBGM()override;

};