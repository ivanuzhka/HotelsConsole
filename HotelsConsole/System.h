#pragma once

#include "RoomType.h"
#include "Room.h"
#include "TypeBooking.h"
#include "Bill.h"
#include "Request.h"

#include <map>
#include <vector>
#include <string>
#include <array>

class System
{
public:
	System() 
		: _current_day(1)
		, _current_time(0)
		, _book_counter(0)
		, _arrive_counter(0)
		, _refuse_counter(0)
		, _revenue(0) {}

	System(std::map<RoomType*, int> sizes) : System()
	{
		// creating _booking & _occupancy
		int counter = 1;
		for (auto& [room_type, size] : sizes)
		{
			_booking[room_type] = TypeBooking();
			for (int i = 0; i < size; ++i)
			{
				_occupancy[room_type].push_back(Room(counter++));
			}
		}
	}
	
	int update_date() { return ++_current_day; }
	int update_time(int time_step) { return _current_time += time_step; }
	int set_time(int time) { return _current_time = time; }

	int get_current_day() const { return _current_day; }
	int get_current_time() const { return _current_time; }

	int get_book_counter() const { return _book_counter; }
	int get_arrive_counter() const { return _arrive_counter; }
	int get_refuse_counter() const { return _refuse_counter; }
	int get_revenue() const { return _revenue; }

	std::map<RoomType*, std::vector<Room>> get_occupancy() const { return _occupancy; }


	// returns { type : discount }
	std::pair<RoomType*, int> get_free_type(Request* request);

	// returns pointer to request that have checked-in and nullptr otherwise
	Request* confirm_request(Request* request, RoomType* room_type, int discount);


	// checks-in booked requests in 12:00 every day
	std::vector<Request*> daily_check_in();

	// departs requests whose booking expired in 14:00 every day
	std::vector<Request*> daily_depart();


private:
	// returns ptr to request that have checked-in and nullptr otherwise
	Request* check_in(int book_id);

private:
	std::map<RoomType*, TypeBooking> _booking;
	std::map<RoomType*, std::vector<Room>> _occupancy;
	std::map<int, Request*> _base;

	int _current_day;
	int _current_time;

	int _counter;

	int _book_counter;
	int _arrive_counter;
	int _refuse_counter;
	int _revenue;

	std::vector<std::vector<int>> _daily_occupancy;
};

