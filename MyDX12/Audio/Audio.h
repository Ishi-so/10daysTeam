#pragma once
#include <string>
class Sound;

namespace XIIlib {
	class Audio {
	private:
		// SE�̉���
		float se_volume = 0.1f;
		// BGM�̉���
		float bgm_volume = 0.04f;

		// SE
		Sound* se = nullptr;
		// BGM
		Sound* bgm = nullptr;
	public:
		Audio();
		~Audio();

		void PlaySE(std::string wav,float volume = 0.1f);
		void PlayBGM(std::string wav);

		void StopBGM();
	};
}