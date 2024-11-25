#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <string_view>
#include <vector>
#include "../define/define.h"
#include "../page/datapage.h"

class Table
{
public:
    // 获取表
    bool read(std::string& table_name);
    bool read(std::string&& table_name);

    // 保存表
    bool save();

    // 创建表
    static Table* create();
    static Table* create(std::string& table_name, std::vector<std::vector<std::string>>& columns);
    static Table* create(std::string&& table_name, std::vector<std::vector<std::string>>& columns);

    // 删除表
    bool drop();

    // 插入数据
    bool insert(std::vector<std::string>& values);

    // 删除数据
    bool drop(std::string& key);
    bool drop(std::string&& key);

    // 更新数据
    bool update(std::string& key, std::vector<std::string>& values);
    bool update(std::string&& key, std::vector<std::string>& values);

    // 选择数据
    bool select(std::string& key, std::vector<std::string>& values);
    bool select(std::string&& key, std::vector<std::string>& values);

    // 打印数据
    bool show();
    bool show(std::string& key);
    bool show(std::string&& key);

private:
    Table();
    ~Table();
    // 禁止拷贝和赋值
    void operator=(const Table& table) = delete;
    Table(const Table& table) = delete;
private:
    // 当前表名
    unsigned char key_column;
    // 判断数据是否修改
    bool dirty;
	// 判断表是否存在
    bool exist;
    std::vector<DataPage*> pages;
};

#endif // TABLE_H