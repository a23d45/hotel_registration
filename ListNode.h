#pragma once

#include <string>
#include "CheckInData.h"

struct ListNode
{
	CheckInData* data;
	ListNode* next = nullptr;
	ListNode* previous = nullptr;
	ListNode(CheckInData* data);
};

