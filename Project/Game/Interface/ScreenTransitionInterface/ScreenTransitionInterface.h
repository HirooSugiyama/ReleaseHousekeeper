
/*
��ʑJ�ڊǗ��N���X(Singleton)

�쐬���F2021/12/28
*/
#pragma once
#include <Libraries/MyLibraries/Wipe.h>
#include <Libraries/MyLibraries/Fade.h>

#include"../../Common/ObjectTexture.h"

class ScreenTransitionInterface
{
private:
	//�������g
	static ScreenTransitionInterface* sTransitionInterface;

	//���C�v
	std::unique_ptr<Wipe> mpWipe;
	//�g�p�t���O
	bool mWipeUseFlag;

	//�t�F�[�h
	std::unique_ptr<Fade> mpFade;
	//�g�p�t���O
	bool mFadeUseFlag;


	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	ScreenTransitionInterface(ScreenTransitionInterface const& sti) = delete;
	ScreenTransitionInterface operator=(ScreenTransitionInterface const& sti) = delete;

	//�R���X�g���N�^
	ScreenTransitionInterface();
	//�f�X�g���N�^
	~ScreenTransitionInterface() = default;

public:
	//��������
	static ScreenTransitionInterface& GetScreenTransitionInstance();

	//�폜����
	void Destroy() const;

	//���C�v�̎擾
	Wipe* GetWipe() { return mpWipe.get(); }	
	//�g�p�t���O�̃A�N�Z�T
	bool GetWipeUseFlag() { return mWipeUseFlag; }
	void SetWipeUseFlag(bool flag) { mWipeUseFlag = flag; }

	//�t�F�[�h�̎擾
	Fade* GetFade() { return mpFade.get(); }
	//�g�p�t���O�̃A�N�Z�T
	bool GetFadeUseFlag() { return mFadeUseFlag; }
	void SetFadeUseFlag(bool flag) { mFadeUseFlag = flag; }

};
