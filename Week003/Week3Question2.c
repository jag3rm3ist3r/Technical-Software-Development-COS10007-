#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>


int main(void) {
	// Wait 1 second to make sure that the time isn't the same when we run this
	// program again.
	sleep(1);
	// Setup random number generation.
	srandom(time(NULL));

	// Singly linked list.
	struct student {
		char name[20];
		int id;
		struct student *next;
	};
	typedef struct student Student;
	typedef Student *Student_ptr;

	// Pointers to locations in the list.
	Student_ptr index = NULL;
	Student_ptr curr = NULL;
	Student_ptr new = NULL;


	// Check if a number corresponds to a student.
	// Returns true if student number exists.
	bool checkid(unsigned int checkme) {
		bool found = false;
		Student_ptr student_to_check = index;
		while(student_to_check != NULL) {
			if(checkme == student_to_check->id) {found = true;}
			student_to_check = student_to_check->next;
		}
		return found;
	}

	bool checkname(char* checkme) {
		bool found = false;
		Student_ptr student_to_check = index;
		while(student_to_check != NULL) {
			if(strcmp(checkme, student_to_check->name)) {found = true;}
			student_to_check = student_to_check->next;
		}
		return found;
	}


	// Place "new" into the correct location in the list.
	void insert_into_list(void) {
		// Insert new student in linked list.
		curr = index;
		if(index != NULL) {
			while(curr != NULL) {
				if(curr->id > new->id) {
					// Make new the index and link to the old index,
					// this should only happen when the index is greater than
					// the new value we create.
					new->next = curr;
					index = new;
					curr = NULL;
				} else if(	curr->next == NULL ||
							curr->id < new->id &&
							curr->next->id > new->id) {
					// Place after curr.
					new->next = curr->next;
					curr->next = new;
					curr = NULL;
				} else {
					// Move to the next position in the list.
					curr = curr->next;
				}
			}
		} else {
			// If there isn't an index yet then new becomes the index.
			new->next = NULL;
			index = new;
		}
	}

	// Create a new student and place them in order of student id.
	void create_student(void) {
		int tmpid;

		// !!! BUG !!!
		// This code will get stuck in a loop if every possible value is used.
		// Generate a new student id that is unique.
		do {
			tmpid = (random() % 100) + 1;
		} while(checkid((unsigned int) tmpid));

		new = (Student*) malloc(sizeof(Student));
		new->id = tmpid;
		// Take user input for name of student.
		printf("What is the student's name. (ID: %d)\n", new->id);
		char tmpname[20];
		fgets(tmpname, 19, stdin);
		// Get rid of newline.
		for(int i = 0; i < strlen(tmpname); i++) {
			if(tmpname[i] == '\n') {tmpname[i] = '\0';}
		}
		strcpy(new->name, tmpname);

		insert_into_list();
	}


	// Create students.
	for(int i = 0; i < 10; i++) {
		create_student();
	}
	printf("\n");


	// Print the list to screen.
	void print_student_list(void) {
		printf("Student list\n");
		curr = index;
		while(curr != NULL) {
			printf("ID: %d\tName: %s\n", curr->id, curr->name);
			curr = curr->next;
		}
		printf("\n");
	}
	print_student_list();


	// Print the list to the screen in reverse.
	printf("Student list (reverse order)\n");
	curr = index;
	// Count how many entries there are.
	int i = 0;
	while(curr != NULL) {
		i++;
		curr = curr->next;
	}
	// Walk backwards through the linked list.
	for(i; i > 0; i--) {
		curr = index;
		for(int a = 1; a < i; a++) {
			curr = curr->next;
		}
		printf("ID: %d\tName: %s\n", curr->id, curr->name);
	}
	printf("\n");


	// Write the list to file.
	FILE *fptr = fopen("./iofile.txt", "w+");
	curr = index; 
	while(curr != NULL) {
		fprintf(fptr, "ID: %d\tName: %s\n", curr->id, curr->name);
		curr = curr->next;
	}
	fclose(fptr);


	// Setup for user removing and editing entries.
	char userinputchar[20];
	int userinputint;
	void take_user_input(void) {
		fgets(userinputchar, 19, stdin);
		// Filter input.
		for(int i = 0; i < strlen(userinputchar); i++) {
			if(userinputchar[i] == '\n') {userinputchar[i] = '\0';}
		}
		userinputint = atoi(userinputchar);
	}




	// Remove an entry.
	printf("Input a student name or number to delete: ");
	take_user_input();
	// Check if it exists.
	if(checkid(userinputint) || checkname(userinputchar)) {
		// Find it.
		Student_ptr tmp;
		tmp = (Student*) malloc(sizeof(Student));
		tmp->next = index;
		curr = tmp;
		while(	strcmp(curr->next->name, userinputchar) != 0 &&
				curr->next->id != userinputint) {
			curr = curr->next;
		}
		// Handle removing and rearranging the list.
		if(curr->next == index) {
			// The index is the removed value.
			index = curr->next->next;
			free(curr->next);
		} else {
			// The removed value is not the index.
			free(tmp);
			tmp = curr->next;
			curr->next = curr->next->next;
		}
		free(tmp);
	}
	printf("\n");


	print_student_list();


	// Edit a student's details.
	printf("Input a student name or number to edit: ");
	take_user_input();
	// Check if it exists.
	if(checkid(userinputint) || checkname(userinputchar)) {
		Student_ptr tmp;
		tmp = (Student*) malloc(sizeof(Student));
		tmp->next = index;
		curr = tmp;
		while(	strcmp(curr->next->name, userinputchar) != 0 &&
				curr->next->id != userinputint) {
			curr = curr->next;
		}

		// Edit the student ID.
		printf("Enter a new ID for %s: ", curr->next->name);
		take_user_input();

		// Remove the student from the list and mark it as "new" for
		// re-insertion.
		if(curr->next == index) {
			// The edited value is the index.
			new = curr->next;
			index = curr->next->next;
		} else {
			// The edited value is not the index.
			new = curr->next;
			curr->next = curr->next->next;
		}
		// We don't need tmp any more.
		free(tmp);
		// Check if the new number is already in the list.
		if(checkid(userinputint)) {
			printf("Error: That student ID is not unique.\n");
		} else {
			new->id = userinputint;
		}
		// Re-insert new into the list.
		insert_into_list();
	}
	printf("\n");


	print_student_list();


	// Free memory.
	while(index != NULL) {
		curr = index->next;
		free(index);
		index = curr;
	}


	return 0;
}
