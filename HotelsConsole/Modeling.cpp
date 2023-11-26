#include "Modeling.h"
#include <iostream>

std::mt19937 rnd(time(0));

std::vector<Request*> Modeling::do_step(int time_step)
{
	std::vector<Request*> processed_requests;

	int start = _system.get_current_time();
	int end = start + time_step;

	for (auto& request : _all_requests)
	{
		if (request->get_creation_day() != _system.get_current_day()
			|| request->get_creation_time() < start
			|| request->get_creation_time() > end) continue;

		++_current_request_number;

		// daily check-in
		if (request->get_creation_time() > 12 && _system.get_current_time() <= 12)
		{
			process_daily_check_in();
		}

		// daily depart
		if (request->get_creation_time() > 14 && _system.get_current_time() <= 14)
		{
			process_daily_depart();
		}


		_system.set_time(request->get_creation_time());
		if (process_request(request) == nullptr) continue;
		processed_requests.push_back(request);
	}

	// daily check-in
	if (end > 12 && _system.get_current_time() <= 12)
	{
		process_daily_check_in();
	}

	// daily depart
	if (end > 14 && _system.get_current_time() <= 14)
	{
		process_daily_depart();
	}

	_system.set_time(end);

	return processed_requests;
}

Request* Modeling::to_next_request()
{
	for (; _current_request_number < _all_requests.size(); ++_current_request_number)
	{
		auto request = _all_requests[_current_request_number];

		if (request->get_creation_day() != _system.get_current_day())
		{
			// layered to next day
			_system.set_time(24);
			return nullptr;
		}

		// daily check-in
		if (request->get_creation_time() > 12 && _system.get_current_time() <= 12)
		{
			process_daily_check_in();
		}

		// daily_depart
		if (request->get_creation_time() > 14 && _system.get_current_time() <= 14)
		{
			process_daily_depart();
		}

		Request* processed_request = process_request(request);
		_system.set_time(request->get_creation_time());

		if (processed_request != nullptr)
		{
			++_current_request_number;
			return request;
		}
	}

	_system.set_time(24);
	return nullptr;
}

std::vector<Request*> Modeling::get_actions()
{
	_system.update_date();
	_system.set_time(0);

	std::vector<Request*> tmp = _daily_departure_list;
	_daily_departure_list.clear();

	for (auto& [room_type, mass] : _daily_occupancy)
	{
		int previous = mass.back();
		mass.push_back(previous);
	}

	return tmp;
}

std::array<std::pair<int, int>, 5> Modeling::get_day_statistic()
{
	std::array<std::pair<int, int>, 5> result;

	for (auto& [room_type, statistic] : _daily_statistic)
	{
		result[_num_to_type[room_type]] = statistic;
	}
	_daily_statistic.clear();

	return result;
}

std::array<std::vector<Room>, 5> Modeling::get_information_rooms()
{
	std::array<std::vector<Room>, 5> result;

	for (auto& [room_type, el] : _system.get_occupancy())
	{
		result[_num_to_type[room_type]] = el;
	}

	return result;
}

std::array<std::vector<int>, 5> Modeling::get_occupancy()
{
	std::array<std::vector<int>, 5> result;

	for (auto& [room_type, el] : _daily_occupancy)
	{
		result[_num_to_type[room_type]] = el;
	}

	return result;
}



Request* Modeling::process_request(Request* request)
{
	auto [free_room_type, discount] = _system.get_free_type(request);

	if (free_room_type == nullptr) return nullptr;

	if (*free_room_type != *request->get_room_type() && rnd() % 2 == 0)
	{
		free_room_type = nullptr;
		discount = -1;
	}

	_system.confirm_request(request, free_room_type, discount);

	if (free_room_type != nullptr && request->get_request_type() == "arrive")
	{
		++_daily_statistic[request->get_room_type()].first;
		++_daily_occupancy[request->get_room_type()].back();
	}

	return free_room_type == nullptr ? nullptr : request;
}


std::vector<Request*> Modeling::generate_requests()
{
	std::vector<Request*> reqs;
	int now_day = 1;
	int now_time = rnd() % _max_interval;

	while (now_time + (now_day - 1) * 24 < (_period - 1) * 24)
	{
		RoomType* room_type = _types[rnd() % 5];
		bool bid_type = rnd() % 2;
		int departure_day, arrival_day;
		Request* q;

		if (bid_type || now_day == _period - 1)
		{
			arrival_day = now_day;
			departure_day = rnd() % (_period - now_day) + now_day + 1;
			q = new Request("arrive", now_day, now_time, room_type, arrival_day, departure_day);
		}
		else
		{
			arrival_day = rnd() % (_period - now_day) + now_day + 1;
			if (arrival_day == _period) arrival_day--;
			departure_day = rnd() % (_period - arrival_day) + arrival_day + 1;
			q = new Request("book", now_day, now_time, room_type, arrival_day, departure_day);
		}

		reqs.push_back(q);
		int plus = rnd() % (_max_interval - _min_interval + 1) + _min_interval;
		now_day = now_day + (now_time + plus) / 24;
		now_time = (now_time + plus) % 24;
	}
	return reqs;
}


void Modeling::process_daily_check_in()
{

	for (auto& request : _system.daily_check_in())
	{
		++_daily_statistic[request->get_room_type()].first;
		++_daily_occupancy[request->get_room_type()].back();
	}
}

void Modeling::process_daily_depart()
{

	for (auto& request : _system.daily_depart())
	{
		++_daily_statistic[request->get_room_type()].second;
		--_daily_occupancy[request->get_room_type()].back();
		_daily_departure_list.push_back(request);
	}
}
