#include "page/table.h"

void insert_data(Table &data_table)
{
    data_table.insert({"1", "zhangsan"});
    data_table.insert({"2", "lisi"});
    data_table.insert({"3", "wangwu"});
    data_table.insert({"4", "zhaoliu"});
    data_table.insert({"5", "sunqi"});
    data_table.insert({"6", "zhouba"});
    data_table.insert({"7", "wujiu"});
    data_table.insert({"8", "zhengshi"});
    data_table.insert({"9", "wangwu"});
    data_table.insert({"10", "zhaoliu"});
    data_table.insert({"11", "sunqi"});
    data_table.insert({"12", "zhouba"});
}

int main()
{
    auto data_table = Table::create("user_data",{{INT, "id", KEY, NOT_NULL}, {varchar, "name", NOT_KEY, NOT_NULL}});
    insert_data(data_table);
    data_table.save();
    data_table.show();
    data_table.drop();

}