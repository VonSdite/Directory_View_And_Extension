#ifndef FILE_H
#define FILE_H

#include <io.h>
#include <string>

#define _fsize_ long long

class File 
{
public:
	File(_finddata_t);
	~File();
	bool operator==(const File &);
	File(const File&);
	
	std::string get_name();					// 获取文件名字

	std::string get_create_time_str();  // 获取文件创建时间 字符串形式
	std::string get_access_time_str();  // 获取文件最后一次访问的时间 字符串形式
	std::string get_write_time_str();	// 获取文件最后一次被修改的时间 字符串形式

	__time64_t get_create_time();			// 获取文件创建时间
	__time64_t get_access_time();			// 获取文件最后一次访问的时间
	__time64_t get_write_time();			// 获取文件最后一次被修改的时间
	
	_fsize_ get_size();					// 获取文件的大小，单位Byte
	void set_size(_fsize_);				// 设置文件大小

	unsigned get_attrib();				// 获取文件的属性
	/*
	一个文件/目录可以有多种属性，每种属性可以是下面列出的属性之一。
	_A_ARCH     档案。文件被BACKUP指令改变或清除时被设置。值：0x20。
	_A_HIDDEN   隐藏。使用DIR指令一般看不到，除非使用/AH选项。值：0x02。
	_A_NORMAL   普通。文件没有更多属性被设置，可以没有限制地被读或写。值：0x00。
	_A_RDONLY   只读。不能以“写”为目的打开该文件，并且不能创建同名的文件。值：0x01。
	_A_SUBDIR   子目录。值：0x10。
	_A_SYSTEM   系统文件。使用DIR指令一般看不见，除非使用/A或/A:S选项。值：0x04。
	要检查x是否含有某个属性a，可以用x & a进行检查。指定多个属性可以使用按位or运算符，
	例如_A_SYSTEM |  _A_RDONLY | _A_HIDDEN。
	*/
private:
	_finddata_t file_data;				// 文件信息
	_fsize_ size;						// 文件大小，由于子目录文件大小需要重新计算，所以加多这一条属性
};

#endif // !FILE_H
