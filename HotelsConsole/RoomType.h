#pragma once
#include <algorithm>
#include <string>

class RoomType
{
public:
	RoomType() : _title("unknown"), _price(0), _discount(0) {}
	RoomType(std::string title, int price, int discount) 
		: _title(title)
		, _price(price)
		, _discount(discount) {}

	int get_price() const { return _price; }
	std::string get_title() const { return _title; }
	int get_discount() const { return _discount; }

	bool operator<(const RoomType& other) const { return this->_price < other._price; }
	bool operator==(const RoomType& other) const { return this->_title == other._title; }
	bool operator!=(const RoomType& other) const { return !(*this == other); }

private:
	int _price;
	std::string _title;
	int _discount;
};

class Lux : public RoomType
{
public:
	Lux() : RoomType("Lux", -1, -1) {}
	Lux(int price, int discount) : RoomType("Lux", price, discount) {}
};

class SemiLux : public RoomType
{
public:
	SemiLux() : RoomType("SemiLux", -1, -1) {}
	SemiLux(int price, int discount) : RoomType("SemiLux", price, discount) {}
};

class DoublePro : public RoomType
{
public:
	DoublePro() : RoomType("DoublePro", -1, -1) {}
	DoublePro(int price, int discount) : RoomType("DoublePro", price, discount) {}
};

class Double : public RoomType
{
public:
	Double() : RoomType("Double", -1, -1) {}
	Double(int price, int discount) : RoomType("Double", price, discount) {}
};

class Single : public RoomType
{
public:
	Single() : RoomType("Single", -1, -1) {}
	Single(int price, int discount) : RoomType("Single", price, discount) {}
};
