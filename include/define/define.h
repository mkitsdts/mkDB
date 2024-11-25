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

// 定义数据库文件路径
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

struct LSN									// 文件页LSN
{
	int FILE_PAGE_LSN_OFFSET;				// 文件页LSN偏移
	int FILE_PAGE_LSN_CHECKSUM;				// 校验和

	LSN() = default;
};

struct file_header
{
	int FILE_PAGE_SPACE_OR_CHECKSUM;			// 文件页空间或校验和
	unsigned char FILE_PAGE_ORDER;				// 文件页偏移
	unsigned char FILE_PAGE_PREV;				// 上一个文件页
	unsigned char FILE_PAGE_NEXT;				// 下一个文件页
	LSN FILE_PAGE_LSN;							// 文件页LSN
	file_header() = default;
};

struct file_tailer
{
	int FILE_PAGE_CHECKSUM;						// 文件页空间或校验和
	file_tailer() = default;
};

struct page_header
{
	unsigned int PAGE_N_DIR_DATA;				// 页中目录数据的数量
	unsigned int PAGE_HEAP_TOP;					// 页堆顶
	unsigned int PAGE_LAST_INSERT;				// 最后插入的记录的位置
	unsigned int PAGE_RECORD_NUMBER;			// 当前页中记录的数量
	page_header() = default;
};	

struct record_header_information
{
	unsigned int RECORD_TYPE;					// 记录类型
	unsigned int COLUMN_OWNED;					// 成员变量个数
	unsigned int RECORD_LENGTH;					// 记录长度
	int NEXT_ROCORD;							// 下一个记录
	unsigned int ROWS_ORDER;					// 行编号
};

struct page_directory
{
	unsigned int max_key;
	unsigned int min_key;
};

struct column_information
{
	unsigned COLUMN_TYPE : 4;					// 列类型
	unsigned COLUMN_NULL : 4;					// 列是否为空
	unsigned char COLUMN_KEY;					// 列键
	unsigned char COLUMN_NAME_LENGTH;			// 列名长度
	char *COLUMN_NAME;							// 列名
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