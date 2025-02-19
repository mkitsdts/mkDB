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
    // ҳ��Ϣ
    HeapPageId pid;
    // ����id
    TupleDecs tuple_decs;
    // ����
    std::vector<Tuple> tuples;
    // ͷ��Ϣ
    std::vector<std::byte> header;
    // �ղ�����
    int slot_count;
    // ������
    std::vector<std::byte> old_data;
    // ��¼�޸���Ϣ������
    TransactionId dirty_tid;
    // ��֤һ���̲߳���old_data
    std::mutex data_mutex;
};
} // namespace mkDB