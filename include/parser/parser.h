#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace mkDB
{
class Parser
{
  public:
    static void parse(int argc, char *argv[]);

  private:
    Parser() = default;
    ~Parser() = default;
};
} // namespace mkDB