#ifndef DATAPAGE_H
#define DATAPAGE_H

#include "../define/define.h"
#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <iostream>

class DataPage
{
public:
    // 创建数据页
    static DataPage* create(unsigned char order);

    // 添加列
    void add_column(char type, std::string &column_name, char is_key = NOT_KEY, char is_null = ALLOW_NULL);
    void add_column(char type, std::string &&column_name, char is_key = NOT_KEY, char is_null = ALLOW_NULL);

    // 删除列
    bool drop_column(std::string &column_name);
    bool drop_column(std::string &&column_name);

    // 选择列
    bool select_column(std::string &column_name);
    bool select_column(std::string &&column_name);
    bool select_column(unsigned char column_order);

    // 读取数据
    bool read(int page_order);

    // 写入数据
    bool write();

private:

    DataPage();
    ~DataPage();
    // 解析数据
    bool parse_data();
    // 加入缓冲区
    bool add_to_buffer();
    // 重写赋值运算符
    void operator=(const DataPage &data_page) = delete;
    DataPage(const DataPage &data_page) = delete;

protected:
    // 缓冲
    char buffer[4096];
    // 数据页是否脏页
    bool dirty;
    // 主键列序号
    unsigned char key_column;
    // 当前列
    unsigned char current_column;
    // 列数
    unsigned int column_count;
    // 文件头
    file_header header;
    // 文件尾
    file_tailer tailer;
    // 页面头记录
    page_header page_header;
    // 页目录
    page_directory directory;
    // 列信息
    std::vector<column_information> columns;
    // 行信息
    std::unordered_map<int,user_records> data;
};

#endif // DATAPAGE_H