#ifndef LOGPAGE_H
#define LOGPAGE_H

#include "define/define.h"
#include <vector>
#include <string>
#include <string_view>

class LogPage
{
    public:
    // 创建数据页
    static LogPage * instance();

    // 添加列
    int8_t add(std::string &column_name);
    int8_t add(std::string &&column_name);
    int8_t add(std::string_view column_name);

    // 删除列
    int8_t drop(int8_t order);

    // 读取数据
    int8_t read();

    // 写入数据
    int8_t write();

private:
    LogPage();
    ~LogPage();
    // 重写赋值运算符
    void operator=(const LogPage &data_page) = delete;
    LogPage(const LogPage &data_page) = delete;
private:
    // 数据页是否脏页
    int8_t dirty;
    // 单例
    static LogPage * log_page;
    // 日志信息
    std::vector<std::string> logs;
};

#endif // LOGPAGE_H