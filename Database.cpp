#include "Database.h"

const char* Database::DEFAULT_PATH = "../db.sqlite3";


Database::Database(const char* path)
{
	this->path = path;
	int result = sqlite3_open(path, &(this->database));
	if (result != 0)
	{
		throw exception(sqlite3_errmsg(database));
	}
}


Database::~Database()
{
	sqlite3_close(database);
}

void Database::createTables()
{
	const char* create_table_guests =
		"DROP TABLE IF EXISTS guests;"
		"CREATE TABLE guests("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"first_name TEXT,"
		"last_name TEXT,"
		"patronymic TEXT,"
		"passport_number TEXT UNIQUE,"
		"birth_year INTEGER,"
		"address TEXT,"
		"purpose_of_arrival TEXT)";

	const char* create_table_hotel_rooms =
		"DROP TABLE IF EXISTS hotel_rooms;"
		"CREATE TABLE hotel_rooms("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"number TEXT UNIQUE,"
		"number_of_beds INTEGER," // количество мест
		"number_of_rooms INTEGER,"
		"bathroom_included BOOLEAN"
		"equipment TEXT)";

	char* error_message;
	/*
	int result = 
		sqlite3_exec(this->database, create_table_guests, 0, 0, &error_message);
	if (result != SQLITE_OK)
	{
		throw exception(error_message);
	}*/
	int result =
		sqlite3_exec(this->database, create_table_hotel_rooms, 0, 0, &error_message);
	if (result != SQLITE_OK)
	{
		//throw exception(error_message);
		cout << error_message;
	}

}
