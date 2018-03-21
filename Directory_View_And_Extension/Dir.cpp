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
		cout << "û���κα仯!" << endl;
	cout << "========================\n";
}

list<File> Dir::scandir(bool (*select_criteria)(File &), bool(*compare)(File &, File &))
{
	list<File> file_list = this->file_list;

	file_list.sort(compare);		// �Ȱ��������������

	// �ڰ���ɸѡ����ɸѡ
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
	dir_ = dir;			// Ŀ¼��
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
{ // ������ǰĿ¼�������ļ� ����ʼ���ļ��б�
	intptr_t handle;
	_finddata_t findData;

	char dirNew[2048];
	memset(dirNew, 0, sizeof(dirNew));
	strcpy(dirNew, dir_.c_str());
	strcat(dirNew, "/*.*");

	handle = _findfirst(dirNew, &findData);    // ����Ŀ¼�еĵ�һ���ļ�
	if (handle == -1)        // ����Ƿ�ɹ�
		return;

	do
	{
		if (!strcmp(findData.name, ".") || !strcmp(findData.name, ".."))
			continue;
		File file(findData);

		// ������ļ��У�ֻ�ܵݹ�������е��ļ���������ļ��еĴ�С
		//if (file.get_attrib() & (_A_SUBDIR))
		//{
		//	memset(dirNew, 0, sizeof(dirNew));
		//	strcpy(dirNew, dir_.c_str());
		//	strcat(dirNew, "/");
		//	strcat(dirNew, file.get_name().c_str());

		//	file.set_size(calc_sub_dir_size(dirNew));
		//}

		file_list.push_back(file);
	} while (_findnext(handle, &findData) == 0);    // ����Ŀ¼�е���һ���ļ�

	_findclose(handle);    // �ر��������
}

_fsize_ Dir::calc_sub_dir_size(const char *sub_dir)
{ // ������Ŀ¼�������ļ�����������ļ���С�ͼ�Ϊ��Ŀ¼�Ĵ�С
	_fsize_ size = 0;
	char file[2048];
	memset(file, 0, sizeof(file));
	strcpy(file, sub_dir);
	strcat(file, "/*.*");    // ��Ŀ¼�������"/*.*"���е�һ������

	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(file, &findData);
	if (handle == -1)        // ����Ƿ�ɹ�
		return 0;

	do
	{
		if (findData.attrib & _A_SUBDIR)
		{
			if (!strcmp(findData.name, ".") || !strcmp(findData.name, ".."))
				continue;

			// ��Ŀ¼�������"/"����������Ŀ¼��������һ������
			strcpy(file, sub_dir);
			strcat(file, "/");
			strcat(file, findData.name);

			size += calc_sub_dir_size(file);
		}
		else
			size += (_fsize_)findData.size;
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);    // �ر��������
	return size;
}
