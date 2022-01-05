#include <iostream>
#include <cstddef>
#include "Question5.h"




int main(int argc, char *argv[]) {
	int arrayi[10] =
		{0, 1, -2, 3, -4, 5, 6, -7, 8, 9};
	float arrayf[10] =
		{0.00, 1.00, -2.00, 3.00, -4.00, 5.00, 6.00, -7.00, 8.00, 9.00};
	using std::cout;
	using std::endl;
	cout << countNegative(sizeof(arrayi) / sizeof(*arrayi), arrayi) << endl;
	cout << countNegative(sizeof(arrayf) / sizeof(*arrayf), arrayf) << endl;
	return 0;
}


