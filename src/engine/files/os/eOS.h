//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "engine/files/eFile.h"

namespace Engine::Files
{

	// Операционная система работа с файлами
	class OS
	{
	public:
		OS() = delete;

		static bool ExistsFile(const std::string& name);
		static bool RemoveFile(const std::string& name);
		
		static bool ExistsDirectory(const std::string& name);
		static bool CreateDirectory(const std::string& name);
		static bool RemoveDirectory(const std::string& name);
		
		static std::string HomeDirectory();
		static std::string TempDirectory();
		static std::string DownloadDirectory();
		static std::string AppDirectory();
		
		static EFile::UPtr Open(const std::string& name, const OpenModes mode = OpenModes::EF_READ);
	};



}
