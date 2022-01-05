// Question3.cpp


#include <iostream>
#include "Question3.h"


int main(int argc, char *argv[]) {
	std::cout << "Making a rectangle:" << std::endl;
	Rectangle rectangle;
	rectangle.ui_get_area();

	std::cout << std::endl << "Making a box:" << std::endl;
	Box box;
	box.ui_get_area();
	box.ui_get_volume();


	return 0;
}
