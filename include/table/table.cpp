#include "table.h"
#include <fstream>
#include <iostream>

Table::Table() : key_column(0), dirty(0), exist(0)
{
}

Table::~Table()
{
}

// 获取b+树根节点所在的页
bool Table::read(std::string& table_name)
{
	std::ifstream file;
	file.open(PAGE_PATH, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "open file failed" << std::endl;
		return false;
	}
	auto page = DataPage::create(ROOT);
	if (!page)
	{
		std::cout << "create page failed" << std::endl;
		return false;
	}
	pages.push_back(page);
}

bool Table::read(std::string&& table_name)
{
	std::ifstream file;
	file.open(PAGE_PATH, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "open file failed" << std::endl;
		return false;
	}
	auto page = DataPage::create(ROOT);
	if (!page)
	{
		std::cout << "create page failed" << std::endl;
		return false;
	}
	pages.push_back(page);
}

bool Table::save()
{

	return false;
}

Table* Table::create()
{
	return nullptr;
}

Table* Table::create(std::string& table_name, std::vector<std::vector<std::string>>& columns)
{
	return nullptr;
}

Table* Table::create(std::string&& table_name, std::vector<std::vector<std::string>>& columns)
{
	return nullptr;
}

bool Table::drop()
{
	return false;
}

bool Table::insert(std::vector<std::string>& values)
{
	dirty = true;

	return false;
}

bool Table::drop(std::string& key)
{
	return false;
}

bool Table::drop(std::string&& key)
{
	return false;
}

bool Table::update(std::string& key, std::vector<std::string>& values)
{
	return false;
}

bool Table::update(std::string&& key, std::vector<std::string>& values)
{
	return false;
}

bool Table::select(std::string& key, std::vector<std::string>& values)
{
	return false;
}

bool Table::select(std::string&& key, std::vector<std::string>& values)
{
	return false;
}

bool Table::show()
{
	return false;
}

bool Table::show(std::string& key)
{
	return false;
}

bool Table::show(std::string&& key)
{
	return false;
}