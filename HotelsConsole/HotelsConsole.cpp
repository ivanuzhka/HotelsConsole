#include "Modeling.h"

#include <iostream>

using std::cout;

int main()
{
	for (int i = 0; i < 100; ++i)
	{

		Modeling model(10, 4, 5, { 1, 1, 1, 1, 1 }, { 5, 4, 1, 2, 3 }, { 0, 0, 0, 0, 0 });

		model.do_step(24);

		model.get_actions();
		model.get_day_staticstic();

		model.do_step(24);

		model.get_actions();
		model.get_day_staticstic();

		cout << "test # " << i + 1 << "\n";

	}

	cout << "\nend of testing\n";


}
