#include "TypeBooking.h"

bool TypeBooking::is_empty_rooms(int arrival_day, int departure_day, int capacity) const
{
	int counter = 0;

	for (auto& event : _days)
	{
		counter += event._type;

		if (event._day < arrival_day || departure_day < event._day) continue;
		if (capacity < counter)
			return false;
	}
	return true && capacity != 0;
}

void TypeBooking::insert(int id, int arrival_day, int departure_day)
{
	_days.insert({ id, arrival_day, 1 });
	_days.insert({ id, departure_day, -1 });
}

int TypeBooking::pull()
{
	int book_id, arrival_day, departure_day;
	book_id = _days.begin()->_book_id;
	arrival_day = _days.begin()->_day;
	_days.erase(_days.begin());

	for (auto& event : _days)
	{
		if (event._book_id != book_id) continue;

		departure_day = event._day;
		_days.erase(event);
		break;
	}

	return book_id;
}

void TypeBooking::erase(int book_id)
{
	for (int _ = 0; _ < 2; ++_)
	{
		for (auto& el : _days)
		{
			if (el._book_id == book_id)
			{
				_days.erase(el);
				break;
			}
		}
	}
}

std::tuple<int, int> TypeBooking::get_book(int book_id) const
{
	int arrival_day, departure_day;
	for (auto& event : this->_days)
	{
		if (event._book_id == book_id && event._type == 1)
			arrival_day = event._day;
		else if (event._book_id == book_id && event._type == -1)
			departure_day = event._day;
	}

	return { arrival_day, departure_day };

}
