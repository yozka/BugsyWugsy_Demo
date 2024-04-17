//◦ EggEngine ◦
#include "eDir.h"


std::string Engine::Files::ExtractDirectory(const std::string& fileName)
{
	const auto path = fileName.substr(0, fileName.find_last_of("/\\"))+"/";
	return path;
}
