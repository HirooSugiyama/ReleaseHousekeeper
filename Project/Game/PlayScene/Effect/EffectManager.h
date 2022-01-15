/*
�G�t�F�N�g�}�l�[�W���[
�쐬���F2021/09/19
*/
#pragma once


//�񋓌^�̎g�p
#include"EffectType.h"


//�t�@�C���̏��Ԃ��܂Ƃ߂��񋓑�
enum class eEffectFileReading
{
	FILE_NAME,
	EFFECT_SPRITE_TIMER,
	EFFECT_HORIZONTAL_SIZE,
	EFFECT_SCALE_X,
	EFFECT_SCALE_Y,
};


//�O���錾
class EffectSpriteTexture;
class CameraBase;

//�G�t�F�N�g�}�l�[�W��
class EffectManager
{
public:
	//�C���X�^���X�̎擾
	static EffectManager* GetInstance()
	{
		static EffectManager instance;
		return &instance;
	}
private:

	//���ޓ�����̃G�t�F�N�g�̐�
	static const int EFFECT_NUM;


	//�ϐ�
	//�G�t�F�N�g�ێ��p�}�b�v
	std::unordered_map <eEffectType,std::vector<std::unique_ptr<EffectSpriteTexture>>>
		mpEffectDB;

	//�J�����̃|�C���^�ۑ��p�ϐ�
	CameraBase* mpCamera;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	EffectManager(EffectManager const & em) = delete;
	EffectManager operator=(EffectManager const& em) = delete;

	//�R���X�g���N�^
	EffectManager();
	//�f�X�g���N�^
	~EffectManager();



public:

	//������
	void Initialize(const wchar_t* filepath);

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//�I������
	void Finalize();

	//���\�[�X�̎擾
	EffectSpriteTexture* GetEffect(eEffectType const& key);

	//�J�����̃|�C���^��ۑ�����
	void SetCameraPointer(CameraBase* pCamera) { mpCamera = pCamera; }

	//�S�G�t�F�N�g�̉ғ��t���O
	bool ChackAllEffect();

private:

	//���\�[�X�f�[�^��ǂݍ���
	void LoadCSV(const wchar_t* filepath);

	//���ׂẴ��\�[�X�̍폜
	void DeleteAllData();

};