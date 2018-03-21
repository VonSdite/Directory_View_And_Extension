#ifndef QUERY_H
#define QUERY_H

#include "Dir.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
using namespace std;

bool none_select(File &file);
bool none_cmp(File &file_a, File &file_b);
bool cmp_by_name_asc(File &file_a, File &file_b);
bool cmp_by_name_dec(File &file_a, File &file_b);
bool cmp_by_size_asc(File &file_a, File &file_b);
bool cmp_by_size_dec(File &file_a, File &file_b);
bool cmp_by_write_time_asc(File &file_a, File &file_b);
bool cmp_by_write_time_dec(File &file_a, File &file_b);
void enter_model(int choice);
void log_model();
void difference_model();

void heart_beat();

void heart_beat()
{
	int choice;
	while (true)
	{

		cout << "选择要进入的模式: " << endl
			<< "1. 日志模式" << endl
			<< "2. 差异模式" << endl;
		cin >> choice;
		enter_model(choice);
	}
}

void enter_model(int choice)
{
	switch (choice)
	{
	case 1:
		log_model();
		break;
	case 2:
		difference_model();
		break;
	default:
		break;
	}
}

void difference_model()
{
	string dir;
	cout << "输入所要访问的目录(例d:/): ";
	cin >> dir;
	ifstream file;
	file.open("./" + dir.substr(dir.rfind("/") + 1) + ".txt");
	if (!file)
	{
		cout << "没有之前的日志文件" << endl;
		return;
	}

	Dir d(dir);

	unordered_map<string, string> file_to_write_time;
	string name, write_time, line;
	while (!file.eof())
	{
		getline(file, line);
		if (line != "")
		{
			name = line.substr(0, line.find(","));
			write_time = line.substr(line.rfind(","));
			write_time = write_time.substr(write_time.rfind(" ") + 1);
			file_to_write_time[name] = write_time;
		}
	}
	file.close();

	d.differ(file_to_write_time);
}

void log_model()
{
	string dir;
	cout << "输入所要访问的目录(例d:/): ";
	cin >> dir;
	Dir d(dir);

	cout << "选择文件显示顺序:" << endl
		<< "1. 按文件名升序显示" << endl
		<< "2. 按文件名降序显示" << endl
		<< "3. 按文件大小升序显示" << endl
		<< "4. 按文件大小降序显示" << endl
		<< "5. 按最后一次修改时间升序显示" << endl
		<< "6. 按最后一次修改时间降序显示" << endl
		<< "7. 不排序" << endl;
	int c;
	cin >> c;
	while (c > 7 || c < 1)
	{
		cout << "请重新输入" << endl;
		cin >> c;
	}
	list<File> file_list;
	switch (c)
	{
	case 1:
		file_list = d.scandir(none_select, cmp_by_name_asc);
		break;
	case 2:
		file_list = d.scandir(none_select, cmp_by_name_dec);
		break;
	case 3:
		file_list = d.scandir(none_select, cmp_by_size_asc);
		break;
	case 4:
		file_list = d.scandir(none_select, cmp_by_size_dec);
		break;
	case 5:
		file_list = d.scandir(none_select, cmp_by_write_time_asc);
		break;
	case 6:
		file_list = d.scandir(none_select, cmp_by_write_time_dec);
		break;
	case 7:
		file_list = d.scandir(none_select, none_cmp);
		break;
	default:
		break;
	}
	cout << setiosflags(ios::left)
		<< setw(40)
		<< "文件名"
		<< " "
		<< setw(18)
		<< "文件大小"
		<< " "
		<< "文件最近修改时间"
		<< endl;

	ofstream outf;
	outf.open("./" + dir.substr(dir.rfind("/") + 1) + ".txt");

	for (auto file : file_list)
	{
		cout << setiosflags(ios::left)
			<< setw(40)
			<< file.get_name() + ","
			<< " ";
		if (file.get_attrib() & _A_SUBDIR)
			cout << setw(18) << "<dir>,";
		else
		{
			char size[20];
			memset(size, 0, sizeof(size));
			sprintf(size, "%I64d,", file.get_size());
			cout << setw(18) << size;
		}
		cout << " "
			<< file.get_write_time_str()
			<< endl;

		outf << setiosflags(ios::left)
			<< setw(40)
			<< file.get_name() + ","
			<< " ";
		if (file.get_attrib() & _A_SUBDIR)
			outf << setw(18) << "<dir>,";
		else
		{
			char size[20];
			memset(size, 0, sizeof(size));
			sprintf(size, "%I64d,", file.get_size());
			outf << setw(18) << size;
		}
		outf << " "
			<< file.get_write_time_str()
			<< endl;
	}

	outf.close();

	cout << "=========================" << endl;
}


bool none_select(File &file) { return true; }

bool none_cmp(File &file_a, File &file_b) { return false; }

bool cmp_by_name_asc(File &file_a, File &file_b)
{
	return file_a.get_name() < file_b.get_name();
}

bool cmp_by_name_dec(File &file_a, File &file_b)
{
	return file_a.get_name() > file_b.get_name();
}

bool cmp_by_size_asc(File &file_a, File &file_b)
{
	return file_a.get_size() < file_b.get_size();
}
bool cmp_by_size_dec(File &file_a, File &file_b)
{
	return file_a.get_size() > file_b.get_size();
}

bool cmp_by_write_time_asc(File &file_a, File &file_b)
{
	return file_a.get_write_time() < file_b.get_write_time();
}
bool cmp_by_write_time_dec(File &file_a, File &file_b)
{
	return file_a.get_write_time() > file_b.get_write_time();
}

#endif // !QUERY_H

