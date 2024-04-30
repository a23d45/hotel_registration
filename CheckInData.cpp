#include "CheckInData.h"


CheckInData::CheckInData(
	std::string guest_passport_number, std::string hotel_room_number,
	std::string check_in_date, std::string date_eviction
)
{
	this->guest_passport_number = guest_passport_number;
	this->hotel_room_number = hotel_room_number;
	this->check_in_date = check_in_date;
	this->date_eviction = date_eviction;
}
