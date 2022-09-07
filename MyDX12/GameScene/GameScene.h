#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

class DebugCamera;
class LightGroup;
class Circle;
class Tessellation;

namespace XIIlib {

	class GameScene {
	private:// ê√ìIÉÅÉìÉo
		static const int debugTextTexNumber = 0;
		static const int debugJISTextTexNumber = 1;

	private:// ÉÅÉìÉo
		LightGroup* lightGroup = nullptr;
		DebugCamera* d_camera = nullptr;

		void* objectA = nullptr;
		void* objectB = nullptr;

		Math::Vector3 cameraPos;
		float cameRad = 0.0f;

		Circle* circle = nullptr;

	public:
		static GameScene* Create();

		GameScene();
		~GameScene();

		bool Initialize();

		void Update();

		void Draw();
	};
}