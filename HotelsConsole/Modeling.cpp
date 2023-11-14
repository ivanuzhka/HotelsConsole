#include "Modeling.h"

std::mt19937 rnd(time(0));

std::vector<Request*> Modeling::do_step(int time_step)
{
	std::vector<Request*> processed_requests;

	int start = _system.get_current_time();
	int end = start + time_step - 1;

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

		// daily deaprt
		if (request->get_creation_time() > 14 && _system.get_current_time() <= 14)
		{
			process_daily_depart();
		}

		_system.update_time(request->get_creation_time() - _system.get_current_time());
		process_request(request);
		processed_requests.push_back(request);
	}

	return processed_requests;
}

Request* Modeling::to_next_request()
{
	for (; _current_request_number < _all_requests.size(); ++_current_request_number)
	{
		auto request = _all_requests[_current_request_number];

		if (request->get_creation_day() != _system.get_current_time())
		{
			_system.set_time(request->get_creation_time());
			return nullptr;
		}

		//daily check-in
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
			if (++_current_request_number == _all_requests.size())
			{
				_system.set_time(24);
			}
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

std::array<std::pair<int, int>, 5> Modeling::get_day_staticstic()
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

	if (*free_room_type != *request->get_room_type() && rnd() % 2 == 0)
	{
		free_room_type = nullptr;
		discount = -1;
	}

	_system.confirm_request(request, free_room_type, discount);

	return free_room_type == nullptr ? nullptr : request;
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
