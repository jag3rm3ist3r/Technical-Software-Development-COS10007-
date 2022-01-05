#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN 10
#define MAX_VAL 64


// Array to search.
int array[ARRAY_LEN];


void sort_array(void) {
	for(int i = 0; i < ARRAY_LEN; i++) {
		int min = MAX_VAL;
		size_t min_index = 0;
		for(int j = i; j < ARRAY_LEN; j++) {
			if(array[j] < min) {
				min = array[j];
				min_index = j;
			}
		}
		int temp = array[i];
		array[i] = min;
		array[min_index] = temp;
	}
}


void print_array(void) {
	printf("?");
	for(int i = 0; i < ARRAY_LEN; i++) {
		printf("\t%d", array[i]);
	}
	printf("\n");
}


// Search each element in array, return first matching value found.
int linear_search(int * a, size_t a_len, int key) {
	for(int i = 0; i < a_len; i++) {
		if(a[i] == key) {
			return i;
		}
	}
	return -1;
}


// Search by dividing the list in half each time, return the first matching value found.
int binary_search(int * a, size_t a_len, int key) {
	int divide(int l, int r) {
		int m = (l + r) / 2;
		if(a[m] == key) {return m;}
		if(l >= r) {return -1;}
		// Don't check m because it's already checked at the start of this function.
		if(key < a[m]) {
			// Go left.
			return divide(l, m - 1);
		} else {
			// Go right.
			return divide(m + 1, r);
		}
		// Catchall in case something goes horribly wrong.
		return -1;
	}
	return divide(0, a_len - 1);
}


int main(void) {
	srandom(time(NULL));
	for(int i = 0; i < ARRAY_LEN; i++) {array[i] = random() % MAX_VAL;}
	printf("Initial Array\n\n");
	print_array();
	printf("\nSorted Array\n\n");
	sort_array();
	print_array();
	printf(	"\n-------------------------------------------"
			"---------------------------------------\n\n");


	printf("Linear Search\n\n");
	print_array();
	for(int i = 0; i < linear_search(array, ARRAY_LEN, 32) + 1; i++) {
		printf("\t");
	}
	printf("^\n\n");


	printf("Binary Search\n\n");
	print_array();
	for(int i = 0; i < binary_search(array, ARRAY_LEN, 32) + 1; i++) {
		printf("\t");
	}
	printf("^\n\n");


	return 0;
}
