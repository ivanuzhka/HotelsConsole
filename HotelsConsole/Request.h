#pragma once

#include "RoomType.h"
#include "string"

class Request
{
public:
	Request() = default;

	Request(std::string request_type
		, int creation_day
		, int creation_time
		, RoomType* room_type
		, int arrival_day
		, int departure_day)

		: Request(request_type
			, -1
			, creation_day
			, creation_time
			, -1
			, room_type
			, -1
			, arrival_day
			, departure_day) {}
	
	Request(std::string request_type
		, int id
		, int creation_day
		, int creation_time
		, int final_price
		, RoomType* room_type
		, int room_number
		, int arrival_day
		, int departure_day)

		: _request_type(request_type)
		, _id(id)
		, _creation_day(creation_day)
		, _creation_time(creation_time)
		, _final_price(final_price)
		, _room_type(room_type)
		, _room_number(room_number)
		, _arrival_day(arrival_day)
		, _departure_day(departure_day) {}

	std::string get_request_type() { return _request_type; }
	int get_id() const { return _id; }
	int get_creation_day() const { return _creation_day; }
	int get_creation_time() const { return _creation_time; }
	int get_final_price() const { return _final_price; }
	std::string get_room_type_title() const { return _room_type->get_title(); }
	int get_room_number() const { return _room_number; }
	int get_arrival_day() const { return _arrival_day; }
	int get_departure_day() const { return _departure_day; }
	int get_room_price() const { return _room_type->get_price(); }
	RoomType* get_room_type() const { return _room_type; }

	int set_id(int id) { return _id = id; }
	RoomType* set_room_type(RoomType* new_room_type) { return _room_type = new_room_type; }
	int set_final_price(int final_price) { return _final_price = final_price; }
	int set_room_number(int room_number) { return _room_number = room_number; }

private:
	std::string _request_type;
	int _id;
	int _creation_day;
	int _creation_time;
	int _final_price;
	RoomType* _room_type;
	int _room_number;
	int _arrival_day;
	int _departure_day;
};

class Book : public Request
{
public:
	Book(int id
		, int creation_day
		, int creation_time
		, int final_price
		, RoomType* room_type
		, int room_number
		, int arrival_day
		, int departure_day)

		: Request("book"
			, id, creation_day
			, creation_time
			, final_price
			, room_type
			, room_number
			, arrival_day
			, departure_day) {}
};

class Arrive : public Request
{
public:
	Arrive(int id
		, int creation_day
		, int creation_time
		, int final_price
		, RoomType* room_type
		, int room_number
		, int arrival_day
		, int departure_day)

		: Request("arrive"
			, id, creation_day
			, creation_time
			, final_price
			, room_type
			, room_number
			, arrival_day
			, departure_day) {}
};
