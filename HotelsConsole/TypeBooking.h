#pragma once

#include <set>
#include <tuple>

struct Event
{
	int _book_id, _day, _type;

	bool operator<(const Event& other) const
	{
		if (this->_day == other._day)
			return this->_type > other._type;
		return this->_day < other._day;
	}
};

class TypeBooking
{
public:
	bool is_empty_rooms(int arrival_day, int departure_day, int capacity) const;
	bool empty() const { return _days.empty(); }

	void insert(int id, int arrival_day, int departure_day);

	// erase first event from _days and returns its book id;
	int pull();
	
	// erase events with id equal to book_id
	void erase(int book_id);

	bool check_front(int current_day) const
	{
		if (_days.empty()) return false;
		return _days.begin()->_day == current_day;
	}

	std::set<Event> get_days() const { return _days; }

	std::tuple<int, int> get_book(int book_id) const;

private:
	std::set<Event> _days;
};

