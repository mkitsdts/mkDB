#pragma once

#include "utils/define/define.h"
#include <unordered_map>
#include <unordered_set>
namespace mkDB
{
// 默认页大小
constexpr int DEFAULT_PAGE_SIZE = 4096;
constexpr int DEFAULT_PAGES = 50;
const int MAX_TIMEOUT = 1000;

class BufferPool
{
  public:
    BufferPool(int pages = DEFAULT_PAGES)
        : max_num_page(pages), page_size_(DEFAULT_PAGE_SIZE), pages(std::unordered_map<PageId, Page>{}),
          locks(std::unordered_map<PageId, Lock>{})
    {
    }

    struct SharedLock
    {
        std::unordered_set<TransactionId> shares;
        SharedLock(std::unordered_set<TransactionId> &transactions) : shares(transactions)
        {
        }
    };
    struct ExclusiveLock
    {
        TransactionId owner;
        ExclusiveLock(TransactionId &transaction) : owner(transaction)
        {
        }
    };

    int page_size();

    // 是否有锁
    bool has_lock(TransactionId &tid, PageId &pid);

    // 是否提交事务
    void transaction_complete(TransactionId &tid);
    void transaction_complete(TransactionId &tid, bool commit);

    // 添加页
    void insert_page(Page &p);
    // 保存需要修改的页
    void flush_page(PageId pid);
    void flush_pages(TransactionId tid);
    // 删除不需要修改的页
    void evict_page();
    // 移除页
    void remove_page(PageId pid);

    // 删除元数据
    void delete_tuple(TransactionId &tid, Tuple &t);
    // 插入元数据
    void insert_tuple(TransactionId &tid, int tableid, Tuple &t);

  private:
    int max_num_page;
    int page_size_;
    std::unordered_map<PageId, Page> pages;
    std::unordered_map<PageId, Lock> locks;
};
} // namespace mkDB