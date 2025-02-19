#include "utils/page/heappage.h"
#include "heappage.h"
#include <fstream>
#include <sstream>

using namespace mkDB;

HeapPage::HeapPage(HeapPageId pageid, std::vector<std::byte> data) : pid(pageid)
{
    td =
}