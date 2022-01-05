// Question2.c




#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Question2.h"


int main(int argc, char *argv[]) {
	srandom(time(NULL));
	size_t student_marks_array[50];
	for(int i = 0; 50 > i; i++) {
		student_marks_array[i] = random() % 101;
	}


	size_t marks[50];
	void reset_students(void) {
		memcpy(marks, student_marks_array, sizeof(marks));
	}
	reset_students();


	void print_students(size_t min, size_t max) {
		for(int i = 0, ticker = 0; 50 > i; i++) {
			if(marks[i] >= min && marks[i] < max) {
				printf("Mark %d : %d\t", i + 1, marks[i]);
				// Newline every 5 columns.
				if((++ticker) % 5 == 0) {printf("\n");}
			}
		}
		printf("\n");
	}


	bool menu(void) {
		clear();
		printf(	"STUDENT MARKS\n\n"
				"1\t:\tShow original order of marks\n"
				"2\t:\tBubble Sort\n"
				"3\t:\tSelection Sort\n"
				"4\t:\tInsertion Sort\n"
				"5\t:\tAll Sorting Methods\n"
				"6\t:\tGenerate Report\n"
				"10\t:\tExit\n\n");
		switch(user_input_int()) {
			case 1:
				// No sort.
				printf("Original order:\n");
				reset_students();
				print_students(0, 100);
				break;
			case 2:
				// Bubble.
				printf("Bubble sort:\n");
				reset_students();
				memcpy(marks, bubble_sort(marks), sizeof(marks));
				print_students(0, 100);
				break;
			case 3:
				// Selection.
				printf("Selection sort:\n");
				reset_students();
				memcpy(marks, selection_sort(marks), sizeof(marks));
				print_students(0, 100);
				break;
			case 4:
				// Insertion.
				printf("Insertion sort:\n");
				reset_students();
				memcpy(marks, insertion_sort(marks), sizeof(marks));
				print_students(0, 100);
				break;
			case 5:
				// All sorting methods.
				printf("All sorting methods:\n");

				// Unsorted
				printf("Unsorted\n");
				reset_students();
				print_students(0, 100);

				// Bubble sort
				printf("Bubble\n");
				reset_students();
				memcpy(marks, bubble_sort(marks), sizeof(marks));
				print_students(0, 100);

				// Selection sort
				printf("Selection\n");
				reset_students();
				memcpy(marks, selection_sort(marks), sizeof(marks));
				print_students(0, 100);

				// Insertion sort
				printf("Insertion\n");
				reset_students();
				memcpy(marks, insertion_sort(marks), sizeof(marks));
				print_students(0, 100);
				break;
			case 6:
				// Report
				reset_students();
				memcpy(marks, insertion_sort(marks), sizeof(marks));

				printf(	"Generate a report for which group?"
						"\n"
						"\n"
						"1 HD\n"
						"2 D\n"
						"3 C\n"
						"4 P\n"
						"5 N\n"
						"\n");
				switch(user_input_int()) {
					case 1:
						printf("\nHD (80 - 100)\n");
						print_students(80, 100);
						break;
					case 2:
						printf("\nD\t(70 - 80)\n");
						print_students(70, 80);
						break;
					case 3:
						printf("\nC\t(60 - 70)\n");
						print_students(60, 70);
						break;
					case 4:
						printf("\nP\t(50 - 60)\n");
						print_students(50, 60);
						break;
					case 5:
						printf("\nN\t (0 - 50)\n");
						print_students(0, 50);
						break;
					default:
						break;
				}
				break;
			case 10:
				return false;
			default:
				return true;
		}
		printf("Press enter to continue...");
		user_input_int();
		printf("\n\n\n\n");
	}
	while(menu()) {}




	return 0;
}

