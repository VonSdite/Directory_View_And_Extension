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

		cout << "ѡ��Ҫ�����ģʽ: " << endl
			<< "1. ��־ģʽ" << endl
			<< "2. ����ģʽ" << endl;
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
	cout << "������Ҫ���ʵ�Ŀ¼(��d:/): ";
	cin >> dir;
	ifstream file;
	file.open("./" + dir.substr(dir.rfind("/") + 1) + ".txt");
	if (!file)
	{
		cout << "û��֮ǰ����־�ļ�" << endl;
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
	cout << "������Ҫ���ʵ�Ŀ¼(��d:/): ";
	cin >> dir;
	Dir d(dir);

	cout << "ѡ���ļ���ʾ˳��:" << endl
		<< "1. ���ļ���������ʾ" << endl
		<< "2. ���ļ���������ʾ" << endl
		<< "3. ���ļ���С������ʾ" << endl
		<< "4. ���ļ���С������ʾ" << endl
		<< "5. �����һ���޸�ʱ��������ʾ" << endl
		<< "6. �����һ���޸�ʱ�併����ʾ" << endl
		<< "7. ������" << endl;
	int c;
	cin >> c;
	while (c > 7 || c < 1)
	{
		cout << "����������" << endl;
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
		<< "�ļ���"
		<< " "
		<< setw(18)
		<< "�ļ���С"
		<< " "
		<< "�ļ�����޸�ʱ��"
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

