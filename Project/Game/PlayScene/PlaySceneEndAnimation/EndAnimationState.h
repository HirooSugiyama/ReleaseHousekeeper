/*
�I�����A�j���[�V���������Ŏg�p����񋓌^

�쐬���F2021/11/10
*/
#pragma once




//�g�p����A�j���[�V����
enum class eUseEndAnim
{
	NONE,		//�Ȃ�
	LOSE,		//����
	WIN_TIME,	//���Ԍo�߂̏���
	WIN_EXTERM,	//�G�r�ł̏���
};



//�A�j���[�V�����̒i�K

//�����A�j���[�V����
enum class eLoseAnimStep
{
	NONE,				//�Ȃ�
	PREPARATION,		//����
	ROTATION_ANGLE,		//�J������]
	FIRST_EXPLOSION,	//1���ڔ���
	SECOND_EXPLOSION,	//2���ڔ���
	THIRD_EXPLOSION,	//3���ڔ���
	FORTH_EXPLOSION,	//4���ڔ���
	LOSE_TEXTURE,		//�����摜�`��
	END,				//�I��
};



//�����A�j���[�V����
enum class eWinAnimStep
{
	NONE,			//�Ȃ�
	PREPARATION,	//����
	SUNRISE,		//���̏o
	ROTATION_ANGLE1,//�J������]
	EXTERM_ENEMY,	//�G�S��
	END,			//�I��
};					