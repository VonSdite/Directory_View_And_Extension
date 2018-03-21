#include "File.h"
#include <time.h>

using namespace std;

File::File(_finddata_t data)
{
	file_data = data;
	size = (_fsize_)data.size;
}

File::File(const File &file)
{
	this->file_data = file.file_data;
	this->size = file.size;
}

bool File::operator==(const File &file)
{
	if (this->file_data.attrib == file.file_data.attrib
		&& this->file_data.name == file.file_data.name
		&& this->file_data.size == file.file_data.size
		&& this->file_data.time_access == file.file_data.time_access
		&& this->file_data.time_create == file.file_data.time_create
		&& this->file_data.time_write == file.file_data.time_write
		&& this->file_data.size == file.file_data.size)
		return true;
	return false;
}

File::~File()
{
}

string to_localtime(time_t time_)
{
	struct tm now_time;

	#if defined(__linux__)
		// Linuxϵͳ
		localtime_r(&time_, &now_time);
	#elif defined(_WIN32)
		// Windowsϵͳ
		localtime_s(&now_time, &time_);
	#endif

		char time_ch[256];
		sprintf(time_ch, "%d-%02d-%02d/%02d:%02d:%02d", now_time.tm_year + 1900, now_time.tm_mon + 1,
			now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
		return string(time_ch);
}

string File::get_name()
{
	return (string)file_data.name;
}
 
__time64_t File::get_create_time()
{
	return __time64_t(file_data.time_create);
}

__time64_t File::get_access_time()
{
	return __time64_t(file_data.time_access);
}

__time64_t File::get_write_time()
{
	return __time64_t(file_data.time_write);
}

string File::get_create_time_str()
{
	return to_localtime(time_t(file_data.time_create));
}

string File::get_access_time_str()
{
	return to_localtime(time_t(file_data.time_access));
}

string File::get_write_time_str()
{
	return to_localtime(time_t(file_data.time_write));
}

_fsize_ File::get_size()
{
	return size;
}

unsigned File::get_attrib()
{
	return file_data.attrib;
}

void File::set_size(_fsize_ file_size)
{
	size = file_size;
}
