#pragma once
#include "../../library/tnl_sequence.h"

class SceneBase;

class GameManager {
public:
	//�Q�[���}�l�[�W���[�̃A�h���X��Ԃ�
	static GameManager* GetInstance(std::shared_ptr<SceneBase> start_scene = nullptr);
	//�A�h���X���폜
	static void Destroy();

	void changeScene(std::shared_ptr<SceneBase> next_scene);

	std::shared_ptr<SceneBase> getSceneInstance() { return now_scene_; }

	
	//bool getClicked() { return clicked_; }
	

	void update(float delta_time);

	bool clicked_ = false;

private:
	GameManager(std::shared_ptr<SceneBase> start_scene);

	~GameManager();

	std::shared_ptr<SceneBase> now_scene_ = nullptr;
	std::shared_ptr<SceneBase> next_scene_ = nullptr;

};