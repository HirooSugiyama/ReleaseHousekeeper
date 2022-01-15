/*
�n�ʂ̏�ɂ���I�u�W�F�N�g�̊��N���X
�쐬���F2021/08/19
*/
#pragma once



class IGroundObject
{

protected:
	//�R���X�g���N�^
	IGroundObject() = default;
	//�f�X�g���N�^
	virtual ~IGroundObject() = default;
public:
	//������
	virtual void Initialize() = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;
};