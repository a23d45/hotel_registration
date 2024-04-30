#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Guest.h"
#include "HashTableNode.h"


using namespace std;

const string FILENAME_FOR_IMPORT = "file1.txt";
const string FILENAME_FOR_EXPORT = "file2.txt";

template <typename T>
class HashTable
{
private:
	static const int NUMBER_OF_SEGMENTS = 2000;
	Node<T>* table[NUMBER_OF_SEGMENTS] = { nullptr };
	string key_format;
	int count_elements;
	int hashFunction(const string key) const;
	int linearTesting(const int hash, const string key, const int step = 1);
	int quadraticTesting(
		const int hash, 
		const string key, 
		const int linear_coefficient = 1,
		const int quadratic_coefficient = 2
	);
	int searchElement(
		const string key,
		const bool print_collisions = false,
		const int step = 1
	) const;
	bool isEmptySegment(int segment) const;
	bool isDeletedSegment(int segment) const;
public:
	HashTable(const string key_format = KEY_FORMAT);
	~HashTable();
	bool isCorrectKey(const string key) const;
	void insert(const string key, const T value);
	void deleteByKey(const string key);
	Node<T>* getElementByKey(const string key) const;
	void writeToFile(const string filename = FILENAME_FOR_EXPORT) const;
	void printAll() const;
	string getKeyFormat() const;
	void fillTableFromTheFile(const string filename = FILENAME_FOR_IMPORT);
};


template <typename T>
HashTable<T>::HashTable(string key_format)
{
	this->key_format = key_format;
	count_elements = 0;
}

template <typename T>
HashTable<T>::~HashTable()
{
	for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
	{
		if (table[i] != nullptr)
		{
			delete table[i];
		}
	}
}

template <typename T>
int HashTable<T>::hashFunction(const string key) const
{
	int hash = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hash += (key[i] * key[i]);
	}
	hash = hash % NUMBER_OF_SEGMENTS;
	return hash;
}

template<typename T>
int HashTable<T>::linearTesting(const int hash, const string key, const int step)
{
	// Возвращает свободный адрес, используя метод линейного опробования
	int i = 0;
	int cyclic_shift = 0;
	int address = hash + step * i;
	while (!isEmptySegment(address) || isDeletedSegment(address))
	{
		if (cyclic_shift == NUMBER_OF_SEGMENTS)
		{
			return -1;
		}
		cout << endl;

		if (table[address]->key == key)
		{
			return -2;
		}
		if (address >= NUMBER_OF_SEGMENTS)
		{
			address = cyclic_shift++;
			i = 0;
		}
		else
		{
			i++;
			address = cyclic_shift + hash + step * i;
		}

	}
	return address;
}

template<typename T>
int HashTable<T>::quadraticTesting(
	const int hash, 
	const string key, 
	const int linear_coefficient, 
	const int quadratic_coefficient
)
{
	int i = 0;
	int cyclic_shift = 0;
	int address = hash + linear_coefficient * i + quadratic_coefficient * i * i;
	while (!isEmptySegment(address) || isDeletedSegment(address))
	{
		if (cyclic_shift == NUMBER_OF_SEGMENTS)
		{
			return -1; // хеш-таблица заполнилась полностью
		}
		cout << endl;

		if (table[address]->key == key)
		{
			return -2;
		}
		if (address >= NUMBER_OF_SEGMENTS)
		{
			address = cyclic_shift++;
			i = 0;
		}
		else
		{
			i++;
			address = hash + linear_coefficient * i + quadratic_coefficient * i * i;
		}

	}
	return address;
}

template <typename T>
int HashTable<T>::searchElement(
	const string key,
	const bool print_collisions,
	const int step
) const
{
	int hash = hashFunction(key);
	int i = 0;
	int cyclic_shift = 0;
	int address = hash;
	if (print_collisions)
	{
		cout << "Коллизии: ";
	}
	int count_collisions = 0;
	while (!isEmptySegment(address) || isDeletedSegment(address))
	{
		if (table[address]->key == key)
		{
			if (print_collisions && count_collisions == 0)
			{
				cout << "Не обнаружено!" << endl;
			}
			else
			{
				cout << endl;
			}
			return address;
		}
		if (print_collisions)
		{
			count_collisions++;
			cout << table[address]->key << " ";
		}
		if (cyclic_shift == NUMBER_OF_SEGMENTS)
		{
			return -1;
		}
		if (address >= NUMBER_OF_SEGMENTS)
		{
			address = cyclic_shift++;
			i = 0;
		}
		else
		{
			i++;
			address = cyclic_shift + hash + step * i;
		}

	}
	if (print_collisions)
	{
		cout << "Не обнаружено!" << endl;
	}
	return -1;
}

template <typename T>
bool HashTable<T>::isCorrectKey(const string key) const
{
	// NNNN-NNNNNN
	if (key.length() != key_format.length())
	{
		return false;
	}
	for (int i = 0; i < key.length(); i++)
	{
		if (key_format[i] == 'N')
		{
			if (key[i] < 48 || key[i] > 57)
			{
				return false;
			}
		}
		else if (!(i == 4 && key_format[i] == '-'))
		{ 
			return false;
		}
		else 
		{
			return false;
		}
	}
	return true;
}


template <typename T>
void HashTable<T>::insert(const string key, const T value)
{
	if (!isCorrectKey(key))
	{
		return;
		cout << "Ключ не совпадает с заданным форматом!" << endl;
	}
	if (count_elements == NUMBER_OF_SEGMENTS)
	{
		cout << "Ошибка! Хеш-таблица заполнена!" << endl;
		return;
	}
	Node<T>* element = new Node<T>(value);
	element->is_empty = false;
	element->key = key;
	int hash = hashFunction(key);
	if (!isEmptySegment(hash)) // коллизия
	{
		hash = quadraticTesting(hash, key);
	}
	if (hash == -2)
	{
		cout << "Ошибка! Данный ключ уже есть в хеш-таблице!" << endl;
		return;
	}
	cout << "Значение сохранено в хеш-таблице!" << endl;
	table[hash] = element;
	count_elements++;
}

template <typename T>
Node<T>* HashTable<T>::getElementByKey(const string key) const
{
	int hash = searchElement(key);
	if (hash == -1)
	{
		return nullptr;
	}
	return table[hash];
}

template <typename T>
void HashTable<T>::deleteByKey(const string key)
{
	int hash = searchElement(key, true);
	if (hash == -1)
	{
		cout << "Ошибка! Данный ключ не существует!" << endl;
		return;
	}
	table[hash]->key = "";
	table[hash]->is_deleted = true;
	table[hash]->is_empty = true;
	count_elements--;
}

template <typename T>
void HashTable<T>::writeToFile(const string filename) const
{
	ofstream file;
	file.open(filename);
	if (file.is_open())
	{
		for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
		{
			if (isEmptySegment(i))
			{
				continue;
			}
			file << table[i]->key << " " << table[i]->value << endl;
		}
		file.close();
		cout << "Запись в файл " << filename << " завершена!" << endl;
		return;
	}

	cout << "Ошибка при открытии файла!" << endl;
}


template <typename T>
void HashTable<T>::printAll() const
{
	cout << "Содержимое хеш-таблицы: ";
	if (count_elements == 0)
	{
		cout << "Пусто!" << endl;
		return;
	}
	cout << "\nКлюч      Значение\n";
	for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
	{
		if (!isEmptySegment(i))
		{
			cout << table[i]->key << "    " << table[i]->value << endl;
		}
	}
}

template <typename T>
string HashTable<T>::getKeyFormat() const
{
	return key_format;
}

template <typename T>
bool HashTable<T>::isEmptySegment(int segment) const
{
	if (table[segment] == nullptr || table[segment]->is_empty)
	{
		return true;
	}
	return false;
}

template <typename T>
bool HashTable<T>::isDeletedSegment(int segment) const
{
	if (table[segment] == nullptr)
	{
		return false;
	}
	if (table[segment]->is_deleted)
	{
		return true;
	}
	return false;
}

template <typename T>
void HashTable<T>::fillTableFromTheFile(const string filename)
{

	ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		string key;
		int value;
		while (!file.eof())
		{
			file >> key >> value;
			Node<T>* current_element = getElementByKey(key);
			if (current_element != nullptr)
			{
				deleteByKey(key);
			}
			insert(key, value);
		}
		file.close();
		cout << "Загрузка хеш-таблицы из файла завершена!" << endl;
		return;
	}

	cout << "Ошибка при открытии файла!" << endl;
}
