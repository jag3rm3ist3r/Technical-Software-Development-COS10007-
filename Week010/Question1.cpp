// Question1.cpp




#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


int user_input_int(void);
inline float sphereVolume(int r);


int main(int argc, char * argv[]) {
	std::cout << "What is the radius of the sphere?\n";
	std::cout << sphereVolume(user_input_int()) << std::endl;
	return 0;
}


int user_input_int(void) {
	char input[50];
	fflush(stdin);
	fgets(input, 49, stdin);
	return atoi(input);
}


inline float sphereVolume(int r) {
	return (4 * M_PI * pow(r, 3)) / 3;
}


