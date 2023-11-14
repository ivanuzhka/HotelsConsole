#pragma once

#include "RoomType.h"

class Room
{
public:
	Room() : Room(-1) {}

	Room(int number)
		: _room_type(nullptr)
		, _room_number(number)
		, _now_price(-1)
		, _arrival_day(-1)
		, _departure_day(-1)
		, _book_id(-1) {}

	std::string get_room_type() const { return _room_type->get_title(); }
	int get_room_number() const { return _room_number; }
	int get_arrival_day() const { return _arrival_day; }
	int get_departure_day() const { return _departure_day; }
	int get_price() const { return _now_price; }
	int get_book_id() const { return _book_id; }
	int get_now_price() const { return _now_price; }


	bool is_busy() const { return _arrival_day != -1; }
	bool is_departure_day(int current_day) const { return _departure_day == current_day; }

	void clear() { Room(number); }

	void check_into(int book_id, RoomType* room_type, int arrival_day, int departure_day, int now_price)
	{
		_book_id = book_id;
		_room_type = room_type;
		_arrival_day = arrival_day;
		_departure_day = departure_day;
		_now_price = now_price;
	}

private:
	RoomType* _room_type;
	int _room_number;
	int _arrival_day;
	int _departure_day;	
	int _now_price;
	int _book_id;
};

