/*
�G�̃��f���̌������Ǘ�����񋓂����w�b�_�[�t�@�C��
�쐬���F2021/09/01
*/
#pragma once


//�ύX��̓G�̌�����\���񋓌^ 
enum class eAngleEnemy
{
	STRAIGHT,
	LEFT,
	RIGHT,
};

//�ς�����������ۑ�����񋓌^
enum class eChangeAfterAngle
{
	NONE,
	LEFT_ROTATION,
	RIGHT_ROTATION,
	STRAIGHT,
};

//�G�̕��s��Ԃ�\���񋓌^
enum class eEnemyWalkState
{
	GENERALLY,
	CHASING,
};
