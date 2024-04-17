//◦ EggEngine ◦
#include "eOS.h"
#include "eFileDisk.h"

#include "engine/CoreSDL.h"
#include "engine/debug/eAssert.h"
#include <filesystem>


using namespace Engine::Files;


EFile::UPtr OS::Open(const std::string& name, const OpenModes mode)
{
	auto file = std::make_unique<EFileDisk>();
	if (file->Open(name, mode)) {
		return file;
	}
	return {};
}


bool OS::ExistsFile(const std::string& name)
{
	return std::filesystem::exists({name});
}


bool OS::RemoveFile(const std::string& name)
{
	return std::filesystem::remove_all(name);
}


bool OS::ExistsDirectory(const std::string& name)
{
	std::filesystem::directory_entry entry{name};
	return entry.exists();
}


bool OS::CreateDirectory(const std::string& name)
{
	return std::filesystem::create_directories(name);
}


bool OS::RemoveDirectory(const std::string& name)
{
	return std::filesystem::remove_all(name);
}


std::string OS::HomeDirectory()
{
	const auto pref = SDL_GetPrefPath(EN_ORGANIZATION, EN_APPLICATION);
	std::string path = pref;
	SDL_free(pref);
	return path;
}


std::string OS::TempDirectory()
{
	std::string path = HomeDirectory();
	path += "temp/";
	if (!ExistsDirectory(path)) {
		CreateDirectory(path);
	}
	return path;
}


std::string OS::DownloadDirectory()
{
	std::string path = HomeDirectory();
	path += "download/";
	if (!ExistsDirectory(path)) {
		CreateDirectory(path);
	}
	return path;
}


std::string OS::AppDirectory()
{
	std::string path = HomeDirectory();
	path += "app/";
	if (!ExistsDirectory(path)) {
		CreateDirectory(path);
	}
	return path;
}
