#include "List.h"

List::List()
{
	first = last = nullptr;
}

void List::append(CheckInData* data)
{
	ListNode* new_last = new ListNode(data);
	new_last->previous = last;
	if (last != nullptr)
	{
		last->next = new_last;
	}
	if (first == nullptr)
	{
		first = new_last;
	}
	last = new_last;
}

CheckInData* List::getByIndex(const int index)
{
	int n = 0;
	ListNode* current_node = first;
	while (n != index)
	{
		if (current_node == nullptr)
		{
			return nullptr;
		}
		current_node = current_node->next;
	}
	return current_node->data;
}

CheckInData* List::operator [] (const int index)
{
	return getByIndex(index);
}

