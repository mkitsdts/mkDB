#pragma once

#include "utils/define/define.h"
#include "utils/tuple/tuple.h"
#include <mutex>
#include <vector>

namespace mkDB
{
class HeapPage : public Page
{
  public:
    HeapPage(HeapPageId pageid, std::vector<std::byte> data);

  private:
    // 页信息
    HeapPageId pid;
    // 事务id
    TupleDecs tuple_decs;
    // 数据
    std::vector<Tuple> tuples;
    // 头信息
    std::vector<std::byte> header;
    // 空槽数量
    int slot_count;
    // 旧数据
    std::vector<std::byte> old_data;
    // 记录修改信息的事务
    TransactionId dirty_tid;
    // 保证一个线程操作old_data
    std::mutex data_mutex;
};
} // namespace mkDB