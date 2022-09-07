#include "ObjectContainer.h"
#include "Object3D.h"

void XIIlib::ObjectContainer::NomeSort()
{
	int i = 1;
	while (i < (int)container.size()) {
		// 調べているアルファ値の方が大きければそのまま進む
		if (container[i - 1].get()->alpha >= container[i].get()->alpha)++i;
		else {// そうでなければ入れ替える
			std::swap(container[i - 1], container[i]);
			if (i > 1)--i;
		}
	}
}

XIIlib::ObjectContainer* XIIlib::ObjectContainer::GetInstance()
{
	static XIIlib::ObjectContainer instance;
	return &instance;
}

void XIIlib::ObjectContainer::Draw()
{
	for (auto& obj : container) {
		obj.get()->Draw();
	}
}

void XIIlib::ObjectContainer::SetObject3D(std::unique_ptr<Object3D> unique)
{
	container.push_back(std::move(unique));
}
