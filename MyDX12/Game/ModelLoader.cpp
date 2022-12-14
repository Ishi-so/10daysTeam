#include "ModelLoader.h"
#include "../3D/Model.h"

ModelLoader* ModelLoader::GetInstance()
{
	static ModelLoader instance;
	return &instance;
}

void ModelLoader::Initialize()
{
	models.resize(20);
}

void ModelLoader::Load(){
	SetModel(MODEL_BLOCK, "block");
	SetModel(MODEL_ITEM, "ICO");
	SetModel(MODEL_PLAYER, "rice_ball");
	SetModel(MODEL_GOAL, "box_v000");
}

Model* ModelLoader::GetModel(const ModelNum& modelNum) const
{
	return models[static_cast<int>(modelNum)].get();
}

void ModelLoader::SetModel(const ModelNum& modelNum,const std::string& modelName)
{
	std::unique_ptr<Model> uModel(Model::CreateFromOBJ(modelName));
	models[static_cast<int>(modelNum)] = std::move(uModel);
}
