//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <variant>
#include <map>
#include <vector>



namespace Engine
{
	struct TVariant : public std::variant<bool, int, float, std::string>
	{
		bool ToBool(const bool def = {}) const
		{
			if (std::holds_alternative<bool>(*this)) {
				return std::get<bool>(*this);
			}
			return def;
		}
		
		int ToInteger(const int def = {}) const
		{
			if (std::holds_alternative<int>(*this)) {
				return std::get<int>(*this);
			}
			return def;
		}
		
		float ToFloat(const float def = {}) const
		{
			if (std::holds_alternative<float>(*this)) {
				return std::get<float>(*this);
			}
			return def;
		}
		
		std::string ToString(const std::string &def = {}) const
		{
			if (std::holds_alternative<std::string>(*this)) {
				return std::get<std::string>(*this);
			}
			return def;
		}
	};
	
	
	struct Property : public std::map<std::string, TVariant>
	{
		std::vector<std::string> Keys() const
		{
			std::vector<std::string> keys;
			for (const auto&[key, value] : *this) {
				keys.push_back(key);
			}
			return keys;
		}
		
		bool Contains(const std::string &key) const
		{
			const auto it = find(key);
			return it != cend() ? true : false;
		}		
		
		bool GetBool(const std::string &key, const bool &def = {}) const
		{
			const auto it = find(key);
			if (it != cend()) {
				return it->second.ToBool(def);
			}
			return def;
		}
		
		int GetInteger(const std::string &key, const int &def = {}) const
		{
			const auto it = find(key);
			if (it != cend()) {
				return it->second.ToInteger(def);
			}
			return def;
		}
		
		float GetFloat(const std::string &key, const float &def = {}) const
		{
			const auto it = find(key);
			if (it != cend()) {
				return it->second.ToFloat(def);
			}
			return def;
		}
		
		std::string GetString(const std::string &key, const std::string &def = {}) const
		{
			const auto it = find(key);
			if (it != cend()) {
				return it->second.ToString(def);
			}
			return def;
		}
	};

}
