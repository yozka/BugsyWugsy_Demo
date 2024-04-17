//◦ EggEngine ◦
#include "eTinyxml.h"
#include <vector>
#include <memory>

std::unique_ptr<tinyxml2::XMLDocument> Engine::Xml::Load(const Engine::Files::EFile::UPtr& file)
{
	auto doc = std::make_unique<tinyxml2::XMLDocument>();
	if (file) {
		const auto size = file->Size();
		if (size > 0) {
			std::vector<char> buffer;
			buffer.resize(size + 1, 0);
			if (file->Read(buffer.data(), size) == size) {
				std::string_view xml(buffer.data(), size);
				doc->Parse(xml.data());
			}
		}
	}
	return doc;
}


std::unique_ptr<tinyxml2::XMLDocument> Engine::Xml::Create(const std::string &rootName)
{
	auto doc = std::make_unique<tinyxml2::XMLDocument>();
	auto root = doc->NewElement(rootName.c_str());
	doc->InsertFirstChild(root);
	return doc;
}

bool Engine::Xml::Save(const std::unique_ptr<tinyxml2::XMLDocument> &doc, const Engine::Files::EFile::UPtr& file)
{
	tinyxml2::XMLPrinter printer;
	doc->Accept(&printer);
	file->Write(printer.CStr(), printer.CStrSize());
	file->Tell();
	return true;
}


std::string Engine::Xml::ToString(const Node *node, const std::string& name, const std::string &def)
{
	if (node) {
		if (auto p = node->Attribute(name.c_str())) {
			return { p };
		}
	}
	return def;
}


float Engine::Xml::ToFloat(const Node *node, const std::string& name, const float &def)
{
	if (node) {
		return node->FloatAttribute(name.c_str(), def);
	}
	return def;
}


int Engine::Xml::ToInteger(const Node *node, const std::string& name, const int &def)
{
	if (node) {
		return node->IntAttribute(name.c_str(), def);
	}
	return def;
}


bool Engine::Xml::ToBool(const Node *node, const std::string& name, const bool &def)
{
	if (node) {
		return node->BoolAttribute(name.c_str(), def);
	}
	return def;
}


bool Engine::Xml::Contain(const Node *node, const std::string& name)
{
	if (node) {
		return node->FindAttribute(name.c_str());
	}
	return false;
}
