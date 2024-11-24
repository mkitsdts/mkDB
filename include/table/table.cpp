#include "table.h"
#include <fstream>

Table::Table() : key_column(0), dirty(0), exist(0)
{
}

Table::~Table()
{
}

Table* Table::read(std::string& table_name)
{
	std::ifstream file;
	file.open(table_name, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		return nullptr;
	}
}