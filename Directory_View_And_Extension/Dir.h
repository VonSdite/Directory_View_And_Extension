#ifndef DIR_H
#define DIR_H

#include <string>
#include <list>
#include <unordered_map>
#include "File.h"

class Dir
{
public:
	Dir(const std::string);			// ���캯��
	Dir(const Dir &);				// �������캯��
	~Dir();							// ��������

	// �xȡ�M���^�~ select_criteria �������ļ�
	// ������ compare ָ���ķ�ʽ�M�������ጢ���xȡ���ļ������б�fileList��
	std::list<File> scandir(bool (*select_criteria)(File &), 
						bool (*compare)(File &, File &));

	void differ(std::unordered_map<std::string, std::string> &);
private:
	std::list<File> file_list;		// File�ļ��б�
	std::string dir_;				// Ŀ¼�ַ���
	void init_file_list();			// ������ʼ��File�ļ��б�, ���캯��ʱ����
	_fsize_ calc_sub_dir_size(const char *);	// ������Ŀ¼�Ĵ�С
												//��û��ֱ�ӵõ���Ŀ¼��С�ķ�����ֻ���Լ��㣩
};



#endif // !DIR_H
