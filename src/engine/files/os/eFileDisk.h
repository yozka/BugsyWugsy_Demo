//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>

#include "engine/files/eFile.h"

namespace Engine::Files
{

	// Файл находящийся на диске
	class EFileDisk : public EFile 
	{
	public:
		using Super		= EFile;
		using UPtr		= std::unique_ptr<EFileDisk>;
		using Ptr		= std::shared_ptr<EFileDisk>;
		using WeakPtr	= std::weak_ptr<EFileDisk>;

	public:
		EFileDisk();
		~EFileDisk() override;
		
	public:
		bool	Open(const std::string& name, const OpenModes mode) override;
		bool	Close() override;
		bool	IsOpen() const override;
		size_t	Read(void *data, const size_t size) override;
		size_t	Write(const void *data, const size_t size) override;
		int64_t	Seek(const int64_t offset, const SeekModes origin = SeekModes::EF_SEEK_SET) override;
		int64_t	Tell() const override;
		int64_t	Size() const override;
		bool	Eof() const override;

	private:
		mutable std::fstream m_fileStream;

	};



}
