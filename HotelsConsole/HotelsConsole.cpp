#include "Modeling.h"

#include <iostream>

using std::cout;

int main()
{
	Modeling model(2, 5, 10, { 2, 2, 2, 2, 2 }, { 5, 4, 3, 2, 1 }, { 50, 50, 50, 50, 50});

	model.do_step(10);

	for (int i = 0; i < 2 * 24; i += 2)
	{
		model.do_step(2);
	}
}
