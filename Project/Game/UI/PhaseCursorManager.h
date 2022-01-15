/*
�t�F�[�Y���n�܂�^�C�~���O�������J�[�\���̕`����s���N���X
*/
#pragma once

//�O���錾
#include"PhaseCursor.h"

class PhaseCursorManager
{
private:

	//�擾���W�̂��炷��
	static const float PHASECURSOR_SHIFT_POSITION;

	//�ϐ�
	std::vector<std::unique_ptr<PhaseCursor>> mpPhaseCursor;

public:

	//�R���X�g���N�^
	PhaseCursorManager();
	//�f�X�g���N�^
	~PhaseCursorManager();
	//����������
	void Initialize(int const& phasemaxnum);
	//�`�揈��
	void Draw();

	//�`�悷����W�����߂�
	void SetDrawPosition(DirectX::SimpleMath::Vector2 const& startpos,float const& movepos);

};
