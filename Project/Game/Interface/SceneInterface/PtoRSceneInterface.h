/*
�v���C�V�[�����烊�U���g�V�[���֏���n�����߂̃C���^�[�t�F�[�X
*/
#pragma once

class PtoRSceneInterface
{
private:
	//�������g
	static PtoRSceneInterface* sPtoRIF;

	//�X�R�A
	int mScoreNum;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	PtoRSceneInterface( PtoRSceneInterface const& pr) = delete;
	PtoRSceneInterface operator=( PtoRSceneInterface const& pr) = delete;


	//�R���X�g���N�^
	PtoRSceneInterface();
	//�f�X�g���N�^
	~PtoRSceneInterface()=default;
public:
	//���g�̃C���X�^���X
	static PtoRSceneInterface& GetPtoRIFInstance();



	//�e��A�N�Z�T
	//�X�R�A
	void SetScoreNum(int score) { mScoreNum = score; }
	int GetScoreNum() { return mScoreNum; }


	//�폜����
	void Destroy()
	{
		if (sPtoRIF != nullptr) 
		{
			delete sPtoRIF;
			sPtoRIF = nullptr;
		}
	}
};
