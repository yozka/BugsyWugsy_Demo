//◦ EggEngine ◦
#include "eUtils.h"
#include <stdexcept>
#include <sstream>

namespace Engine
{

	std::vector<std::string> Split(const std::string& s, const char seperator)
	{
		std::vector<std::string> output;
		std::string::size_type prev_pos = 0, pos = 0;
		while ((pos = s.find(seperator, pos)) != std::string::npos) {
			std::string substring(s.substr(prev_pos, pos - prev_pos));
			output.push_back(substring);
			prev_pos = ++pos;
		}
		output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
		return output;
	}

	std::string Remove(const std::string& s, const char del)
	{
		auto str = s;
		str.erase(std::remove(str.begin(), str.end(), del), str.cend());
		return str;
	}

	int StringToInt(const std::string& str, const int def, std::size_t* pos, int base) noexcept
	{
		// wrapping std::stoi because it may throw an exception
		
		try {
			return std::stoi(str, pos, base);
		}
		
		catch (const std::invalid_argument& ia) {
			//std::cerr << "Invalid argument: " << ia.what() << std::endl;
			return def;
		}
		
		catch (const std::out_of_range& oor) {
			//std::cerr << "Out of Range error: " << oor.what() << std::endl;
			return def;
		}
		
		catch (const std::exception& e)
		{
			//std::cerr << "Undefined error: " << e.what() << std::endl;
			return def;
		}
		return def;
	}

	float StringToFloat(const std::string& str, const float def, std::size_t* pos) noexcept
	{
		try {
			return std::stof(str, pos);
		}
		
		catch (const std::invalid_argument& ia) {
			return def;
		}
		
		catch (const std::out_of_range& oor) {
			return def;
		}
		
		catch (const std::exception& e)
		{
			return def;
		}
		return def;
	}

	SDL_Color StringToColor(const std::string& str, const SDL_Color& def)
	{
		if (str.empty()) return def;
		SDL_Color color = def;
		
		if (str == "black")	return {00,00,00,0xFF};
		if (str == "red")	return {0xFF,00,00,0xFF};
		if (str == "green") return {00,0xFF,00,0xFF};
		if (str == "blue")	return {00,00,0xFF,0xFF};
		
		if (str.at(0) == '#') {
			std::string hexCode = str.substr(1);
			unsigned long value = std::stoul(hexCode, nullptr, 16);
			if (hexCode.length() == 8) {
				color.a = (value >> 24) & 0xff;
			}
			color.r = (value >> 16) & 0xff;
			color.g = (value >> 8) & 0xff;
			color.b = (value >> 0) & 0xff;
		}
		return color;
	}

	//Высчитать процент от базового значения
	bool CalcPercent(const std::string &percent, const float base, float *value)
	{
		if (percent.empty()) return false;
		if (percent.back() != '%') return false;
		const std::string_view s(percent.data(), percent.length()-1);
		try {
			if (value) {
				const float source = std::stof(s.data());
				*value = (source / 100.0f) * base;
			}
			return true;
		}
		catch (const std::invalid_argument& ia) { return false;	}
		catch (const std::out_of_range& oor) 	{ return false;	}
		catch (const std::exception& e)			{ return false; }
		return false;
	}

}
