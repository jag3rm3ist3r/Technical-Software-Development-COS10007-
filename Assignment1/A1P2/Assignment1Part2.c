// size_t
#include <stdlib.h>
// sleep
//#include <unistd.h>
// text interaction
#include <stdio.h>
// bool
//#include <stdbool.h>
// strcpy
#include <string.h>
// toupper
//#include <ctype.h>
// isnan
//#include <math.h>


int main(int argc, char *argv[]) {
	// Handle arguments.
	// Check ammount of arguments.
	if(argc != 1) {
		// Incorrect number of arguments,
		// display a terse message then kill the program.
		printf("No arguments accepted.\n");
		return 1;
	}


	// !!! CAN'T CHANGE THIS STRUCT THIS IS A FIXED PART OF THE ASSIGNMENT !!!
	struct studentID {
		int value;
		struct studentID *next;
	};
	typedef struct studentID STUDENTID;
	typedef STUDENTID * STUDENTIDPtr;
	// !!! END FIXED PART OF THE ASSIGNMENT !!!


	void clear(void) {
		const size_t lines_to_clear = 100;
		for(int i = 0; i < lines_to_clear; i++) {printf("\n");}
	}
	clear();


	STUDENTIDPtr index_ptr = NULL;
	STUDENTIDPtr temp_ptr = NULL;
	STUDENTIDPtr new_ptr = NULL;
	STUDENTIDPtr curr_ptr = NULL;


	new_ptr = (STUDENTID*) malloc(sizeof(STUDENTID));
	new_ptr->value = 4;
	new_ptr->next = NULL;
	index_ptr = new_ptr;
	temp_ptr = new_ptr;

	new_ptr = (STUDENTID*) malloc(sizeof(STUDENTID));
	new_ptr->value = 5;
	new_ptr->next = NULL;
	temp_ptr->next = new_ptr;
	temp_ptr = new_ptr;

	new_ptr = (STUDENTID*) malloc(sizeof(STUDENTID));
	new_ptr->value = 3;
	new_ptr->next = NULL;
	temp_ptr->next = new_ptr;
	temp_ptr = new_ptr;

	new_ptr = (STUDENTID*) malloc(sizeof(STUDENTID));
	new_ptr->value = 4;
	new_ptr->next = NULL;
	temp_ptr->next = new_ptr;
	temp_ptr = new_ptr;

	new_ptr = (STUDENTID*) malloc(sizeof(STUDENTID));
	new_ptr->value = 5;
	new_ptr->next = NULL;
	temp_ptr->next = new_ptr;
	temp_ptr = new_ptr;

	// Please just give me a number with duplicates next time,
	// my student number doesn't have any.
	// I am using the student number from the example in the PDF.

	void printit(void) {
		curr_ptr = index_ptr;
		int i = 1;
		while(curr_ptr != NULL) {
			printf("Value %d: %d\n", i, curr_ptr->value);
			curr_ptr = curr_ptr->next;
			i++;
		}
		printf("\n");
	}
	// Print the ll before the changes.
	printf("This is the linked list before removing duplicates.\n");
	printit();


	void remove_node(STUDENTIDPtr remove_me, STUDENTIDPtr remove_me_prev) {
		remove_me_prev->next = remove_me->next;
		free(remove_me);
	}

	// This is where we remove the duplicate instances.
	curr_ptr = index_ptr;
	int inspect;
	while(curr_ptr != NULL) {
		inspect = curr_ptr->value;
		temp_ptr = curr_ptr;
		while(curr_ptr->next != NULL) {
			if(curr_ptr->next->value == inspect) {
				remove_node(curr_ptr->next, curr_ptr);
			} else {
				curr_ptr = curr_ptr->next;
			}
		}
		curr_ptr = temp_ptr->next;
	}


	printf("This is the linked list after removing duplicates.\n");
	printit();
	printf("\n\n");


	// Clean up memory afterwards.
	while(index_ptr != NULL) {
		curr_ptr = index_ptr->next;
		free(index_ptr);
		index_ptr = curr_ptr;
	}


	return 0;
}
