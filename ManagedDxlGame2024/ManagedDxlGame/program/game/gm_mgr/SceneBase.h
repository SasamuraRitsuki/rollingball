#pragma once

class SceneBase {
public:
	virtual void update(float delta_time) {};
	virtual void draw() {};

protected:
	//bgm�̉��y�p�X
	int bgm_snd_;
};