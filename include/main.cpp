#include "database/database.h"
#include "parser/parser.h"
#include <iostream>
using namespace mkDB;

int main(int argc, char *argv[])
{
    if (argv[1] == "convert")
    {
        std::cout << "Usage: " << argv[0] << " <database file>" << std::endl;
    }
    else if (argv[1] == "parser")
    {
        Parser::parse(argc, argv);
        std::cout << "Usage: " << argv[0] << " <database file>" << std::endl;
    }
    else
    {
        std::cout << "Unknown commond: " << argv[0] << " <database file>" << std::endl;
    }
    return 0;
}