#include "utils/file/heapfile.h"
using namespace mkDB;

HeapFile::HeapFile(std::fstream &file, TupleDecs tuple_decs) : file_(file), tuple_decs_(tuple_decs)
{
}

Page HeapFile::read(PageId &id)
{
}