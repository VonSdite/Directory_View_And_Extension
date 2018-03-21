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
	
	std::string get_name();					// ��ȡ�ļ�����

	std::string get_create_time_str();  // ��ȡ�ļ�����ʱ�� �ַ�����ʽ
	std::string get_access_time_str();  // ��ȡ�ļ����һ�η��ʵ�ʱ�� �ַ�����ʽ
	std::string get_write_time_str();	// ��ȡ�ļ����һ�α��޸ĵ�ʱ�� �ַ�����ʽ

	__time64_t get_create_time();			// ��ȡ�ļ�����ʱ��
	__time64_t get_access_time();			// ��ȡ�ļ����һ�η��ʵ�ʱ��
	__time64_t get_write_time();			// ��ȡ�ļ����һ�α��޸ĵ�ʱ��
	
	_fsize_ get_size();					// ��ȡ�ļ��Ĵ�С����λByte
	void set_size(_fsize_);				// �����ļ���С

	unsigned get_attrib();				// ��ȡ�ļ�������
	/*
	һ���ļ�/Ŀ¼�����ж������ԣ�ÿ�����Կ����������г�������֮һ��
	_A_ARCH     �������ļ���BACKUPָ��ı�����ʱ�����á�ֵ��0x20��
	_A_HIDDEN   ���ء�ʹ��DIRָ��һ�㿴����������ʹ��/AHѡ�ֵ��0x02��
	_A_NORMAL   ��ͨ���ļ�û�и������Ա����ã�����û�����Ƶر�����д��ֵ��0x00��
	_A_RDONLY   ֻ���������ԡ�д��ΪĿ�Ĵ򿪸��ļ������Ҳ��ܴ���ͬ�����ļ���ֵ��0x01��
	_A_SUBDIR   ��Ŀ¼��ֵ��0x10��
	_A_SYSTEM   ϵͳ�ļ���ʹ��DIRָ��һ�㿴����������ʹ��/A��/A:Sѡ�ֵ��0x04��
	Ҫ���x�Ƿ���ĳ������a��������x & a���м�顣ָ��������Կ���ʹ�ð�λor�������
	����_A_SYSTEM |  _A_RDONLY | _A_HIDDEN��
	*/
private:
	_finddata_t file_data;				// �ļ���Ϣ
	_fsize_ size;						// �ļ���С��������Ŀ¼�ļ���С��Ҫ���¼��㣬���ԼӶ���һ������
};

#endif // !FILE_H
