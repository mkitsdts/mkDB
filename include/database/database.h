#pragma once

#include "buffer/bufferpool.h"
#include "catelog/catelog.h"
#include "utils/file/logfile.h"

namespace mkDB
{
const std::string MKDATABASE_PATH = "mkdb";
const std::string MKDATABASE_LOG = "mkdb.log";

class Database
{
  public:
    static Database *instance();

    void reset();

    Catelog catelog();

    BufferPool buffer_pool();

    LogFile log_file();

    static Database *mkDB;

  private:
    Database();
    ~Database();

  private:
    BufferPool buffer_pool_;
    Catelog catelog_;
    LogFile log_file_;
};

Database *Database::mkDB = nullptr;

} // namespace mkDB