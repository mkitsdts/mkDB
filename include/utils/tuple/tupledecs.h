#pragma once

#include "utils/define/define.h"
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace mkDB
{

class FieldType
{
  public:
    FieldType(Type type) : type_(type)
    {
    }
    std::string to_string()
    {
        switch (type_)
        {
        case Type::INT:
            return "int";
        case Type::FLOAT:
            return "float";
        case Type::VARCHAR:
            return "varchar";
        case Type::DATE:
            return "date";
        default:
            throw std::runtime_error("unknown type");
        }
    }

    std::size_t size()
    {
        switch (type_)
        {
        case Type::INT:
            return sizeof(int);
        case Type::FLOAT:
            return sizeof(float);
        case Type::VARCHAR:
            return 255;
        case Type::DATE:
            return 4;
        default:
            throw std::runtime_error("unknown type");
        }
    }

  private:
    Type type_;
};

// 描述元组信息
class TupleDecs
{
  public:
    struct TupleDecsItem
    {
        std::string field_name;
        FieldType field_type;
        TupleDecsItem(FieldType type, std::string name) : field_type(type), field_name(name)
        {
        }

        std::string to_string()
        {
            return field_name + "(" + field_type.to_string() + ")";
        }
    };

    TupleDecs(std::vector<FieldType> type, std::vector<std::string> name)
    {
        if (type.size() != name.size())
        {
            throw std::runtime_error("type size not equal to name size");
        }
        for (size_t index = 0; index < type.size(); ++index)
        {
            items_.push_back(TupleDecsItem(type[index], name[index]));
        }
    }

    std::vector<TupleDecsItem>::iterator iterator()
    {
        return items_.begin();
    }

  private:
    std::vector<TupleDecsItem> items_;
    int record_id_;
};
}