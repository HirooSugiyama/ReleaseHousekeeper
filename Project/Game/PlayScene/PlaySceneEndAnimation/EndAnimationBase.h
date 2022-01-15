/*
�I�����A�j���[�V�����������N���X

�쐬���F2021/11/10
*/
#pragma once

//�񋓌^�̎g�p
#include"EndAnimationState.h"

//����
#include"Libraries/MyLibraries/Camera.h"

class EndAnimationBase 
{
private:

	std::unique_ptr<Camera> mpCamera;

protected:
	//�R���X�g���N�^
	EndAnimationBase() 
		:mpCamera(nullptr)
	{
		mpCamera = std::make_unique<Camera>(); 
	}
	//�f�X�g���N�^
	virtual ~EndAnimationBase() = default;

public:

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual bool Update() = 0;
	//�`��
	virtual void Draw() = 0;

protected:
	Camera* GetCamera() { return mpCamera.get(); }

};
