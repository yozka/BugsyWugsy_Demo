//◦ EggEngine ◦
#include "eFileDisk.h"
#include "engine/debug/eAssert.h"
#include <filesystem>

using namespace Engine::Files;


EFileDisk::EFileDisk()
{

}


EFileDisk::~EFileDisk()
{
	Close();
}


bool EFileDisk::Open(const std::string& name, const OpenModes mode)
{
	if (IsOpen()) {
		Close();
	}
	
	if (name.empty()) {
		sassert2(false, "Имя файла отсутствует");
		return false;
	}
	
	// Открываем файл в соответствии с выбранным режимом
	std::ios_base::openmode md;
	switch (mode) {
		case OpenModes::EF_READ:		md = std::ios::in; break;
		case OpenModes::EF_WRITE:		md = std::ios::out | std::ios::trunc; break;
		case OpenModes::EF_READWRITE:	md = std::ios::in | std::ios::out; break;
		case OpenModes::EF_WRITEREAD:	md = std::ios::in | std::ios::out | std::ios::trunc; break;
	}
	
	m_fileStream.open(name, md | std::ios::binary);
	
	if (!m_fileStream.is_open()) {
		sassert2(false, "Файл не открылся, ошибка");
		return false;
	}
	return true;
}


bool EFileDisk::Close()
{
	if (!IsOpen()) {
		return false;
	}
	m_fileStream.close();
	return true;
}


bool EFileDisk::IsOpen() const
{
	return m_fileStream.is_open();
}


int64_t EFileDisk::Seek(const int64_t offset, const SeekModes origin)
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}
	
	std::ios_base::seekdir dir;
	switch (origin) {
		case SeekModes::EF_SEEK_SET: dir = std::ios::beg; break;
		case SeekModes::EF_SEEK_CUR: dir = std::ios::cur; break;
		case SeekModes::EF_SEEK_END: dir = std::ios::end; break;
	}
	m_fileStream.seekg(offset, dir);
	return m_fileStream.tellg();
}


int64_t EFileDisk::Tell() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}
	return m_fileStream.tellg();
}


int64_t EFileDisk::Size() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}

	const auto current = m_fileStream.tellg();
	m_fileStream.seekg(0, std::ios::end);
	const auto size = m_fileStream.tellg();
	m_fileStream.seekg(current, std::ios::beg);
	return size;
}


//Мы находимся в коце файла
bool EFileDisk::Eof() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return true;
	}
	return m_fileStream.eof();
}


size_t EFileDisk::Read(void* data, const size_t size)
{
	if (!IsOpen() || data == nullptr) {
		sassert2(false, "Невозможно прочитать файл");
		return EF_FAIL;
	}

	m_fileStream.read(static_cast<char*>(data), size);
	return m_fileStream.gcount();
}


size_t EFileDisk::Write(const void* data, const size_t size)
{
	if (!IsOpen() || data == nullptr) {
		sassert2(false, "Невозможно записать файл");
		return EF_FAIL;
	}
	m_fileStream.write(static_cast<const char*>(data), size);
	return size;
}
