#include "database/database.h"
#include "database.h"
#include <mutex>

mkDB::Database *mkDB::Database::instance()
{
    std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);
    if (mkDB == nullptr)
    {
        mkDB = new Database();
    }
    return mkDB;
}

void mkDB::Database::log_file(std::string &file_name)
{
}

mkDB::Database::~Database()
{
}

mkDB::Database::Database()
{
}
