#include "Dir.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

void Dir::differ(std::unordered_map<std::string, std::string> &file_to_write_time)
{
	bool change = false;
	for (auto file : file_list)
	{
		if (file.get_write_time_str() != file_to_write_time[file.get_name()])
		{
			if (file_to_write_time[file.get_name()] == "")
			{
				cout << file.get_name() << " -> " << "new add!" << endl;
			}
			else cout << file.get_name() << " " << file_to_write_time[file.get_name()] << " -> "
				<< file.get_write_time_str() << endl;
			if (!change) change = true;
		} 
		file_to_write_time[file.get_name()] = "";
	}
	for (auto file : file_to_write_time)
	{
		if (file.second != "")
		{
			cout << file.first << " -> " << "deleted!" << endl;
			if (!change) change = true;
		}
	}

	if (!change)
		cout << "没有任何变化!" << endl;
	cout << "========================\n";
}

list<File> Dir::scandir(bool (*select_criteria)(File &), bool(*compare)(File &, File &))
{
	list<File> file_list = this->file_list;

	file_list.sort(compare);		// 先按照排序规则排序

	// 在按照筛选规则筛选
	for (list<File>::iterator file = file_list.begin(); file != file_list.end();)
	{
		if (!select_criteria(*file))
		{
			file_list.remove(*file++);
		}
		else ++file;
	}

	return file_list;
}

Dir::Dir(const string dir)
{
	dir_ = dir;			// 目录名
	init_file_list();
}

Dir::Dir(const Dir &d)
{
	file_list = d.file_list;
	dir_ = d.dir_;
}

Dir::~Dir()
{
}

void Dir::init_file_list()
{ // 遍历当前目录下所有文件 来初始化文件列表
	intptr_t handle;
	_finddata_t findData;

	char dirNew[2048];
	memset(dirNew, 0, sizeof(dirNew));
	strcpy(dirNew, dir_.c_str());
	strcat(dirNew, "/*.*");

	handle = _findfirst(dirNew, &findData);    // 查找目录中的第一个文件
	if (handle == -1)        // 检查是否成功
		return;

	do
	{
		if (!strcmp(findData.name, ".") || !strcmp(findData.name, ".."))
			continue;
		File file(findData);

		// 如果是文件夹，只能递归遍历所有的文件，计算出文件夹的大小
		//if (file.get_attrib() & (_A_SUBDIR))
		//{
		//	memset(dirNew, 0, sizeof(dirNew));
		//	strcpy(dirNew, dir_.c_str());
		//	strcat(dirNew, "/");
		//	strcat(dirNew, file.get_name().c_str());

		//	file.set_size(calc_sub_dir_size(dirNew));
		//}

		file_list.push_back(file);
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	_findclose(handle);    // 关闭搜索句柄
}

_fsize_ Dir::calc_sub_dir_size(const char *sub_dir)
{ // 遍历子目录下所有文件，求出所有文件大小和即为子目录的大小
	_fsize_ size = 0;
	char file[2048];
	memset(file, 0, sizeof(file));
	strcpy(file, sub_dir);
	strcat(file, "/*.*");    // 在目录后面加上"/*.*"进行第一次搜索

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(file, &findData);
	if (handle == -1)        // 检查是否成功
		return 0;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (!strcmp(findData.name, ".") || !strcmp(findData.name, ".."))
				continue;

			// 在目录后面加上"/"和搜索到的目录名进行下一次搜索
			strcpy(file, sub_dir);
			strcat(file, "/");
			strcat(file, findData.name);

			size += calc_sub_dir_size(file);
		}
		else
			size += (_fsize_)findData.size;
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // 关闭搜索句柄
	return size;
}
