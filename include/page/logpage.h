#ifndef LOGPAGE_H
#define LOGPAGE_H

#include "define/define.h"
#include <vector>
#include <string>
#include <string_view>

class LogPage
{
    public:
    // ��������ҳ
    static LogPage * instance();

    // �����
    int8_t add(std::string &column_name);
    int8_t add(std::string &&column_name);
    int8_t add(std::string_view column_name);

    // ɾ����
    int8_t drop(int8_t order);

    // ��ȡ����
    int8_t read();

    // д������
    int8_t write();

private:
    LogPage();
    ~LogPage();
    // ��д��ֵ�����
    void operator=(const LogPage &data_page) = delete;
    LogPage(const LogPage &data_page) = delete;
private:
    // ����ҳ�Ƿ���ҳ
    int8_t dirty;
    // ����
    static LogPage * log_page;
    // ��־��Ϣ
    std::vector<std::string> logs;
};

#endif // LOGPAGE_H