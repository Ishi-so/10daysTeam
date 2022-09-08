#pragma once
#include "GameObj.h"

class Block : public GameObj {
public:
	Block();
	~Block();

	void Init()override;	// ‰Šú‰»
	void Update()override;	// XV
	void Draw()override;	// •`‰æ
};