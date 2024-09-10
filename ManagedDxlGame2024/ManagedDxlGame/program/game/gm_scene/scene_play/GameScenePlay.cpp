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

	//�N���[��������ƂȂ鋅�𐶐�����
	Shared<dxe::Mesh> base_mesh = nullptr;

	base_mesh = dxe::Mesh::CreateSphereMV(RADIUS);

	//���ꂼ��̋��̍��W
	tnl::Vector3 ball1_pos = { 150, 0, 0 };
	tnl::Vector3 ball2_pos = { -150, 0, 0 };
	tnl::Vector3 ball3_pos = { -50, 0, 300 };
	tnl::Vector3 ball4_pos = { 250, 0, 200 };
	tnl::Vector3 ball5_pos = { 250, 0, -200 };
	tnl::Vector3 ball6_pos = { 0, 0, 500 };

	//����
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

		//�������Ă��鋅�����삵�Ă��鋅����Ȃ���
		if (ball != controll_) {
			//���W���n�ʂ��Ⴂ��
			if (ball->position_.y < GROUND_POS_Y) {
				//���W��n�\��
				ball->position_.y = GROUND_POS_Y;
				//��������̋��ɂ���
				controll_ = ball;

			}
		}
	}

	//�Փ˔���
	//��{�[�����`�F�b�N
	auto link_it = link_ball_.begin();
	while (link_it != link_ball_.end()) {
		//�쐶�̃{�[�����`�F�b�N
		auto free_it = free_ball_.begin();
		while (free_it != free_ball_.end()) {

			tnl::Vector3 l = (*link_it)->position_;
			//�������
			tnl::Vector3 f = (*free_it)->position_;

			//�Փ˔���
			if (tnl::IsIntersectSphere(f, RADIUS, l, RADIUS)) {
				//l����f�̑��΍��W
				tnl::Vector3 lf = f - l;
				//f����l�̑��΍��W
				tnl::Vector3 fl = l - f;

				// ��{�[���̃����N�f�[�^�ɁA���������쐶�{�[���̃f�[�^��ǉ�
				(*link_it)->links_data_.emplace_back(std::make_shared<Links>((*free_it), lf, (*link_it)->rotation_));
				//(*link_it)->links_data_.push_back(std::make_shared<Links>((*free_it), lf, (*link_it)->rotation_));

				/*(*link_it)->links_.emplace_back(*free_it);
				(*link_it)->local_positions_.emplace_back(lf);
				(*link_it)->local_rotations_;*/

				// �쐶�{�[���̃����N�f�[�^�ɁA����������{�[���̃f�[�^��ǉ�
				//(*free_it)->links_data_.push_back(std::make_shared<Links>((*link_it), fl, (*free_it)->rotation_));
				(*free_it)->links_data_.emplace_back(std::make_shared<Links>((*link_it), fl, (*free_it)->rotation_));

				/*(*free_it)->links_.emplace_back(*link_it);
				(*free_it)->local_positions_.emplace_back(fl);
				(*free_it)->local_rotations_;*/

				//��{�[���̃��X�g�ɓ��������쐶�{�[����ǉ�
				link_ball_.emplace_back((*free_it));

				//�쐶�{�[���̃��X�g���瓖�������{�[�����폜
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