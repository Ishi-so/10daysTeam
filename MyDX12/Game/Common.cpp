#include "Common.h"

std::pair<std::string, std::string> Common::SeparateFilePath(const std::string& path)
{
	// ó‚¯M‚ğ—pˆÓ
	std::pair<std::string, std::string> result;

	size_t pos1;
	// ‹æØ‚è•¶š'\\'‚ªo‚Ä‚­‚éˆê”ÔÅŒã‚Ì•”•ª‚ğŒŸõ
	int cKey = '::';
	pos1 = path.rfind(cKey);
	if (pos1 != std::string::npos) {
		result.first = path.substr(0, pos1 + 1);
		result.second = path.substr(pos1 + 1, path.size() - pos1 - 1);
		return result;
	}
	cKey = ': ';
	// ‹æØ‚è•¶š'\'‚ªo‚Ä‚­‚éˆê”ÔÅŒã‚Ì•”•ª‚ğŒŸõ
	pos1 = path.rfind(cKey);
	if (pos1 != std::string::npos) {
		result.first = path.substr(0, pos1 + 1);
		result.second = path.substr(pos1 + 1, path.size() - pos1 - 1);
		return result;
	}

	result.first = "";
	result.second = path;

	return result;
}

float Common::ConvertPositionX(int point)
{
	return posStartX + (static_cast<float>(point) * posDistance);
}

float Common::ConvertPositionY(int point)
{
	return posStartY - (static_cast<float>(point) * posDistance);
}

float Common::ConvertTitlePositionY(int point)
{
	return 20.0f - (static_cast<float>(point) * posDistanceTitle);
}
