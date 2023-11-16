#include "System.h"


Request* System::check_in(int book_id)
{
	Request* request = _base[book_id];

	for (auto& room : _occupancy[request->get_room_type()])
	{
		if (room.is_busy()) continue;

		request->set_room_number(room.get_room_number());

		room.check_into(book_id
			, request->get_room_type()
			, request->get_departure_day()
			, request->get_arrival_day()
			, request->get_final_price());

		return request;
	}

	return nullptr;
}

std::pair<RoomType*, int> System::get_free_type(Request* request)
{
	RoomType* lower_type = nullptr;
	RoomType* equal_type = nullptr;
	RoomType* upper_type = nullptr;

	for (auto& [room_type, type_booking] : _booking)
	{
		int counter = 0;
		for (auto& room : _occupancy[room_type])
		{
			if (!room.is_busy()) continue;
			type_booking.insert(room.get_book_id(), room.get_arrival_day(), room.get_departure_day());
			++counter;
		}

		if (type_booking.is_empty_rooms(request->get_arrival_day(), request->get_departure_day(), _occupancy.size()))
		{
			if (*room_type < *request->get_room_type() && (lower_type == nullptr || *lower_type < *room_type))
			{
				lower_type = room_type;
			}
			else if (*room_type == *request->get_room_type())
			{
				equal_type = room_type;
			}
			else if (upper_type == nullptr || *upper_type > *room_type)
			{
				upper_type = room_type;
				break;
			}
		}
	}

	if (equal_type != nullptr)
	{
		return { equal_type, 0 };
	}
	if (upper_type != nullptr)
	{
		return { upper_type, request->get_room_type()->get_discount() };
	}
	if (lower_type != nullptr)
	{
		return { lower_type, 0 };
	}
	return { nullptr, -1 };
}

Request* System::confirm_request(Request* request, RoomType* room_type, int discount)
{
	if (room_type == nullptr)
	{
		int book_id = std::stoi(std::to_string(_current_day)
			+ std::to_string(_current_time)
			+ std::to_string(_book_counter + _arrive_counter + ++_refuse_counter));

		request->set_id(book_id);
		_base[book_id] = request;

		return nullptr;
	}

	int book_id = std::stoi(std::to_string(_current_day)
		+ std::to_string(_current_time)
		+ std::to_string(_book_counter + _arrive_counter + _refuse_counter + 1));

	int final_price = (double)room_type->get_price() * (1. - (double)discount / 100.);

	request->set_id(book_id);
	request->set_room_type(room_type);
	request->set_final_price(final_price);

	_base[book_id] = request;

	if (request->get_request_type() == "book")
	{
		_booking[room_type].insert(book_id, request->get_arrival_day(), request->get_departure_day());
		++_book_counter;
	}
	else
	{
		check_in(book_id);
		++_arrive_counter;
	}

	return request;
}

std::vector<Request*> System::daily_check_in()
{
	std::vector<Request*> processed_requests;

	for (auto& [room_type, type_booking] : _booking)
	{
		while (type_booking.check_front(_current_day))
		{
			int book_id = type_booking.pull();
			check_in(book_id);
			processed_requests.push_back(_base[book_id]);
		}
	}

	return processed_requests;
}

std::vector<Request*> System::daily_depart()
{
	std::vector<Request*> processed_requests;

	for (auto& [room_type, rooms] : _occupancy)
	{
		for (auto& room : rooms)
		{
			if (!room.is_departure_day(_current_day)) continue;

			_revenue += room.get_now_price();

			room.clear();
			processed_requests.push_back(_base[room.get_book_id()]);
		}
	}

	return processed_requests;
}