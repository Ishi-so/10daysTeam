#pragma once
#include <vector>
#include <memory>
class Object3D;

namespace XIIlib {

	class ObjectContainer {
	private:
		
		// オブジェクトを管理する変数
		std::vector<std::unique_ptr<Object3D>> container;
	private:
		ObjectContainer() = default;
		~ObjectContainer() = default;

		//ノームソート
		void NomeSort();
	public:// 静的メンバ関数
		static ObjectContainer* GetInstance();
	public:
		ObjectContainer(const ObjectContainer& obj) = delete;
		ObjectContainer& operator = (const ObjectContainer& obj) = delete;
		void Draw();

		void SetObject3D(std::unique_ptr<Object3D> unique);
	};
}