/*
�����������\�����s���N���X�̊��N���X
�쐬���F2021/10/22
*/

#pragma once


class NumberBase
{
private:

	//�����x�����l
	static const float INIT_ALPHA;
	//�����̐��̍ő吔
	static const int MAX_NUMTYPE_NUM;


	//�����x�Ǘ��ϐ�
	float mTextureAlpha;

	//�摜�L�[
	std::string mTextureKey;


protected:
	//�R���X�g���N�^
	NumberBase();

	//�f�X�g���N�^
	virtual ~NumberBase();

public:

	//�X�V����
	virtual void Update() {}

	//�`�揈��
	virtual void Draw() = 0;

	//�摜�L�[�̃A�N�Z�T
	void SetTextureKey(std::string key) { mTextureKey = key; }
	std::string GetTextureKey() { return mTextureKey; }


protected:

	//�擾������������K�v�Ȑ�����I�яo��
	std::vector<int> ChooseNum(int num);

	//�A�N�Z�T
	//�����x�Ǘ��ϐ�
	float GetTextureAlpha() { return mTextureAlpha; }
	void SetTextureAlpha(float alpha) { mTextureAlpha = alpha; }

	float GetInitAlpha() { return INIT_ALPHA; }
	int GetMaxNumTypeNum() { return MAX_NUMTYPE_NUM; }

};
