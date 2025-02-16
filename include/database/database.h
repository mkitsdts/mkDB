#ifndef DATABASE_H
#define DATABASE_H

#include <unordered_map>
#include <string>
#include "../table/table.h"

class Database
{
public:
    Database();
    ~Database();

	static Database* instance();

    // 创建表
    bool create_table(std::string& table_name, std::vector<std::vector<std::string>>& columns);
    bool create_table(std::string&& table_name, std::vector<std::vector<std::string>>& columns);

    // 删除表
    bool drop_table(std::string& table_name);
    bool drop_table(std::string&& table_name);

    // 插入数据
    bool insert(std::vector<std::string>& values);
    bool insert(std::vector<std::string>&& values);

    // 选择表
    bool use(std::string& table_name);
    bool use(std::string&& table_name);

	// 删除数据
	bool drop(std::string& key);
	bool drop(std::string&& key);

	// 更新数据
	bool update(std::string& key, std::vector<std::string>& values);
	bool update(std::string&& key, std::vector<std::string>& values);

	// 选择数据
	bool select(std::string& key, std::vector<std::string>& values);
	bool select(std::string&& key, std::vector<std::string>& values);

	// 显示数据
	bool show();
    bool show(std::string& key);
	bool show(std::string&& key);

private:
    std::unordered_map<std::string, Table*> tables;
    // 当前表
    std::string current_table;
};

inline Database* mkDb = Database::instance();

#endif // DATABASE_H