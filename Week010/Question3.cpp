// Question3.cpp




#include <iostream>

int doubleByValue(int v) {
	return v * 2;
}
void doubleByReference(int * v) {
	*v *= 2;
}

int main(int argc, char * argv[]) {
	int value = 1337;
	std::cout << doubleByValue(value) << std::endl;
	doubleByReference(&value);
	std::cout << value << std::endl;

	return 0;
}


