/*
�^�C�g���V�[��
*/
#pragma once

#include "../IScene.h"
#include "Game/GameMain.h"

//����
#include"Game/Common/Cloud.h"

class TitleScene : public IScene
{
private:

	//���S�̍��W
	static const DirectX::SimpleMath::Vector2 TITLE_LOGO_POSITION;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mpLogo;

	std::unique_ptr<Cloud> mpCloud;

	//���yID
	int mBGMID;

public:

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

	// ������
	void Initialize() override;

	// �X�V
	eGameScene Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

private:
	//BGM�𗬂�
	void PlayBGM()override;

	//BGM���~�߂�
	void StopBGM()override;
};