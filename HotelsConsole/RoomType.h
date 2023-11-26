#pragma once
#include <algorithm>
#include <string>

class RoomType
{
public:
	RoomType() : _title("unknown"), _price(0), _discount(0) {}
	RoomType(std::string title, int price, int discount, int priority) 
		: _title(title)
		, _price(price)
		, _discount(discount)
		, _priority(priority) {}

	int get_price() const { return _price; }
	std::string get_title() const { return _title; }
	int get_discount() const { return _discount; }

	bool operator==(const RoomType& other) const { return this->_priority == other._priority; }
	bool operator!=(const RoomType& other) const { return !(*this == other); }
	bool operator<(const RoomType& other) const { return this->_priority < other._priority; }
	bool operator>(const RoomType& other) const { return *this != other && !(*this < other); }

private:
	int _price;
	std::string _title;
	int _discount;
	int _priority;
};

class Lux : public RoomType
{
public:
	Lux() : RoomType("Lux", -1, -1, 5) {}
	Lux(int price, int discount) : RoomType("Lux", price, discount, 5) {}
};

class SemiLux : public RoomType
{
public:
	SemiLux() : RoomType("SemiLux", -1, -1, 4) {}
	SemiLux(int price, int discount) : RoomType("SemiLux", price, discount, 4) {}
};

class DoublePro : public RoomType
{
public:
	DoublePro() : RoomType("DoublePro", -1, -1, 3) {}
	DoublePro(int price, int discount) : RoomType("DoublePro", price, discount, 3) {}
};

class Double : public RoomType
{
public:
	Double() : RoomType("Double", -1, -1, 2) {}
	Double(int price, int discount) : RoomType("Double", price, discount, 2) {}
};

class Single : public RoomType
{
public:
	Single() : RoomType("Single", -1, -1, 1) {}
	Single(int price, int discount) : RoomType("Single", price, discount, 1) {}
};
