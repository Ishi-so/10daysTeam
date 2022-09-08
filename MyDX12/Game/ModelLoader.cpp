#include "ModelLoader.h"
#include "../3D/Model.h"
using namespace XIIlib;

ModelLoader* XIIlib::ModelLoader::GetInstance()
{
	static ModelLoader instance;
	return &instance;
}

void XIIlib::ModelLoader::Initialize()
{
	models.resize(20);
}

void XIIlib::ModelLoader::Load(){
	SetModel(MODEL_BLOCK, "box_v000");
	SetModel(MODEL_ITEM, "box_v000");
	SetModel(MODEL_PLAYER, "sphere");
}

Model* XIIlib::ModelLoader::GetModel(const ModelNum& modelNum) const
{
	return models[static_cast<int>(modelNum)].get();
}

void XIIlib::ModelLoader::SetModel(const ModelNum& modelNum,const std::string& modelName)
{
	std::unique_ptr<Model> uModel(Model::CreateFromOBJ(modelName));
	models[static_cast<int>(modelNum)] = std::move(uModel);
}
