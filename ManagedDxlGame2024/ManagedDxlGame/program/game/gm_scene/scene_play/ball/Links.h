#pragma once

class Ball;

class Links{
public:
	Links(std::shared_ptr<Ball> ball, tnl::Vector3 pos, tnl::Quaternion rot);
	~Links();

	// �������g
	std::weak_ptr<Ball> links_ball_;
	// �����t�����u�Ԃ̑��΍��W���L��
	tnl::Vector3 local_positions_;
	// �����t�����u�Ԃ̎p�����L��
	tnl::Quaternion local_rotations_;

	//�����t���Ă���{�[���ւ̏���
	void UpDataLink(tnl::Quaternion parent_rotation,std::shared_ptr<Ball> parent);
};