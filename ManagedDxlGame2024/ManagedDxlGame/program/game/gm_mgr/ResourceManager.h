#pragma once

class ResourceManager {
public:
	//�摜�f�[�^�̓ǂݍ���
	int loadGraph(const std::string& file_path);
	//���y�f�[�^�̓ǂݍ���
	int loadSound(const std::string& file_path);

	static ResourceManager* GetInstance();
	static void Destroy();

private:
	ResourceManager();
	~ResourceManager();

	//bgm��se�̉��ʂ�80%�ɗ}����
	const int SOUND_VOL = 8000;

	//�摜�t�@�C��
	std::unordered_map<std::string, int> graphics_map_;
	//���y�t�@�C��
	std::unordered_map<std::string, int> sounds_map_;
};