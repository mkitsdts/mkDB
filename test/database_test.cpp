#include "database/database.h"

int main()
{
    mkDb->create_table("test", {{"id", "int", "key"}, {"name", "varchar"}});
    mkDb->use("test");
    mkDb->insert({"1", "test"});
    mkDb->show();
    return 0;
}