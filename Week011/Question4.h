// Question4.h


// Find the larger of the two numbers.
template <class T> T max(T a, T b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

// Find the smaller of the two numbers.
template <class T> T min(T a, T b) {
	if(a > b) {
		return b;
	} else {
		return a;
	}
}
