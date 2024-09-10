#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../gm_mgr/GameManager.h"
#include "GameSceneTitle.h"
#include "../scene_play/GameScenePlay.h"

SceneTitle::SceneTitle() {
	SetBackgroundColor(32, 32, 32);
	SetFontSize(20);
}

SceneTitle::~SceneTitle() {

}

void SceneTitle::update(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//ƒQ[ƒ€‰æ–Ê‚É‘JˆÚ
		auto mgr = GameManager::GetInstance();
		mgr->changeScene(std::make_shared<ScenePlay>(false));
	}
}

void SceneTitle::draw() {
	DrawStringEx((DXE_WINDOW_WIDTH / 2) - (50 * 3),DXE_WINDOW_HEIGHT / 2 - 50,-1,"ƒ^ƒCƒgƒ‹‰æ–Ê");
	
	DrawStringEx(DXE_WINDOW_WIDTH / 2 - 135,DXE_WINDOW_HEIGHT / 2 + 50,-1,"Press Enter");
}