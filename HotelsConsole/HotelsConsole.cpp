#include "Modeling.h"

#include <iostream>

using std::cout;

int main()
{
	Modeling model(1, 1, 5, { 1, 1, 1, 1, 1 });

	std::vector<Request*> requests = model.generate_requests();

	

	for (int i = 0; i < requests.size(); ++i)
	{
		cout << i + 1 << ".\n";
		cout << "room_type: " << requests[i]->get_room_type()->get_title() << "\n";
		cout << "base_price: " << requests[i]->get_room_type()->get_price() << "\n";
		cout << "time (h): " << requests[i]->get_time() << "\n";
		cout << "arrival_day: " << requests[i]->get_arrival_day() << "\n";
		cout << "departure_day: " << requests[i]->get_departure_day() << "\n";
		cout << "paid (percent): " << requests[i]->get_percent() << "\n\n\n";
	}
}
