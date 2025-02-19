#pragma once

#include "tuple/tupledecs.h"

namespace mkDB
{

// 元组，即单条数据
class Tuple
{
  public:
    TupleDecs &tuple_decs()
    {
        return tupledecs;
    }
    RecordId &record_id()
    {
        return rid;
    }

    void set_record_id(RecordId id)
    {
        rid = id;
    }

    void reset_tuple_decs(TupleDecs &decs)
    {
        tupledecs = decs;
    }

    static void merge(Tuple &tuple1, Tuple &tuple2)
    {
        tuple1.fields.insert(tuple1.fields.end(), tuple2.fields.begin(), tuple2.fields.end());
    }

  private:
    TupleDecs tupledecs;
    RecordId rid;
    std::vector<Field> fields;
};
} // namespace mkDB