#include "database.h"

Database::Database()
{
}

Database::~Database()
{
}

bool Database::create_table(const std::string& table_name, std::vector<std::vector<std::string>>& columns)
{
	return false;
}

bool Database::create_table(const std::string&& table_name, std::vector<std::vector<std::string>>& columns)
{
	return false;
}

bool Database::drop_table(const std::string& table_name)
{
	return false;
}

bool Database::drop_table(const std::string&& table_name)
{
	return false;
}

bool Database::insert(std::vector<std::string>& values)
{
	return false;
}

bool Database::insert(std::vector<std::string>&& values)
{
	return false;
}

bool Database::use(const std::string& table_name)
{
	return false;
}

bool Database::use(const std::string&& table_name)
{
	return false;
}

bool Database::drop(std::string& key)
{
	return false;
}

bool Database::drop(std::string&& key)
{
	return false;
}

bool Database::update(std::string& key, std::vector<std::string>& values)
{
	return false;
}

bool Database::update(std::string&& key, std::vector<std::string>& values)
{
	return false;
}

bool Database::select(std::string& key, std::vector<std::string>& values)
{
	return false;
}

bool Database::select(std::string&& key, std::vector<std::string>& values)
{
	return false;
}

bool Database::show()
{
	return false;
}

bool Database::show(std::string& key)
{
	return false;
}

bool Database::show(std::string&& key)
{
	return false;
}
