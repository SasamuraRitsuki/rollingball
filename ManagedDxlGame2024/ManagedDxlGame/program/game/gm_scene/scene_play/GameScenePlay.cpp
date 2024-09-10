#include "../../../dxlib_ext/dxlib_ext.h"
#include "GameScenePlay.h"
#include "../../gm_mgr/GameManager.h"
#include "ball/Ball.h"
#include "ball/Links.h"

ScenePlay::ScenePlay(bool hard_mode) {
	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f)); 
	SetBackgroundColor(50, 50, 50);

	camera_ = std::make_shared<dxe::Camera>(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);

	camera_->pos_ = FIRST_CAMERA_POS;

	//クローンを作る基準となる球を生成する
	Shared<dxe::Mesh> base_mesh = nullptr;

	base_mesh = dxe::Mesh::CreateSphereMV(RADIUS);

	//それぞれの球の座標
	tnl::Vector3 ball1_pos = { 150, 0, 0 };
	tnl::Vector3 ball2_pos = { -150, 0, 0 };
	tnl::Vector3 ball3_pos = { -50, 0, 300 };
	tnl::Vector3 ball4_pos = { 250, 0, 200 };
	tnl::Vector3 ball5_pos = { 250, 0, -200 };
	tnl::Vector3 ball6_pos = { 0, 0, 500 };

	//生成
	controll_ = std::make_shared<Ball>(ball1_pos, base_mesh);
	link_ball_.emplace_back(controll_);

	free_ball_.emplace_back(std::make_shared<Ball>(ball2_pos, base_mesh));
	free_ball_.emplace_back(std::make_shared<Ball>(ball3_pos, base_mesh));
	free_ball_.emplace_back(std::make_shared<Ball>(ball4_pos, base_mesh));
	free_ball_.emplace_back(std::make_shared<Ball>(ball5_pos, base_mesh));
	free_ball_.emplace_back(std::make_shared<Ball>(ball6_pos, base_mesh));

	SetFontSize(20);
}

ScenePlay::~ScenePlay() {

}

void ScenePlay::update(float delta_time) {

	//-------------------------------------------------------------------------------
	//
	// update
	//
	//-------------------------------------------------------------------------------

	controll_->move();

	for (auto ball : link_ball_) {

		//くっついている球が操作している球じゃない時
		if (ball != controll_) {
			//座標が地面より低い時
			if (ball->position_.y < GROUND_POS_Y) {
				//座標を地表に
				ball->position_.y = GROUND_POS_Y;
				//操作をこの球にする
				controll_ = ball;

			}
		}
	}

	//衝突判定
	//塊ボールをチェック
	auto link_it = link_ball_.begin();
	while (link_it != link_ball_.end()) {
		//野生のボールをチェック
		auto free_it = free_ball_.begin();
		while (free_it != free_ball_.end()) {

			tnl::Vector3 l = (*link_it)->position_;
			//ここ問題
			tnl::Vector3 f = (*free_it)->position_;

			//衝突判定
			if (tnl::IsIntersectSphere(f, RADIUS, l, RADIUS)) {
				//lからfの相対座標
				tnl::Vector3 lf = f - l;
				//fからlの相対座標
				tnl::Vector3 fl = l - f;

				// 塊ボールのリンクデータに、当たった野生ボールのデータを追加
				(*link_it)->links_data_.emplace_back(std::make_shared<Links>((*free_it), lf, (*link_it)->rotation_));
				//(*link_it)->links_data_.push_back(std::make_shared<Links>((*free_it), lf, (*link_it)->rotation_));

				/*(*link_it)->links_.emplace_back(*free_it);
				(*link_it)->local_positions_.emplace_back(lf);
				(*link_it)->local_rotations_;*/

				// 野生ボールのリンクデータに、当たった塊ボールのデータを追加
				//(*free_it)->links_data_.push_back(std::make_shared<Links>((*link_it), fl, (*free_it)->rotation_));
				(*free_it)->links_data_.emplace_back(std::make_shared<Links>((*link_it), fl, (*free_it)->rotation_));

				/*(*free_it)->links_.emplace_back(*link_it);
				(*free_it)->local_positions_.emplace_back(fl);
				(*free_it)->local_rotations_;*/

				//塊ボールのリストに当たった野生ボールを追加
				link_ball_.emplace_back((*free_it));

				//野生ボールのリストから当たったボールを削除
				free_it = free_ball_.erase(free_it);
				continue;
			}
			free_it++;

		}
		link_it++;
	}


	camera_->update();

}

void ScenePlay::draw() {

	DrawGridGround(camera_, 50, 20);
	int a = 0;
	for (auto ball : link_ball_) {

		ball->render(camera_);
		auto test = ball->position_;
		DrawStringEx(0, a, -1, "x = %.1f,y = %.1f,z = %.1f,", test.x, test.y, test.z);
		//DrawStringEx(0, 100, -1, "l length = %d", link_ball_.size());
		a += 30;
	}

	for (auto ball : free_ball_) {
		ball->render(camera_);
		//DrawStringEx(0, 200, -1, "f length = %d", free_ball_.size());
	}
}