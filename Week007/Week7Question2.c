#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


// !!! FIXED PART OF QUESTION !!!
struct student {
	char name[10];
	int rank;
};
struct student Students[5];
// !!! END FIXED PART OF QUESTION !!!
typedef struct student Student;

// Make a more interesting array.
#define PEOPLE_LEN 20
Student People[PEOPLE_LEN];
Student People_backup[PEOPLE_LEN];

// Functions for assigning default values at start of execution.
void assign_values(const size_t apos, const char * n, const int r);
void assign_values_people(const size_t apos, const char * n, const int r);
// Functions for reseting values to defaults before executing sorting functions.
void reset_values(void);
void reset_values_people(void);
// Calls assign_values_people a bunch to setup for later.
void initialize_values_people(void);
// Print the contents of an array of type Student.
void print_values(const Student * s, size_t s_len);

// Sorting algorithms
Student * selection_sort(Student * s, const size_t s_len);
Student * insertion_sort(Student * s, const size_t s_len);
Student * merge_sort(Student * s, const size_t s_len);
Student * quick_sort(Student * s, const size_t s_len);


int main(void) {
	// Initialize random number generator for later when we run the functions on a larger sample.
	srandom(time(NULL));


	// Unsorted
	reset_values();
	printf("Values before sorting:\n");
	print_values(Students, sizeof(Students) / sizeof(*Students));
	printf("\n");

	// Selction
	reset_values();
	memcpy(Students, selection_sort(Students, sizeof(Students) / sizeof(*Students)), sizeof(Students));
	printf("Values after selection sort:\n");
	print_values(Students, sizeof(Students) / sizeof(*Students));
	printf("\n");

	// Insertion
	reset_values();
	memcpy(Students, insertion_sort(Students, sizeof(Students) / sizeof(*Students)), sizeof(Students));
	printf("Values after insertion sort:\n");
	print_values(Students, sizeof(Students) / sizeof(*Students));
	printf("\n");

	// Merge
	reset_values();
	memcpy(Students, merge_sort(Students, sizeof(Students) / sizeof(*Students)), sizeof(Students));
	printf("Values after merge sort:\n");
	print_values(Students, sizeof(Students) / sizeof(*Students));
	printf("\n");

	// Quick
	reset_values();
	memcpy(Students, quick_sort(Students, sizeof(Students) / sizeof(*Students)), sizeof(Students));
	printf("Values after quick sort:\n");
	print_values(Students, sizeof(Students) / sizeof(*Students));
	printf("\n");




	/**
	sleep(5);
	// Different array with PEOPLE_LEN x random values this time.
	// Unsorted
	initialize_values_people();
	reset_values_people();
	printf("New values before sorting:\n");
	print_values(People, sizeof(People) / sizeof(*People));
	printf("\n");

	// Selction
	reset_values_people();
	memcpy(People, selection_sort(People, sizeof(People) / sizeof(*People)), sizeof(People));
	printf("Values after selection sort:\n");
	print_values(People, sizeof(People) / sizeof(*People));
	printf("\n");

	// Insertion
	reset_values_people();
	memcpy(People, insertion_sort(People, sizeof(People) / sizeof(*People)), sizeof(People));
	printf("Values after insertion sort:\n");
	print_values(People, sizeof(People) / sizeof(*People));
	printf("\n");

	// Merge
	reset_values_people();
	memcpy(People, merge_sort(People, sizeof(People) / sizeof(*People)), sizeof(People));
	printf("Values after merge sort:\n");
	print_values(People, sizeof(People) / sizeof(*People));
	printf("\n");

	// Quick
	reset_values_people();
	memcpy(People, quick_sort(People, sizeof(People) / sizeof(*People)), sizeof(People));
	printf("Values after quick sort:\n");
	print_values(People, sizeof(People) / sizeof(*People));
	printf("\n");
	/**/


	return 0;
}


void assign_values(const size_t apos, const char * n, const int r) {
	strcpy(Students[apos].name, n);
	Students[apos].rank = r;
}


void assign_values_people(const size_t apos, const char * n, const int r) {
	strcpy(People_backup[apos].name, n);
	People_backup[apos].rank = r;
}


void reset_values(void) {
	assign_values(0, "David", 10);
	assign_values(1, "James", 2);
	assign_values(2, "Bruce", 9);
	assign_values(3, "Jane", 12);
	assign_values(4, "Edith", 6);
}


void initialize_values_people(void) {
	for(int i = 0; i < PEOPLE_LEN; i++) {
		assign_values_people(i, "A", random() % 100);
	}
}


void reset_values_people(void) {
	memcpy(People, People_backup, sizeof(People));
}


void print_values(const Student * s, size_t s_len) {
	for(int i = 0; i < s_len; i++) {
		printf("Name: %s\t", s[i].name);
		printf("Rank: ");
		// Keep all of the numbers lined up.
		if(s[i].rank < 10) {printf(" ");}
		printf("%d\n", s[i].rank);
	}
}


// Question 2 Part a
Student * selection_sort(Student * s, const size_t s_len) {
	// Iterate position in array.
	for(int i = 0; i < s_len; i++) {
		int minimum = s[i].rank;
		size_t minpos = i;
		// Find the next lowest value.
		for(int j = i + 1; j < s_len; j++) {
			if(s[j].rank < minimum) {
				minpos = j;
				minimum = s[minpos].rank;
			}
		}
		// Switch the position of the values.
		Student temp = s[i];
		s[i] = s[minpos];
		s[minpos] = temp;
	}
	return s;
}


// Question 2 Part b
Student * insertion_sort(Student * s, const size_t s_len) {
	// Iterate through array.
	for(int i = 0; i < s_len; i++) {
		// Shuffle items down list till we find the correct location.
		for(int j = i + 1; s[j].rank < s[j - 1].rank && j < s_len; j--) {
			Student temp = s[j];
			s[j] = s[j - 1];
			s[j - 1] = temp;
		}
	}
	return s;
}


// Question 2 Part c
Student * merge_sort(Student * s, const size_t s_len) {
	// Sort two arrays into one with the assumption that they're either of length 1 or are already internally
	// sorted.
	Student * conquer(	Student * merge,
								const size_t merge_len,
								const Student * left,
								const size_t left_len,
								const Student * right,
								const size_t right_len) {
		size_t left_pos = 0, right_pos = 0;
		// Merge the arrays into one array.
		for(int i = 0; i < merge_len; i++) {
			if(	left[left_pos].rank < right[right_pos].rank &&
				left_pos != left_len ||
				right_pos == right_len) {
				merge[i] = left[left_pos++];
			} else {
				merge[i] = right[right_pos++];
			}
		}

		/* Debug info *
		printf("Merged values:\n");
		print_values(merge, merge_len);
		printf("\n");
		usleep(500000);
		/**/
		return merge;
	}


	// Divide arrays recursively into smaller arrays eventually of either 1 or two values.
	Student * divide(Student * split, const size_t arr_len) {
		// Find midpoint.
		const size_t midpoint = arr_len / 2;

		// If there is only one value in the array just return it.
		if(arr_len <= 1) {return split;}

		// Work on left half.
		const size_t left_len = midpoint;
		Student left[left_len];
		// Copy left contents.
		for(int i = 0; i < midpoint; i++) {
			left[i] = split[i];
		}
		// Recursively call this function again.
		memcpy(left, divide(left, left_len), sizeof(left) / sizeof(*left));

		// Work on right half.
		const size_t right_len = arr_len - midpoint;
		Student right[right_len];
		// Copy right contents.
		for(int i = midpoint; i < arr_len; i++) {
			right[i - midpoint] = split[i];
		}
		// Recursively call this function again.
		memcpy(right, divide(right, right_len), sizeof(right) / sizeof(*right));

		// Join halves together.
		return conquer(split, arr_len, left, left_len, right, right_len);
	}


	return divide(s, s_len);
}


// Question 2 Part d
Student * quick_sort(Student * s, const size_t s_len) {
	void swap(Student * a, Student * b) {
		Student temp = *a;
		*a = *b;
		*b = temp;
	}


	int parsechunk(Student * s, int lo, int hi) {
		// Save the pivot point.
		Student pivot = s[hi];

		// Search for things that should be left of the midpoint.
		for(int i = lo; i <= hi; i++) {
			// Shift values if low.
			if(s[i].rank <  pivot.rank) {
				swap(&s[lo++], &s[i]);
			}
		}
		// Dump pivot into midpoint.
		swap(&s[lo], &s[hi]);
		return lo;
	}

	Student * sortfork(Student * s, int lo, int hi) {
		if(lo < hi) {
			int m = parsechunk(s, lo, hi);

			memcpy(s, sortfork(s, lo, m - 1), sizeof(Student));
			memcpy(s, sortfork(s, m + 1, hi), sizeof(Student));
		}

		return s;
	}

	return sortfork(s, 0, s_len - 1);
}


