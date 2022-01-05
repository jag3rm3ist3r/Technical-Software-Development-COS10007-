// Question3.h




typedef struct Employee {
		size_t id;
		char name[50];
		size_t salary;
}employee;


int user_input_int(void) {
	char input[100];
	fflush(stdin);
	fgets(input, 99, stdin);
	return atoi(input);
}


void user_input_char(char * input) {
	fflush(stdin);
	fgets(input, 49, stdin);
	for(int i = 0; input[i] != '\0' && i < 50; i++) {
		if(input[i] == '\n') {
			input[i] = '\0';
		}
	}
}


int linear_search_name(employee * e, const size_t e_len, char * s) {
	for(int i = 0; i < e_len; i++) {
		// Compare the string to see if it is a substring.
		if(strstr(e[i].name, s) != NULL) {
			return i;
		}
		// Compare the string to see if it's the exact same string.
		if(0 == strcmp(e[i].name, s)) {
			return i;
		}
	}
	return -1;
}


int linear_search(employee * e, const size_t e_len, int s) {
	// The sensible way to do this.
	/*
	for(int i = 0; i < e_len; i++) {
		if(e[i].id == s) {
			return i;
		}
	}
	return -1;
	*/

	// How I have been asked to do this for some reason.
	int chunk(int index) {
		if(index == e_len) {return -1;}
		if(e[index].id == s) {
			return index;
		} else {
			chunk(++index);
		}
	}
	return chunk(0);
}


int binary_search(employee * e, const size_t e_len, int s) {
	int divide(employee * e, int s, size_t left, size_t right) {
		int midpoint = (left + right) / 2;
		// Check if the search term has been found.
		if(e[midpoint].id == s) {return midpoint;}
		// Check if the search term can not be found.
		if(left >= right) {return -1;}

		// Search the correct side of the array.
		if(e[midpoint].id > s) {
			// midpoint is greater than value we're looking for.
			return divide(e, s, left, midpoint);
		} else {
			// midpoint is lesser than value we're searching for.
			return divide(e, s, midpoint, right);
		}
	}
	return divide(e, s, 0, e_len - 1);
}


