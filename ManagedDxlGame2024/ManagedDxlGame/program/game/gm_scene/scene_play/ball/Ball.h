#pragma once

class Links;

class Ball : public std::enable_shared_from_this<Ball> {
public:
	Ball(tnl::Vector3 pos, Shared<dxe::Mesh> mesh);
	~Ball();

	//���W
	tnl::Vector3 position_;
	//��]��
	tnl::Quaternion rotation_;
	//�����t���Ă���{�[���̃f�[�^�̃��X�g
	std::list<std::shared_ptr<Links>> links_data_;

	Shared<dxe::Mesh> mesh_ = nullptr;

	// �����������ɂ��ꂼ��ʂ� id ��U�肽���̂�
	//static int id_count_;

	// �ċA�p�̃`�F�b�N�t���O
	bool is_link_check_;

	//int id_ = 0;
	//���X�s�[�h
	const float rotation_speed = 4.0f;

	//�R���g���[������������
	void move();
	////�����t���Ă���{�[���ւ̏���
	//void UpDataLink(std::shared_ptr<Ball> parent, tnl::Quaternion parent_rotation,
	//	tnl::Quaternion local_rotation, tnl::Vector3 local_position);

	void render(Shared<dxe::Camera> camera) {
		mesh_->setPosition(position_);
		mesh_->setRotation(rotation_);
		mesh_->render(camera);
	}
};