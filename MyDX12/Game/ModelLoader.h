#pragma once
#include <string>
#include <vector>
#include <memory>

class Model;

enum ModelNum {
	MODEL_BLOCK = 0,
	MODEL_ITEM,
	MODEL_PLAYER,
	MODEL_GOAL,
};

class ModelLoader
{
public:
	static ModelLoader* GetInstance();

	void Initialize();
	void Load();

	Model* GetModel(const ModelNum& modelNum)const;
private:
	ModelLoader() = default;
	ModelLoader(const ModelLoader&) = delete;
	~ModelLoader() = default;
	ModelLoader& operator=(const ModelLoader&) = delete;

	void SetModel(const ModelNum& modelNum, const std::string& modelName);
private:
	std::vector<std::unique_ptr<Model>> models;
};