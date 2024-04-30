#pragma once

#include <string>

class HotelRoom
{
private:
	std::string hotel_room_number;
	int number_of_beds;
	int number_of_rooms;
	bool bathroom_is_included;
	std::string equipment;
public:
	bool operator < (const HotelRoom& other)
	{
		return hotel_room_number < other.hotel_room_number;
	}
};

