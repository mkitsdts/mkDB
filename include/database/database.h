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

    // ������
    bool create_table(const std::string& table_name, std::vector<std::vector<std::string>>& columns);
    bool create_table(const std::string&& table_name, std::vector<std::vector<std::string>>& columns);

    // ɾ����
    bool drop_table(const std::string& table_name);
    bool drop_table(const std::string&& table_name);

    // ��������
    bool insert(std::vector<std::string>& values);
    bool insert(std::vector<std::string>&& values);

    // ѡ���
    bool use(const std::string& table_name);
    bool use(const std::string&& table_name);

	// ɾ������
	bool drop(std::string& key);
	bool drop(std::string&& key);

	// ��������
	bool update(std::string& key, std::vector<std::string>& values);
	bool update(std::string&& key, std::vector<std::string>& values);

	// ѡ������
	bool select(std::string& key, std::vector<std::string>& values);
	bool select(std::string&& key, std::vector<std::string>& values);

	// ��ʾ����
	bool show();
    bool show(std::string& key);
	bool show(std::string&& key);

private:
    std::unordered_map<std::string, Table> tables;
    // ��ǰ��
    unsigned char current_table;
};


#endif // DATABASE_H