#pragma once
#include <vector>
#include <memory>
class Object3D;

namespace XIIlib {

	class ObjectContainer {
	private:
		
		// �I�u�W�F�N�g���Ǘ�����ϐ�
		std::vector<std::unique_ptr<Object3D>> container;
	private:
		ObjectContainer() = default;
		~ObjectContainer() = default;

		//�m�[���\�[�g
		void NomeSort();
	public:// �ÓI�����o�֐�
		static ObjectContainer* GetInstance();
	public:
		ObjectContainer(const ObjectContainer& obj) = delete;
		ObjectContainer& operator = (const ObjectContainer& obj) = delete;
		void Draw();

		void SetObject3D(std::unique_ptr<Object3D> unique);
	};
}