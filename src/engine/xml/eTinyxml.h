//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <tinyxml2.h>

#include "engine/files/eFile.h"

namespace Engine::Xml
{

	std::unique_ptr<tinyxml2::XMLDocument> Load(const Engine::Files::EFile::UPtr& file);
	std::unique_ptr<tinyxml2::XMLDocument> Create(const std::string &rootName);
	bool Save(const std::unique_ptr<tinyxml2::XMLDocument> &doc, const Engine::Files::EFile::UPtr& file);
}
