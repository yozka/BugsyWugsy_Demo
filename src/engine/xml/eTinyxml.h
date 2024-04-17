//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <tinyxml2.h>

#include "engine/files/eFile.h"

namespace Engine::Xml
{
	using Node = tinyxml2::XMLElement;

	std::unique_ptr<tinyxml2::XMLDocument> Load(const Engine::Files::EFile::UPtr& file);
	std::unique_ptr<tinyxml2::XMLDocument> Create(const std::string &rootName);
	bool Save(const std::unique_ptr<tinyxml2::XMLDocument> &doc, const Engine::Files::EFile::UPtr& file);


	std::string ToString(const Node *node, const std::string& name, const std::string &def = {});
	float ToFloat(const Node *node, const std::string& name, const float &def = {});
	int ToInteger(const Node *node, const std::string& name, const int &def = {});
	bool ToBool(const Node *node, const std::string& name, const bool &def = {});

	bool Contain(const Node *node, const std::string& name);

}
