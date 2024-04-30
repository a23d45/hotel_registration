#pragma once
#include "ListNode.h"
#include "CheckInData.h"

class List
{
private:
	ListNode* first;
	ListNode* last;
public:
	List();
	void append(CheckInData* data);
	CheckInData* getByIndex(const int index);
	CheckInData* operator [] (const int index);
};

