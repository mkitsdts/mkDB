#ifndef DEFINE_H
#define DEFINE_H
#pragma once 

#include <string>
#include <vector>

#define PAGE_SIZE 4096

#define ROOT 0

#define NOT_KEY 0
#define KEY 1
#define NOT_NULL 0
#define ALLOW_NULL 1

#define INT 0
#define FLOAT 1
#define VARCHAR 2
#define DATE 3

// �������ݿ��ļ�·��
constexpr const char* PAGE_PAGE_PATH = "data.db";
constexpr const char* INDEX_PATH = "index.db";

inline int toInt(char c1,char c2,char c3,char c4)
{
    return (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;
}

inline float toFloat(char c1,char c2,char c3,char c4)
{
	return (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;
}

inline std::string to_date(char c1,char c2,char c3,char c4)
{
	std::string date;
	date += std::to_string((int)c1);
	date += std::to_string((int)c2);
	date += "-";
	date += std::to_string((int)c3);
	date += "-";
	date += std::to_string((int)c4);
	return date;
}

inline unsigned int hash_value(const std::string& str)
{
	unsigned int hash = 0;
	for (auto c : str)
	{
		hash = hash * 131 + c;
	}
	return hash;
}

struct LSN									// �ļ�ҳLSN
{
	int FILE_PAGE_LSN_OFFSET;				// �ļ�ҳLSNƫ��
	int FILE_PAGE_LSN_CHECKSUM;				// У���

	LSN() = default;
};

struct file_header
{
	int FILE_PAGE_SPACE_OR_CHECKSUM;			// �ļ�ҳ�ռ��У���
	unsigned char FILE_PAGE_ORDER;				// �ļ�ҳƫ��
	unsigned char FILE_PAGE_PREV;				// ��һ���ļ�ҳ
	unsigned char FILE_PAGE_NEXT;				// ��һ���ļ�ҳ
	LSN FILE_PAGE_LSN;							// �ļ�ҳLSN
	file_header() = default;
};

struct file_tailer
{
	int FILE_PAGE_CHECKSUM;						// �ļ�ҳ�ռ��У���
	file_tailer() = default;
};

struct page_header
{
	unsigned int PAGE_N_DIR_DATA;				// ҳ��Ŀ¼���ݵ�����
	unsigned int PAGE_HEAP_TOP;					// ҳ�Ѷ�
	unsigned int PAGE_LAST_INSERT;				// ������ļ�¼��λ��
	unsigned int PAGE_RECORD_NUMBER;			// ��ǰҳ�м�¼������
	page_header() = default;
};	

struct record_header_information
{
	unsigned int RECORD_TYPE;					// ��¼����
	unsigned int COLUMN_OWNED;					// ��Ա��������
	unsigned int RECORD_LENGTH;					// ��¼����
	int NEXT_ROCORD;							// ��һ����¼
	unsigned int ROWS_ORDER;					// �б��
};

struct page_directory
{
	unsigned int max_key;
	unsigned int min_key;
};

struct column_information
{
	unsigned COLUMN_TYPE : 4;					// ������
	unsigned COLUMN_NULL : 4;					// ���Ƿ�Ϊ��
	unsigned char COLUMN_KEY;					// �м�
	unsigned char COLUMN_NAME_LENGTH;			// ��������
	char *COLUMN_NAME;							// ����
	void assign(int c)
	{
		COLUMN_TYPE = c >> 4 & 0x0f;
		COLUMN_NULL = c & 0x0f;
	}
	char toChar() const
	{
		return (COLUMN_TYPE << 4) | COLUMN_NULL;
	}
};

struct user_records
{
	record_header_information header;
	std::vector<std::string> values;
};

#endif // DEFINE_H