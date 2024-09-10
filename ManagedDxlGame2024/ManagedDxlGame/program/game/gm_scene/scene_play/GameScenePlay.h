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
	//カメラのポインタ
	Shared<dxe::Camera> camera_ = nullptr;

	//カメラの初期値
	const tnl::Vector3 FIRST_CAMERA_POS = { 0, 300, -500 };
	//半径
	const float RADIUS = 50;
	//地面の高さ
	const float GROUND_POS_Y = 0;
	//操作出来るボール
	Shared<Ball> controll_ = nullptr;

	//塊ボール
	std::list<std::shared_ptr<Ball>> link_ball_;
	//野生のボール
	std::list<std::shared_ptr<Ball>> free_ball_;
};