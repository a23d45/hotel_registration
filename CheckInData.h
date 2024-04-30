#pragma once

#include <string>

class CheckInData
{
private:
	std::string guest_passport_number;
	std::string hotel_room_number;
	std::string check_in_date;
	std::string date_eviction;
public:
	CheckInData(
		std::string guest_passport_number, std::string hotel_room_number,
		std::string check_in_date, std::string date_eviction
	);
};


