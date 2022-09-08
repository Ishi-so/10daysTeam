#pragma once
#include "SceneState.h"

class Title : public SceneState {
public:
	Title();
	~Title();

	void Initialize()override;
	void Update()override;
	void Draw()override;

private:// •Ï”

};