//
// GameMain.h
//
#pragma once

#include "StepTimer.h"



// �V�[���̗�
enum class eGameScene : int
{
    NONE,

    TITLE,
    STAGE_SELECT,
    PLAY,

};

// �O���錾
class DebugCamera;
class ObjectTexture;

class IScene;

/// <summary>
/// Game�N���X����A���[�U���������𔲂��o�����N���X
/// </summary>
class GameMain
{
private:
    //�萔
    //1��ڂ̃R���g���[���[
    static const int GAMEPAD_ONE = 0;
    //�Q�[���p�b�h�A�C�R��
    //���W
    static const DirectX::SimpleMath::Vector2 GAMEPAD_ICON_POSITION;
    //�g�嗦
    static const DirectX::SimpleMath::Vector2 GAMEPAD_ICON_SCALE;

    //�ϐ�
    
    // �}�E�X
    std::unique_ptr<DirectX::Mouse> mMouse;


	// ���̃V�[���ԍ�
	eGameScene mNextScene;

	// �V�[��
	IScene* mpScene;




public:
    GameMain();
    ~GameMain();

    void Initialize();
    void Update(const DX::StepTimer& timer);
    void Render();
    void Finalize();

	// �V�[���֌W����
private:
	// �V�[���̍쐬
	void CreateScene();

	// �V�[���̍폜
	void DeleteScene();

    //�L�[�{�[�h�̍X�V����
    void KeyboardUpdate();

    //�Q�[���p�b�h�̍X�V����
    void GamePadUpdate();
};
