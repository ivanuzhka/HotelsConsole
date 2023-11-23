#include "Modeling.h"

#include <iostream>

using std::cout;

int main()
{
	for (int i = 0; i < 1000; ++i) {

		Modeling model(2, 7, 8, { 5, 5, 5, 5, 5 }, { 5, 4, 1, 2, 3 }, { 0, 0, 0, 0, 0 });

		model.do_step(24);
	}

	cout << "test\n";


}
