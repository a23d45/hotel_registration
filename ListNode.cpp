#include "ListNode.h"

ListNode::ListNode(CheckInData* data)
{
	this->data = data;
	next = previous = nullptr;
}
