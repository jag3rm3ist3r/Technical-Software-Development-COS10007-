// size_t
#include <stdlib.h>
// sleep
#include <unistd.h>
// text interaction
#include <stdio.h>
// bool
#include <stdbool.h>
// strcpy
#include <string.h>
// toupper
#include <ctype.h>
// isnan
#include <math.h>


int main(int argc, char *argv[]) {
	// Handle arguments.
	// Check ammount of arguments.
	if(argc != 2) {
		// Incorrect number of arguments,
		// display a terse message then kill the program.
		printf("One argument accepted, no more, no less.\n");
		return 1;
	} else {
		FILE *fptr = NULL;
		if((fptr = fopen(argv[1], "r+")) == NULL) {
			// File didn't open, probably doesn't exist.
			printf("File failed to open, does it exist?\n");
			return 1;
		} else {
			// Don't keep the file open unless using it.
			fclose(fptr);
		}
	}

	// This will always open the one argument to the program.
	FILE *open_file(const char *mode) {
		FILE *fptr = NULL;
		if((fptr = fopen(argv[1], mode)) == NULL) {
			// The file didn't open.
			printf("File failed to open.\n");

			// Actual error handling goes here somewhere.
		}
		return fptr;
	}


	// Student details.
	struct person_tag {
		char name[20];
		char id[10];
	};

	// Course details.
	struct course_tag {
		char course_name[20];
		int no_of_units;
		int marks[4];
		float avg;
	};

	// Linked list for storing student details alongside course details.
	struct student_tag {
		struct person_tag student_info;
		struct course_tag course_info;
		struct student_tag *next;
	};

	// typedef laziness
	typedef struct student_info Student_Info;
	typedef struct course_info Course_Info;

	// malloc Person for a list element.
	typedef struct student_tag Student_Tag;
	typedef Student_Tag *Person;

	// Main data holding variables.
	Person Students_Details = NULL;
	FILE *Students_Details_FILE = NULL;

	// Function to free memory allocated to Students_Details.
	void clean_up_Students_Details(void) {
		while(Students_Details != NULL) {
			Person cleanup_pointer = Students_Details;
			Students_Details = Students_Details->next;
			free(cleanup_pointer);
		}
	}

	// Take user input and return a number.
	unsigned int user_input_number(void) {
		unsigned int answer;
		char text_answer[100];

		fflush(stdin);
		fgets(text_answer, 99, stdin);
		answer = atoi(text_answer);

		return answer;
	}

	// Place Person into the linked list in alphabetical order of name.
	void place_into_list(Person addme) {
		// START DEBUG CODE
		/* Prepend to list. *
		addme->next = Students_Details;
		Students_Details = addme;
		/* END DEBUG CODE */

		Person pos = Students_Details;
		// I don't want to bloat my if condition so I'm making it
		// a function.
		bool compare_next_string(void) {
			if(strcmp(	addme->student_info.name,
						pos->next->student_info.name) >= 0) {
				// addme is equal to or greater than the ascii value
				// of pos->next (later in alphabet)
				return true;
			} else {
				// addme is less than the ascii value of pos->next
				// (earlier in the alphabet)
				return false;
			}
		}
		bool compare_string(void) {
			if(strcmp(	addme->student_info.name,
						pos->student_info.name) >= 0) {
				// addme is equal or greater than the ascii value of
				// pos (later in alphabet)
				return true;
			} else {
				// addme is less than the ascii value of pos
				// (earlier in the alphabet)
				return false;
			}
		}

		// Place item into list in alphabetical order of name.
		// pos is a pointer off of the end of the index pointer for
		// this ll.
		// pos -> Students_Details (list index) -> node -> node -> NULL
		/**/
		if(Students_Details == NULL) {
			// There is nothing in the list yet, start a new one.
			Students_Details = addme;
		} else if(!compare_string()) {
			// addme is smaller than the index.
			addme->next = Students_Details;
			Students_Details = addme;
		} else {
			// There are already things in the list.
			while(pos != NULL) {
				// Compare the strings.
				if(	pos->next == NULL ||
					compare_string() &&
					!compare_next_string()) {
					// addme is smaller than pos->next
					addme->next = pos->next;
					pos->next = addme;
					pos = NULL;
				} else {
					// addme is larger than pos->next
					pos = pos->next;
				}
			}
		}
	}
	/**/

	// Method for displaying a student's details.
	// Takes a pointer to a student as an argument.
	void display_single_student(Person single_student) {
		// Name
		printf(	"Name:\t\t\t%s",
				single_student->student_info.name);
		// ID
		printf(	"ID:\t\t\t%s",
				single_student->student_info.id);
		// Course name
		printf(	"Course name:\t\t%s",
				single_student->course_info.course_name);
		// Marks
		for(	int i = 0;
				i < single_student->course_info.no_of_units;
				i++) {
			printf(	"Mark #%d:\t\t%d\n",
					i + 1,
					single_student->course_info.marks[i]);
		}
		// Average mark
		if(!isnan(single_student->course_info.avg)) {
			printf(	"Average mark:\t\t%.2f\n",
					single_student->course_info.avg);
		}
		printf("\n");
	}


	// Menu option 1 display_students
	void display_students(void) {
		Person pos = NULL;
		pos = Students_Details;
		printf("\n");
		while(pos != NULL) {
			display_single_student(pos);
			// Step through list.
			pos = pos->next;
		}
	}



	// Read file passed as argument.
	// Create a linked list of elements described in file.
	// Output pointer to index of linked list created.
	void read_file() {
		clean_up_Students_Details();
		//
		// students.txt file formatting for reference:
		//
		// char[20]	student_info->name
		// char[10]	student_info->id
		// char[20]	course_info->course_name
		// int		course_info->no_of_units
		// int		course_info->marks[0]
		// int		course_info->marks[1]
		// int		course_info->marks[2]
		// int		course_info->marks[3]
		//
		// One variable is not provided by the file.
		// float	course_tag	GENERATED IN RUNTIME
		//

		// Open file before starting, don't open it in the function
		// because the function is called repeatedly.
		Students_Details_FILE = open_file("r");
		// Store the pointer to pass to the inserter function.
		Person temp = NULL;


		// Create a new Person, return it.
		Person create_person(void) {
			// The return value.
			Person newPerson = NULL;
			// Line content pointer to string malloc'd by getline.
			char *line = NULL;
			// Line length.
			// (For -1 when line not there use ssize_t and grab it
			//	from the return value of getline())
			//	This value is ignored because line == NULL,
			//	but we still need it.
			size_t len = 0;


			// Only continue if there is a line to be read.
			if((getline(&line, &len, Students_Details_FILE)) != -1) {
				// Create the person to be returned.
				newPerson = (Student_Tag*) malloc(sizeof(Student_Tag));
				// Make next == NULL so we don't cause errors later.
				newPerson->next = NULL;

				// Get the name.
				// (using getline line from while statement)
				strcpy(newPerson->student_info.name, line);
		
				// Get the id.
				getline(&line, &len, Students_Details_FILE);
				strcpy(newPerson->student_info.id, line);

				// Get the course name.
				getline(&line, &len, Students_Details_FILE);
				strcpy(newPerson->course_info.course_name, line);
		
				// Get the number of units.
				getline(&line, &len, Students_Details_FILE);
				newPerson->course_info.no_of_units = atoi(line);
				if(newPerson->course_info.no_of_units > 4) {
					newPerson->course_info.no_of_units = 4;
					printf("ERROR: Max subjects == 4\n");
				}

				// Get the marks.
				float average = 0.00;
				for(int i = 0;
					i < newPerson->course_info.no_of_units;
					i++) {
					getline(&line, &len, Students_Details_FILE);
					newPerson->course_info.marks[i] = atoi(line);
					average += newPerson->course_info.marks[i];
				}
				average /= newPerson->course_info.no_of_units;
				newPerson->course_info.avg = average;
				// Testing line to print average as it's calculated.
				//printf("%.2f\n", average);

			}

			// Free the line malloc'd by getline.
			free(line);
			return newPerson;
		}
		// Run until create_person no longer returns anything.
		while((temp = create_person()) != NULL) {
			place_into_list(temp);
		}
		// Close file only after running create_person function since
		// it relies on it being open.
		fclose(Students_Details_FILE);

		// Display the results afterwards.
		display_students();
	}


	// Menu option 2 search_student
	void search_student(void) {
		printf("Please type the student's name. (caps insensitive) ");
		char needle[20];
		fflush(stdin);
		fgets(needle, 19, stdin);
		// Get rid of newline.
		for(int i = 0; needle[i] != '\0'; i++) {
			if(needle[i] == '\n') {needle[i] = '\0';}
			needle[i] = toupper(needle[i]);
		}
		printf("Searching for: %s\n\n", needle);
		Person haystack = Students_Details;
		size_t ammount_found_counter = 0;
		while(haystack != NULL) {
			char temp[20] = "";
			for(int i = 0;
				haystack->student_info.name[i] != '\0';
				i++) {
				temp[i] = toupper(haystack->student_info.name[i]);
			}
			if(strstr(temp, needle) != NULL) {
				display_single_student(haystack);
				ammount_found_counter++;
			}
			haystack = haystack->next;
		}
		printf("%d student(s) found.\n", ammount_found_counter);
	}

	// Menu option 3 find_maximum
	void find_maximum(void) {
		Person pos = Students_Details;
		Person highestpos = Students_Details;

		if(Students_Details != NULL) {
			// Determine highest average mark.
			while(pos->next != NULL) {
				if(	pos->next->course_info.avg >
					highestpos->course_info.avg) {
					highestpos = pos->next;
				}
				pos = pos->next;
			}

			printf(	"The highest average mark is held by %s\n",
					highestpos->student_info.name);
			display_single_student(highestpos);
		} else {
			printf("No student data to search.");
		}
	}

	// Menu option 4 find_failed
	void find_failed(void) {
		//while(pointer != NULL) {
		//	if(FAIL) {display_single_student(pointer)}
		//}

		printf(	"Displaying students who failed at least one subject."
				"(mark < 50)\n\n");

		Person pos = Students_Details;

		bool failcheck(Person checkme) {
			for(int i = 0;
				i < checkme->course_info.no_of_units;
				i++) {
				if(checkme->course_info.marks[i] < 50) {return true;}
			}
			return false;
		}

		while(pos != NULL) {
			if(failcheck(pos)) {display_single_student(pos);}
			pos = pos->next;
		}
	}

	// Menu option 5 update_file
	// Open the file and add new student details.
	void update_file(void) {
		// Append new details to file.
		Students_Details_FILE = open_file("a");

		char uinstring[20] = "";
		size_t uinint = 0;

		void remove_newline_char(char *purify) {
			for(int i = 0; i < strlen(purify); i++) {
				if(purify[i] == '\n') {purify[i] = '\0';}
			}
		}

		printf("Add new student to file\n");

		void textin(const char *askfor, const size_t textin_len) {
			strcpy(uinstring, "");
			while(strlen(uinstring) == 0) {
				printf("%s", askfor);
				fflush(stdin);
				fgets(uinstring, textin_len, stdin);
				remove_newline_char(uinstring);
				if(strlen(uinstring) == 0) {
					printf("ERROR: String empty.\n");
				}
			}
			fprintf(Students_Details_FILE, "%s\n", uinstring);
		}

		textin("Name : ", 19);
		textin("ID : ", 9);
		textin("Course name : ", 19);

		uinint = 5;
		while(uinint > 4) {
			printf("Number of units (Max 4) : ");
			uinint = user_input_number();
			if(uinint > 4) {
				printf("ERROR: Maximum number of units == 4\n");
			}
		}
		fprintf(Students_Details_FILE, "%d\n", uinint);

		for(int i = uinint; i > 0; i--) {
			uinint = 101;
			while(uinint < 0 || uinint > 100) {
				printf("Mark (0-100) : ");
				uinint = user_input_number();
				if(uinint < 0 && uinint > 100) {
					printf("ERROR: Mark not within range (0-100)\n");
				}
			}
			fprintf(Students_Details_FILE, "%d\n", uinint);
		}

		fclose(Students_Details_FILE);


		// Re-parse the file.
		// Average is calculated in here.
		read_file();
	}

	// Menu option 0 debug_menu
	void debug_menu(void) {
		printf("\n\n\nDebug menu\n\n\n");
		printf("incomplete\n");
	}



	// Main menu
	bool menu(void) {
		void clear(void) {
			for(int i = 0; i < 100; i++) {printf("\n");}
		}
		clear();

		void anykey(void) {
			printf("Press enter to continue...\n");
			// Take input but ignore it in order to halt the terminal.
			user_input_number();
		}

		printf(	"\n"
				"    ,---.|             |          |        \n"
				"    `---.|--- .   .,---|,---.,---.|---     \n"
				"        ||    |   ||   ||---'|   ||        \n"
				"    `---'`---'`---'`---'`---'`   '`---'    \n"
				"                                           \n"
				"      |              |                     \n"
				"      |    ,---.,---.|__/ .   .,---.       \n"
				"      |    |   ||   ||  \\ |   ||   |       \n"
				"      `---'`---'`---'`   ``---'|---'       \n"
				"                               |           \n"
				"\n"
				"(1) Display students' details\n"
				"(2) Search for a student's marks\n"
				"(3) Find the student with the highest average mark\n"
				"(4) Display students who have failed subjects\n"
				"(5) Add a new student to the record\n"
				"(6) Quit program\n"
				"\n");
		switch(user_input_number()) {
			case 1:
				clear();
				display_students();
				anykey();
				break;
			case 2:
				clear();
				search_student();
				anykey();
				break;
			case 3:
				clear();
				find_maximum();
				anykey();
				break;
			case 4:
				clear();
				find_failed();
				anykey();
				break;
			case 5:
				clear();
				update_file();
				anykey();
				break;
			case 0:
				debug_menu();
				anykey();
				break;
			default:
				printf("Exiting");
				fflush(stdout);
				for(int i = 0; i < 5; i++) {
					usleep(500000);
					printf(".");
					fflush(stdout);
				}
				printf("\n");
				return false;
		}
		return true;
	}
	// Make sure the data is read from the file before starting.
	read_file(Students_Details_FILE);
	// Loop the menu till the menu returns false.
	while(menu()) {}

	clean_up_Students_Details();


	return 0;
}
