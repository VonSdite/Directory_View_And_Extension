#ifndef DIR_H
#define DIR_H

#include <string>
#include <list>
#include <unordered_map>
#include "File.h"

class Dir
{
public:
	Dir(const std::string);			// 构造函数
	Dir(const Dir &);				// 拷贝构造函数
	~Dir();							// 析构函数

	// 選取滿足謂詞 select_criteria 的所有文件
	// 并按照 compare 指定的方式進行排序後將所選取的文件存入列表fileList中
	std::list<File> scandir(bool (*select_criteria)(File &), 
						bool (*compare)(File &, File &));

	void differ(std::unordered_map<std::string, std::string> &);
private:
	std::list<File> file_list;		// File文件列表
	std::string dir_;				// 目录字符串
	void init_file_list();			// 用来初始化File文件列表, 构造函数时调用
	_fsize_ calc_sub_dir_size(const char *);	// 计算子目录的大小
												//（没有直接得到子目录大小的方法，只能自己算）
};



#endif // !DIR_H
