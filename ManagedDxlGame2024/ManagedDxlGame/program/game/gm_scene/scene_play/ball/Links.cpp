#include "../dxlib_ext/dxlib_ext.h"
#include "Links.h"
#include "Ball.h"

Links::Links(std::shared_ptr<Ball> ball, tnl::Vector3 pos, tnl::Quaternion rot)
{
	links_ball_ = ball;
	local_positions_ = pos;
	local_rotations_ = rot;
}

Links::~Links()
{

}

void Links::UpDataLink(tnl::Quaternion parent_rotation, std::shared_ptr<Ball> parent)
{
	//null�`�F�b�N������悤��
	std::shared_ptr<Ball> ball = links_ball_.lock();

	if (ball != nullptr) {

		//���̃{�[������]������
		ball->rotation_ *= parent_rotation;
		//���Ύp��
		tnl::Quaternion q = tnl::Quaternion::Subtract(local_rotations_, parent->rotation_);
		//���W�̍X�V
		ball->position_ = tnl::Vector3::TransformCoord(local_positions_, q);
		ball->position_ += parent->position_;

		for (auto links : ball->links_data_) {

			std::shared_ptr<Ball> link_ball = links->links_ball_.lock();

			if (link_ball == parent) {
				continue;
			}
			else {
				links->UpDataLink(parent_rotation, ball);
			}
		}
	}
	else {

	}
}

