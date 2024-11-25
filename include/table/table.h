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
    // ��ȡ��
    bool read(std::string& table_name);
    bool read(std::string&& table_name);

    // �����
    bool save();

    // ������
    static Table* create();
    static Table* create(std::string& table_name, std::vector<std::vector<std::string>>& columns);
    static Table* create(std::string&& table_name, std::vector<std::vector<std::string>>& columns);

    // ɾ����
    bool drop();

    // ��������
    bool insert(std::vector<std::string>& values);

    // ɾ������
    bool drop(std::string& key);
    bool drop(std::string&& key);

    // ��������
    bool update(std::string& key, std::vector<std::string>& values);
    bool update(std::string&& key, std::vector<std::string>& values);

    // ѡ������
    bool select(std::string& key, std::vector<std::string>& values);
    bool select(std::string&& key, std::vector<std::string>& values);

    // ��ӡ����
    bool show();
    bool show(std::string& key);
    bool show(std::string&& key);

private:
    Table();
    ~Table();
    // ��ֹ�����͸�ֵ
    void operator=(const Table& table) = delete;
    Table(const Table& table) = delete;
private:
    // ��ǰ����
    unsigned char key_column;
    // �ж������Ƿ��޸�
    bool dirty;
	// �жϱ��Ƿ����
    bool exist;
    std::vector<DataPage*> pages;
};

#endif // TABLE_H