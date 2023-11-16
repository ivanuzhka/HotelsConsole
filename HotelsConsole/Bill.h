#pragma once

#include "Room.h"
#include "RoomType.h"

class Bill
{
public:
	//Bill(RoomType* room_type, Room room)
	//	: _room_type(room_type)
	//	, _room_number(room.get_room_number())
	//	, _arrival_day(room.get_arrival_day())
	//	, _departure_day(room.get_departure_day())
	//	, _price(room.get_price())
	//	, _discount(room.get_discount())
	//	, _paid(room.get_paid())
	//	, _book_id(room.get_book_id()) {}

private:
	RoomType* _room_type;
	int _room_number;
	int _arrival_day;
	int _departure_day;
	int _price;
	int _discount;
	int _paid;
	int _book_id;
};

