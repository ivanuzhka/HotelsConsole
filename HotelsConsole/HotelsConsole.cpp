#include "Modeling.h"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
	for (int i = 0; i < 100; ++i)
	{

		Modeling model(10, 3, 4, { 1, 1, 1, 1, 1 }, { 5, 4, 1, 2, 3 }, { 0, 0, 0, 0, 0 });

		auto day1 = model.do_step(24);

		cout << day1.size() << endl;

		for (auto& el : day1)
		{
			cout << "\n\n";
			cout << "Request type: " << el->get_request_type() << "\n";
			cout << "Room type: " << el->get_room_type()->get_title() << "\n";
			cout << "Arrival day: " << el->get_arrival_day() << "\n";
			cout << "Departure day: " << el->get_departure_day() << "\n";
			cout << endl;
		}

		cout << "test # " << i + 1 << "\n";

	}

	cout << "\nend of testing\n";


}
