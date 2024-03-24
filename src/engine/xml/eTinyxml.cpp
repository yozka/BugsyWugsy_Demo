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
