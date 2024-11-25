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
    // ��������ҳ
    static DataPage* create(unsigned char order);

    // �����
    void add_column(char type, std::string &column_name, char is_key = NOT_KEY, char is_null = ALLOW_NULL);
    void add_column(char type, std::string &&column_name, char is_key = NOT_KEY, char is_null = ALLOW_NULL);

    // ɾ����
    bool drop_column(std::string &column_name);
    bool drop_column(std::string &&column_name);

    // ѡ����
    bool select_column(std::string &column_name);
    bool select_column(std::string &&column_name);
    bool select_column(unsigned char column_order);

    // ��ȡ����
    bool read(int page_order);

    // д������
    bool write();

private:

    DataPage();
    ~DataPage();
    // ��������
    bool parse_data();
    // ���뻺����
    bool add_to_buffer();
    // ��д��ֵ�����
    void operator=(const DataPage &data_page) = delete;
    DataPage(const DataPage &data_page) = delete;

protected:
    // ����
    char buffer[4096];
    // ����ҳ�Ƿ���ҳ
    bool dirty;
    // ���������
    unsigned char key_column;
    // ��ǰ��
    unsigned char current_column;
    // ����
    unsigned int column_count;
    // �ļ�ͷ
    file_header header;
    // �ļ�β
    file_tailer tailer;
    // ҳ��ͷ��¼
    page_header page_header;
    // ҳĿ¼
    page_directory directory;
    // ����Ϣ
    std::vector<column_information> columns;
    // ����Ϣ
    std::unordered_map<int,user_records> data;
};

#endif // DATAPAGE_H