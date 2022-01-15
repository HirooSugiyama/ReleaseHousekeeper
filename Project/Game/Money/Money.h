/*
�������Ǘ��t�@�C��
*/
#pragma once



class Money final
{
private:

	////���g
	static Money* sMoney;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	Money( Money const& money) = delete;
	Money operator=( Money const& money) = delete;

	//�t�@�C����
	std::string mFilepath;
	//�������z
	int mPossessionMoney;

	//�R���X�g���N�^
	Money();

	//�f�X�g���N�^
	~Money() = default;

public:

	//���g�̃C���X�^���X
	static Money& GetMoneyInstance();

	//�t�@�C�����̐ݒ�
	void LoadFileSet(std::string filepath);

	//���z������������
	void ReduceMoney(int const& moneynum) { mPossessionMoney -= moneynum; }
	//���z�̏㏑��
	void SetMoney(int const& moneynum) { mPossessionMoney = moneynum; }

	//���z���擾
	int GetMoney()const { return mPossessionMoney; }

	//�폜����
	void Destroy();

private:

	//���z�̏�����
	void MoneyInit();

};
