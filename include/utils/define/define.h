#pragma once

#include <fstream>

namespace mkDB
{
// 锁
struct Lock
{
    virtual ~Lock() = default;
};

// 支持的数据类型
enum class Type
{
    INT,
    FLOAT,
    VARCHAR,
    DATE
};

// 列信息
struct Field
{
    virtual void serialize(std::fstream dos)
    {
    }
    virtual void to_string()
    {
    }
    virtual int hash()
    {
        return 0;
    }
    virtual bool operator==(Field &other) const
    {
        return false;
    }
    Type type()
    {
        return Type::INT;
    }
    virtual ~Field() = default;
};

// 页信息的基类
struct PageId
{
    virtual int id()
    {
        return 0;
    };
    virtual int hash()
    {
        return 0;
    };
    virtual int page_number()
    {
        return 0;
    };
    virtual bool operator==(PageId &other) const
    {
        return false;
    }
    virtual ~PageId() = default;
};

// 数据页 页信息
class HeapPageId : public PageId
{
  public:
    int id()
    {
        return table_id_;
    }

    int hash()
    {
        return table_id_ * 31 + page_number_;
    }

    int page_number()
    {
        return page_number_;
    }

    bool operator==(HeapPageId &other) const
    {
        return page_number_ == other.page_number() && table_id_ == other.id();
    }

  private:
    int page_number_;
    int table_id_;
};

// 对应某条数据的id
class RecordId
{
  public:
    RecordId(PageId id, int number) : pid(id), tuple_number_(number)
    {
    }

    bool operator==(RecordId &other) const
    {
        return pid == other.pid && tuple_number_ == other.tuple_number_;
    }

    int tuple_number()
    {
        return tuple_number_;
    }

    PageId page_id()
    {
        return pid;
    }

    int hash()
    {
        return pid.hash() * 31 + tuple_number_;
    }

    int id()
    {
        return pid.id();
    }

  private:
    PageId pid;
    int tuple_number_;
};

// 标记事务的id
struct TransactionId
{

    TransactionId()
    {
    }

    bool operator==(TransactionId &other) const
    {
        return my_id == other.my_id;
    }

    int id()
    {
        return my_id;
    }

    int hashCode()
    {
        int prime = 31;
        int result = 1;
        result = prime * result + (my_id ^ (my_id >> 32));
        return result;
    }

    std::string to_string()
    {
        return std::to_string(my_id);
    }

    int my_id;
    static std::atomic<int> counter_;
};

// 表对应文件结构
struct DBFile
{
    virtual void write(Page &page)
    {
    }

    virtual Page read(PageId &pid)
    {
        return Page{};
    }

    virtual void insert_tuple(TransactionId tid, Tuple &tuple)
    {
    }

    virtual void delete_tuple(TransactionId tid, Tuple &tuple)
    {
    }

    virtual int id()
    {
        return 0;
    }

    virtual TupleDecs tuple_decs()
    {
        return TupleDecs{{}, {}};
    }

    virtual std::fstream file()
    {
        return std::fstream{};
    }

    virtual ~DBFile() = default;
};

// 页信息
struct Page
{
    virtual PageId id()
    {
        return PageId{};
    };

    virtual TransactionId is_dirty()
    {
        return TransactionId{};
    };

    virtual void mark_dirty(bool dirty, TransactionId tid) {};

    virtual std::vector<std::byte> get_page_data()
    {
        return std::vector<std::byte>{};
    };

    virtual Page get_before_image()
    {
        return Page{};
    };

    virtual void set_before_image() {};
    virtual ~Page() = default;
};
} // namespace mkDB