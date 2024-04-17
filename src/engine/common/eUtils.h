//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "engine/CoreSDL.h"

namespace Engine
{

	std::vector<std::string> Split(const std::string& s, const char seperator);
	std::string Remove(const std::string& s, const char del);

	int StringToInt(const std::string& str, const int def = 0, std::size_t* pos = 0, int base = 10) noexcept;
	float StringToFloat(const std::string& str, const float def = 0, std::size_t* pos = 0) noexcept;
	SDL_Color StringToColor(const std::string& str, const SDL_Color &def);

	bool CalcPercent(const std::string &percent, const float base, float *value); //Высчитать процент от базового значения
}
