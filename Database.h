#pragma once

#include "sqlite3.h"
#include <iostream>

#include <string>

using namespace std;

class Database
{
private:
	static const char* DEFAULT_PATH;
	const char* path;
	sqlite3* database;
public:
	Database(const char* path = Database::DEFAULT_PATH);
	void createTables();
	~Database();
};

