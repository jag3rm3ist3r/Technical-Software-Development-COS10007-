#include "Question4.h"
#include <iostream>


int main(int argc, char * argv[]) {
	const int firstint = 10;
	const int secondint = 50;
	const float firstfloat = 10.30;
	const float secondfloat = 30.50;


	std::cout << "min: " << min(firstint, secondint) << std::endl;
	std::cout << "max: " << max(firstint, secondint) << std::endl;
	std::cout << "min: " << min(firstfloat, secondfloat) << std::endl;
	std::cout << "max: " << max(firstfloat, secondfloat) << std::endl;


	return 0;
}
