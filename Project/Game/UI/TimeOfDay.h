/*
�����t�F�[�Y(��)�Ɩh�q�t�F�[�Y(��)��UI���Ǘ�����N���X
*/
#pragma once

//����
#include"../Common/ObjectTexture.h"

//�O���錾
class Timer;

class TimeOfDay
{
private:

	//�萔
	//�i�ދ��� 
	static const float UI_TOD_ICON_DISTANCE;

	//�Q�[�W�̊g�嗦
	static const DirectX::SimpleMath::Vector2 UI_TOD_GAUGE_SCALE;

	//�A�C�R���̊g�嗦
	static const DirectX::SimpleMath::Vector2 UI_TOD_ICON_SCALE;

	//�Q�[�W�̍��W
	static const DirectX::SimpleMath::Vector2 UI_TOD_GAUGE_POSITION;

	//�A�C�R���̏������W
	static const DirectX::SimpleMath::Vector2 UI_TOD_ICON_POSITION;

	//�t���[�����Z
	static const float CAST_TO_FRAME_TO_SECOND;

	//�ϐ�
	//�Q�[�W�̉摜
	std::unique_ptr<ObjectTexture> mpTODGauge;
	//�A�C�R���̉摜
	std::unique_ptr<ObjectTexture> mpTODIcon;

	//�Q�[���̍ő厞��
	int mMaxGameTime;
	
	//�ۑ��p�ϐ�
	Timer* mpTimer;

	//�A�C�R���̐i�ޑ��x
	float mIconMoveVelocity;


public:
	//�R���X�g���N�^
	TimeOfDay();
	//�f�X�g���N�^
	~TimeOfDay();

	//������
	void Initialize(Timer* pTimer,int const& maxPhaseNum);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�A�C�R���̊J�n�_���擾
	DirectX::SimpleMath::Vector2 GetIconStartPosition()const { return UI_TOD_ICON_POSITION; }
	//�A�C�R���̍ŏI�_���擾
	float GetIconDistancePosition() const { return UI_TOD_ICON_DISTANCE; }

private:

	//�摜�̐ݒ�
	void SetTexture();
	//���W�̐ݒ�
	void SetPosition();
	//�g�嗦�̐ݒ�
	void SetScale();

	//�A�C�R�����i�ރX�s�[�h���Z�o
	float CalculationIconVelocity();


};
