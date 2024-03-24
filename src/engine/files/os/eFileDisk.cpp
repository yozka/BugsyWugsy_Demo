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

	// open
	std::string md;
	switch (mode)
	{
		case OpenModes::EF_READ:		md = "rb"; break;
		case OpenModes::EF_WRITE:		md = "wb"; break;
		case OpenModes::EF_READWRITE:	md = "r+b"; break;
		case OpenModes::EF_WRITEREAD:	md = "w+b"; break;
	}

	m_file = SDL_RWFromFile(name.c_str(), md.c_str());
	if (m_file == nullptr) {
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
	if (m_file) {
		if (SDL_RWclose(m_file) != 0) {
			sassert2(false, "Ошибка закрытия файла");
			return false;
		}
	}
	m_file = nullptr;
	return true;
}


bool EFileDisk::IsOpen() const
{
	return m_file != nullptr;
}


int64_t EFileDisk::Seek(const int64_t offset, const SeekModes origin)
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}

	int whence = 0;
	switch (origin)
	{
		case SeekModes::EF_SEEK_SET: whence = RW_SEEK_SET; break;
		case SeekModes::EF_SEEK_CUR: whence = RW_SEEK_CUR; break;
		case SeekModes::EF_SEEK_END: whence = RW_SEEK_END; break;
	}
	return SDL_RWseek(m_file, offset, whence);
}


int64_t EFileDisk::Tell() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}
	return SDL_RWtell(m_file);
}


int64_t EFileDisk::Size() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return EF_FAIL;
	}

	//const auto size = SDL_RWsize(m_file);
	//return size;
	return 0;
}


//Мы находимся в коце файла
bool EFileDisk::Eof() const
{
	if (!IsOpen()) {
		sassert2(false, "Файл не открыт");
		return true;
	}

	const auto size = 0;//SDL_RWsize(m_file);
	if (size < 0) {
		sassert2(false, "Ошибка с определением длины файла");
		return true;
	}
	const auto current = SDL_RWseek(m_file, 0, RW_SEEK_CUR);
	if (current < 0) {
		return true;
	}

	return current == size;
}


size_t EFileDisk::Read(void* data, const size_t size)
{
	if (!IsOpen() || data == nullptr) {
		sassert2(false, "Невозможно прочитать файл");
		return EF_FAIL;
	}

	const auto ret = SDL_RWread(m_file, data, 1, size);
	sassert2(ret > 0, "Ошибка чтения файла");
	return ret;
}


size_t EFileDisk::Write(const void* data, const size_t size)
{
	if (!IsOpen() || data == nullptr) {
		sassert2(false, "Невозможно записать файл");
		return EF_FAIL;
	}
	const auto ret = SDL_RWwrite(m_file, data, 1, size);
	sassert2(ret > 0, "Ошибка записи файла");
	return ret;
}
