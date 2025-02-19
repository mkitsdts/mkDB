#pragma once

#include "utils/define/define.h"
#include "utils/tuple/tuple.h"
#include <map>

/*
 * 数据库目录
 * 包含列信息，数据信息
 * 快速定位找到对应表
 */
namespace mkDB
{
class Catelog
{
  public:
    Catelog() = default;
    ~Catelog() = default;
    // 表信息
    struct Table
    {
        Table(DBFile file, std::string name, std::string primary_key_field)
            : file(file), name(name), primary_key_field(primary_key_field)
        {
        }
        DBFile file;
        std::string name;
        std::string primary_key_field;
    };

    void create_table(DBFile file, std::string name, std::string primary_key_field);
    void create_table(DBFile file, std::string name);
    void create_table(DBFile file);

    DBFile table(int tebleid);
    int table_id(std::string name);
    TupleDecs tuple_decs(int table_id);
    std::string table_name(int table_id);
    std::string primary_key(int tableid);

  private:
    std::map<std::string, int> table_map;
    std::map<int, Table> tables;
};
} // namespace mkDB