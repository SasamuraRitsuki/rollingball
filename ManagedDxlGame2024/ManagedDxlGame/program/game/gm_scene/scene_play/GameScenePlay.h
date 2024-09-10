#pragma once
#include "../../gm_mgr/SceneBase.h"

class Ball;

class ScenePlay : public SceneBase {
public:
	ScenePlay(bool hard_mode);
	~ScenePlay();

	void update(float delta_time) override;
	void draw() override;

private:
	//�J�����̃|�C���^
	Shared<dxe::Camera> camera_ = nullptr;

	//�J�����̏����l
	const tnl::Vector3 FIRST_CAMERA_POS = { 0, 300, -500 };
	//���a
	const float RADIUS = 50;
	//�n�ʂ̍���
	const float GROUND_POS_Y = 0;
	//����o����{�[��
	Shared<Ball> controll_ = nullptr;

	//��{�[��
	std::list<std::shared_ptr<Ball>> link_ball_;
	//�쐶�̃{�[��
	std::list<std::shared_ptr<Ball>> free_ball_;
};