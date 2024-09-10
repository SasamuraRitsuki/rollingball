#pragma once

class Ball;

class Links{
public:
	Links(std::shared_ptr<Ball> ball, tnl::Vector3 pos, tnl::Quaternion rot);
	~Links();

	// 自分自身
	std::weak_ptr<Ball> links_ball_;
	// くっ付いた瞬間の相対座標を記憶
	tnl::Vector3 local_positions_;
	// くっ付いた瞬間の姿勢を記憶
	tnl::Quaternion local_rotations_;

	//くっ付いているボールへの処理
	void UpDataLink(tnl::Quaternion parent_rotation,std::shared_ptr<Ball> parent);
};