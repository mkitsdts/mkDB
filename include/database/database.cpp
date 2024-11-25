#include "database.h"
#include <iostream>

Database::Database() : current_table("")
{
}

Database::~Database()
{
}

Database* Database::instance()
{
	static Database database;
	return &database;
}

bool Database::create_table(std::string& table_name, std::vector<std::vector<std::string>>& columns)
{
	if (tables.find(table_name) != tables.end())
	{
		std::cout << "table " << table_name << " already exists" << "\n";
		return false;
	}
	else if (columns.size() == 0)
	{
		std::cout << "Data is illegaled" << "\n";
		return false;
	}
	auto table = Table::create(table_name,columns);
	tables[table_name] = table;
	return true;
}

bool Database::create_table(std::string&& table_name, std::vector<std::vector<std::string>>& columns)
{
	if (tables.find(table_name) != tables.end())
	{
		std::cout << "table " << table_name << " already exists" << "\n";
		return false;
	}
	else if (columns.size() == 0)
	{
		std::cout << "Data is illegaled" << "\n";
		return false;
	}
	auto table = Table::create(table_name, columns);
	tables[table_name] = table;
	return true;
}

bool Database::drop_table(std::string& table_name)
{
	if (tables.find(table_name) == tables.end())
	{
		std::cout << "table " << table_name << " not exists" << "\n";
		return false;
	}
	tables.erase(table_name);
	return true;
}

bool Database::drop_table(std::string&& table_name)
{
	if (tables.find(table_name) == tables.end())
	{
		std::cout << "table " << table_name << " not exists" << "\n";
		return false;
	}
	tables.erase(table_name);
	return true;
}

bool Database::insert(std::vector<std::string>& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->insert(values);
}

bool Database::insert(std::vector<std::string>&& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->insert(values);
}

bool Database::use(std::string& table_name)
{
	if (tables.find(table_name) == tables.end())
	{
		std::cout << "table " << table_name << " not exists" << "\n";
		return false;
	}
	current_table = table_name;
	return true;
}

bool Database::use(std::string&& table_name)
{
	if (tables.find(table_name) == tables.end())
	{
		std::cout << "table " << table_name << " not exists" << "\n";
		return false;
	}
	current_table = table_name;
	return true;
}

bool Database::drop(std::string& key)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->drop(key);
}

bool Database::drop(std::string&& key)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->drop(key);
}

bool Database::update(std::string& key, std::vector<std::string>& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->update(key, values);
}

bool Database::update(std::string&& key, std::vector<std::string>& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->update(key, values);
}

bool Database::select(std::string& key, std::vector<std::string>& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->select(key, values);
}

bool Database::select(std::string&& key, std::vector<std::string>& values)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->select(key, values);
}

bool Database::show()
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->show();
}

bool Database::show(std::string& key)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->show(key);
}

bool Database::show(std::string&& key)
{
	if (current_table == "")
	{
		std::cout << "Please select a table first" << "\n";
		return false;
	}
	if (tables.find(current_table) == tables.end())
	{
		std::cout << "table " << current_table << " not exists" << "\n";
		return false;
	}
	return tables[current_table]->show(key);
}
