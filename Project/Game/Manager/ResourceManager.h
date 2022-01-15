/*
���\�[�X�}�l�[�W���[
���\�[�X�S�ʂ��Ǘ�����N���X���C�u����
(����A�I�[�f�B�I�͕ʃ��C�u�������g�p���邽�ߓƗ������Ă��܂��B)
*/
#pragma once



//�ǂݍ��ݕ���
enum class eLoadScene
{
	NONE = -1,
	TITLE = 1,
	MODE_SELECT,
	STAGE_SELECT,
	PLAY,
	WIN,
	LOSE,
};

//�t�@�C���̏��Ԃ��܂Ƃ߂��񋓑�
enum class eFileReading
{
	READ_TIMING,
	IDENTIFIER,
	FILE_NAME,
	FILE_MAPKEY,
};

//���\�[�X�}�l�[�W��
class ResourceManager
{
public:
	//�C���X�^���X�̎擾
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}
private:

	//�ϐ�
	//�e�N�X�`���ێ��p�}�b�v
	std::unordered_map<std::string, Microsoft::WRL::ComPtr
					<ID3D11ShaderResourceView>> mpTextureDB;

	//CMO���f���ێ��p�}�b�v
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>>
		mpCmoModelDB;

	//�ǂݍ��݃^�C�~���O�ۑ��p������ϐ�
	eLoadScene mReadTiming;


	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	ResourceManager(const ResourceManager& rm) = delete;
	ResourceManager operator=(const ResourceManager& rm) = delete;


	//�R���X�g���N�^
	ResourceManager();
	//�f�X�g���N�^
	~ResourceManager();


public:

	//������
	void Initialize(const wchar_t* filepath);

	//�V�[���̎w��
	void SetuseScene(eLoadScene const& scene) { mReadTiming = scene; }

	//�I������
	void Finalize();

	//���\�[�X�̎擾
	ID3D11ShaderResourceView* GetTexture(std::string const& key);
	DirectX::Model* GetCmoModel(std::string const& key);

private:
	//���\�[�X�̓o�^
	void RegisterTexture(const wchar_t* path,  std::string const& key);
	void GetCmoModel(const wchar_t* path,  std::string const& key);

	//���\�[�X�f�[�^��ǂݍ���
	void LoadCSV(const wchar_t* filepath);

	//���ׂẴ��\�[�X�̍폜
	void DeleteAllData();
};