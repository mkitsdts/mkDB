#pragma once

#include "utils/define/define.h"
#include "utils/tuple/tuple.h"
#include <fstream>

namespace mkDB
{

class HeapFile : public DBFile
{
  public:
    HeapFile(std::fstream &file, TupleDecs tuple_decs);
    ~HeapFile() = default;
    Page read(PageId &id);
    void write(Page &page);
    void insert_tuple(TransactionId tid, Tuple &tuple);
    void delete_tuple(TransactionId tid, Tuple &tuple);
    int id();
    TupleDecs tuple_decs();
    std::fstream file();

  private:
    std::fstream file_;
    TupleDecs tuple_decs_;
};

} // namespace mkDB