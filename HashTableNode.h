#pragma once

#include <string>


template <typename T>
struct Node
{
	T* value;
	std::string key;
	bool is_empty;
	bool is_deleted;
	Node();
	Node(T* value);
};

template <typename T>
Node<T>::Node(T* value)
{
	this->value = value;
	is_empty = true;
	is_deleted = false;
	key = "";
}

template <typename T>
Node<T>::Node() : value(nullptr), is_empty(true), is_deleted(false), key("") {};

