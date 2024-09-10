#pragma once
#include "../../gm_mgr/SceneBase.h"

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle();

	void update(float delta_time) override;
	void draw() override;
private:

};