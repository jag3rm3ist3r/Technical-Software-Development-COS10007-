// Question5.cpp


// Count negative values in an array.
// float
size_t countNegative(size_t a_len, float a[]) {
	size_t count = 0;
	for(int i = 0; i < a_len; i++) {
		if(a[i] < 0) {count++;}
	}
	return count;
}
// int
size_t countNegative(size_t a_len, int a[]) {
	size_t count = 0;
	for(int i = 0; i < a_len; i++) {
		if(a[i] < 0) {count++;}
	}
	return count;
}


