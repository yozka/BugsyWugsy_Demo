//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

namespace Engine::Files
{
	
	constexpr int EF_FAIL = -1;


	// open modes
	enum class OpenModes
	{
		EF_READ,			// "rb"
		EF_WRITE,			// "wb" Стераем полностью файл
		EF_READWRITE,		// "r+b" Режим дозаписывание в файл
		EF_WRITEREAD		// "w+b"
	};


	// seek modes ( better to match original values: 0,1,2 )
	enum class SeekModes
	{
		EF_SEEK_SET,
		EF_SEEK_CUR,
		EF_SEEK_END
	};


	// Базовый класс для работы со сфайлом
	class EFile 
	{
	public:
		using UPtr		= std::unique_ptr<EFile>;
		using Ptr		= std::shared_ptr<EFile>;
		using WeakPtr	= std::weak_ptr<EFile>;

	public:
		EFile() = default;
		virtual ~EFile() = default;

	public:
		virtual	bool	Open(const std::string& name, const OpenModes mode) = 0;
		virtual	bool	Close() = 0;
		virtual	bool	IsOpen() const = 0;
		virtual	size_t	Read(void *data, const size_t size) = 0;
		virtual	size_t	Write(const void *data, const size_t size) = 0;
		virtual	int64_t	Seek(const int64_t offset, const SeekModes origin = SeekModes::EF_SEEK_SET) = 0;
		virtual	int64_t	Tell() const = 0;
		virtual	int64_t	Size() const = 0;
		virtual	bool	Eof() const = 0;

	};



}
