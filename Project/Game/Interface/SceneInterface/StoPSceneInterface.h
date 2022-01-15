/*
�X�e�[�W�Z���N�g��ʂ���v���C�V�[���֏���n�����߂̃C���^�[�t�F�[�X
*/
#pragma once

class StoPSceneInterface
{
private:
	//�������g
	static StoPSceneInterface* sStoPIF;


	//�ǂݍ��ރX�e�[�WCSV�t�@�C��
	std::string mCSVFileName;

	//�X�e�[�W�ԍ�
	std::string mStageNumber;	//��XString�^�Ŏg�p���邽�߂��炩����String�^�ŏ���

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	StoPSceneInterface(const StoPSceneInterface& dr) = delete;
	StoPSceneInterface operator=(const StoPSceneInterface& dr) = delete;

	//�R���X�g���N�^
	StoPSceneInterface();
	//�f�X�g���N�^
	~StoPSceneInterface()=default;
public:
	//���g�̃C���X�^���X
	static StoPSceneInterface& GetStoPIFInstance();


	//�e��A�N�Z�T
	//CSV�t�@�C��
	void SetStageCSV(std::string const& filepath) { mCSVFileName = filepath; }
	std::string GetStageCSV() const { return mCSVFileName; }

	//�X�e�[�W�ԍ�
	void SetStageNumber(std::string const& number) { mStageNumber = number; }
	std::string GetStageNumber()const { return mStageNumber; }
	const
	//�폜����
	void Destroy()
	{
		if (sStoPIF != nullptr) {
			delete sStoPIF;
			sStoPIF = nullptr;
		}
	}
};
