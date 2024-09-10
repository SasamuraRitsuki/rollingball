#include "../dxlib_ext/dxlib_ext.h"
#include "Ball.h"
#include "Links.h"

Ball::Ball(tnl::Vector3 pos, Shared<dxe::Mesh> mesh) {

	mesh_ = mesh->createClone();
	mesh_->setTexture(dxe::Texture::CreateFromFile("graphics/test.jpg"));
	//mesh_->setPosition(pos);
	position_ = pos;
}

Ball::~Ball() {

}

void Ball::move(){
	tnl::Vector3 input_v[2];
	tnl::Vector3 input_axis[2];
	int input_count = 0;

	tnl::Input::RunIndexKeyDown(
		[&](uint32_t index) {
			//3“ü—ÍˆÈã‚ðŽó‚¯•t‚¯‚È‚¢
			if (input_count >= 2) {
				return;
			}

			tnl::Vector3 v[4] = {
				tnl::Vector3::left,
				tnl::Vector3::right,
				tnl::Vector3::forward,
				tnl::Vector3::back
			};
			tnl::Vector3 axis[4] = {
				{0,0,1},
				{0,0,-1},
				{1,0,0},
				{-1,0,0}
			};
			//ˆÚ“®‚µ‚½‚¢•ûŒü‚Ì•Û‘¶
			input_v[input_count] = v[index];
			input_axis[input_count] = axis[index];
			input_count++;

			/*for (int i = 0; i < 4; i++) {
				DrawStringEx(100, 100 + i * 50, -1, "x = %.0f, y = %.0f, z = %.0f", v[i].x, v[i].y, v[i].z);
			}*/

		}, eKeys::KB_A, eKeys::KB_D, eKeys::KB_W, eKeys::KB_S);

	//“]‚ª‚·—Ê
	tnl::Quaternion qtn;

	if (input_count == 1) {
		//ˆÚ“®
		position_ += input_v[0] * 3.0f;
		//‰ñ“]
		qtn = tnl::Quaternion::RotationAxis(input_axis[0], tnl::ToRadian(rotation_speed));
		rotation_ *= qtn;
	}
	if (input_count >= 2) {
		//2•ûŒü‚É“]‚ª‚éi‚È‚È‚ß‚Í–ñ0.7”{‚Ù‚Çj
		position_ += input_v[0] * 3.0f * 0.7f;
		position_ += input_v[1] * 3.0f * 0.7f;
		//‰ñ“]
		qtn = tnl::Quaternion::RotationAxis(input_axis[0], tnl::ToRadian(rotation_speed * 0.7f)) * 
			tnl::Quaternion::RotationAxis(input_axis[1], tnl::ToRadian(rotation_speed * 0.7f));
		rotation_ *= qtn;
	}

	for (auto links : links_data_) {
		//‚Ç‚Ì‚­‚ç‚¢‰ñ“]‚·‚é‚© qtn
		//‘—‚ée‚Ìƒf[ƒ^ this
		links->UpDataLink( qtn, shared_from_this() );
	}
}

//void Ball::UpDataLink(tnl::Quaternion parent_rotation, std::shared_ptr<Ball> parent)
//{
//
//}

