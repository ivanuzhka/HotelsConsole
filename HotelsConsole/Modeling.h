#pragma once

#include "System.h"

#include <random>
#include <ctime>

class Modeling
{
public:
	Modeling() = default;

	Modeling(int period
		, int min_interval
		, int max_interval
		, std::array<int, 5> sizes
		, std::array<int, 5> prices
		, std::array<int, 5> discounts)

		: _period(period)
		, _min_interval(min_interval)
		, _max_interval(max_interval)
		, _current_request_number(0)
	{
		_types = 
		{
			new Lux(prices[0], discounts[0])
			, new SemiLux(prices[1], discounts[1])
			, new Single(prices[2], discounts[2])
			, new Double(prices[3], discounts[3])
			, new DoublePro(prices[4], discounts[4])
		};

		_num_to_type =
		{
			{ _types[0], 0 }
			, { _types[1], 1 }
			, { _types[2], 2 }
			, { _types[3], 3 }
			, { _types[4], 4 }
		};

		std::map<RoomType*, int> type_sizes;

		for (int i = 0; i < 5; ++i)
		{
			type_sizes.insert({ _types[i], sizes[i] });
		}

		_system = System(type_sizes);

		_all_requests = generate_requests();

		for (auto& room_type : _types)
		{
			_daily_occupancy[room_type] = { 0 };
		}
	}

	int get_day() const { return _system.get_current_day(); }
	int get_time() const { return _system.get_current_time(); }

	int get_cnt_book() const { return _system.get_book_counter(); }
	int get_cnt_arrive() const { return _system.get_arrive_counter(); }
	int revenue() const { return _system.get_revenue(); }
	int get_cnt_refuse() const { return _system.get_refuse_counter(); }

	// make a step in time_step hours and processes the requests in this time interval
	std::vector<Request*> do_step(int time_step);

	// processes the first successfully processed request
	Request* to_next_request();

	// update day & time, returns _daily_departure_list ans clears it
	std::vector<Request*> get_actions();

	// returns _daily_statistics and clears it
	std::array<std::pair<int, int>, 5> get_day_staticstic();

	// returns rooms
	std::array<std::vector<Room>, 5> get_information_rooms();

	std::array<std::vector<int>, 5> get_occupancy();

private:
	// processes the request by interacting with _system;
	Request* process_request(Request* request);

	std::vector<Request*> generate_requests();

	void process_daily_check_in();
	void process_daily_depart();

private:
	std::vector<Request*> _all_requests;
	std::vector<Request*> _daily_departure_list;
	std::map<RoomType*, std::pair<int, int>> _daily_statistic;
	std::map<RoomType*, std::vector<int>> _daily_occupancy;
	int _current_request_number;

	System _system;
	int _period;
	int _min_interval;
	int _max_interval;
	std::array<RoomType*, 5> _types;
	std::map<RoomType*, int> _num_to_type;
};

