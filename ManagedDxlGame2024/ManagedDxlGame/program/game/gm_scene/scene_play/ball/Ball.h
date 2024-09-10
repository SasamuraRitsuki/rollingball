#pragma once

class Links;

class Ball : public std::enable_shared_from_this<Ball> {
public:
	Ball(tnl::Vector3 pos, Shared<dxe::Mesh> mesh);
	~Ball();

	//座標
	tnl::Vector3 position_;
	//回転量
	tnl::Quaternion rotation_;
	//くっ付いているボールのデータのリスト
	std::list<std::shared_ptr<Links>> links_data_;

	Shared<dxe::Mesh> mesh_ = nullptr;

	// 生成した球にそれぞれ個別の id を振りたいので
	//static int id_count_;

	// 再帰用のチェックフラグ
	bool is_link_check_;

	//int id_ = 0;
	//回るスピード
	const float rotation_speed = 4.0f;

	//コントロールが動く処理
	void move();
	////くっ付いているボールへの処理
	//void UpDataLink(std::shared_ptr<Ball> parent, tnl::Quaternion parent_rotation,
	//	tnl::Quaternion local_rotation, tnl::Vector3 local_position);

	void render(Shared<dxe::Camera> camera) {
		mesh_->setPosition(position_);
		mesh_->setRotation(rotation_);
		mesh_->render(camera);
	}
};