// 103112063.c
// Test




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Structure for holding employee data.
typedef struct{
	char name[20];
	int age;
}personTag;

typedef struct{
	int deptId;
	char cmpName[20];
	float salary;
}officialTag;

typedef struct employeeTag employeeTag;
typedef employeeTag * ll_ptr;
struct employeeTag{
	personTag personalInfo;
	officialTag officialInfo;
	ll_ptr next;
};


// Head of list.
ll_ptr ll_head = NULL;
ll_ptr ll_curr = NULL;
typedef FILE * FPTR;
int open_file(	const char * file_to_open,
				FPTR * fpp,
				const char * mode);
int read_file(FPTR fp, ll_ptr llist, const char *fn);
ll_ptr new_emp(char *name, int age, int deptId, char *cmpName, float salary);
void ll_push(ll_ptr *pushme);
ll_ptr ll_pop(void);
void ll_print(ll_ptr *readme);
void ll_free(ll_ptr *freethis);
// Take user input, return int.
int user_input_int(void);
void user_input_char(char (*input)[20]);


bool menu(void) {
	printf(
			"\n\n\n\n\n\n\n\n\n"
			"1 : Display employee details\n"
			"2 : Search for employees\n"
			"3 : Display employee with highest salary\n"
			"4 : Display average salary across a company\n"
			"-1: Exit\n"
		  );

	switch(user_input_int()) {
		case 1:
			printf("Employee Details\n");
			ll_curr = ll_head;
			while(ll_curr != NULL) { 
				ll_print(&ll_curr);
				ll_curr = ll_curr->next;
			}
			break;
		case 2:
			printf("Employee Search\n");
			printf("Type an employee name: ");
			ll_curr = ll_head;
			char input[20];
			user_input_char(&input);
			while(	strcmp(ll_curr->personalInfo.name, input) != 0 &&
					ll_curr != NULL) {
				ll_curr = ll_curr->next;
			}
			if(ll_curr == NULL) {
				printf("Employee not found.\n");
			} else {
				ll_print(&ll_curr);
			}
			break;
		case 3:
			printf("Highest Salary\n");
			break;
		case 4:
			printf("Average Salary\n");
			break;
		case -1:
			printf("Exit\n");
			return false;
		default:
			break;
	}
	return true;
}


int main(int argc, char *argv[]) {
	// Check there was only one argument.
	if(argc != 2) {
		fprintf(stderr,
				"ERROR: INCORRECT NUMBER OF ARGUMENTS. "
				"FILE INPUT REQUIRED.\n");
		return 1;
	}

	// Open the file passed as an argument;
	FPTR fp = NULL;

	// Read contents of file into memory.
	read_file(fp, ll_head, argv[1]);
	


	// Loop the menu.
	while(menu()) {}
	


	ll_free(&ll_head);
	ll_head = NULL;
	ll_curr = NULL;


	return 0;
}




// Take user input, return int.
int user_input_int(void) {
	char input[128];
	fflush(stdin);
	fgets(input, 127, stdin);
	return atoi(input);
}

void user_input_char(char (*input)[20]) {
	fflush(stdin);
	fgets(*input, 19, stdin);
	// Make sure there's a carriage return before the '\0'.
	for(int i = 0; 20 > i && '\0' != (*input)[i]; i++) {
		if('\0' == (*input)[i + 1]) {
			(*input)[i] = '\n';
		}
	}
}

// Create a new link for the list but do not place it.
// name
// age
// deptId
// cmpName
// salary
ll_ptr new_emp(char *name, int age, int deptId, char *cmpName, float salary) {
	ll_ptr ll_new = malloc(sizeof(employeeTag));
	strcpy(ll_new->personalInfo.name, name);
	ll_new->personalInfo.age = age;
	ll_new->officialInfo.deptId = deptId;
	strcpy(ll_new->officialInfo.cmpName, cmpName);
	ll_new->officialInfo.salary = salary;
	// Make sure the end of the list is NULL terminated.
	ll_new->next = NULL;
}


// Pass a pointer to push to the head.
void ll_push(ll_ptr *pushme) {
	(*pushme)->next = ll_head;
	ll_head = *pushme;
}


// Pop head of list return old head, but do not free it.
ll_ptr ll_pop(void) {
	ll_ptr tmp = ll_head;
	ll_head = ll_head->next;
	return tmp;
}


// Open file, return int depending on if successful.
int open_file(	const char * file_to_open,
				FPTR * fpp,
				const char * mode) {
	if((*fpp = fopen(file_to_open, mode)) == NULL) {
		fprintf(stderr, "Failed to open file.");
		return 1;
	} else {
		return 0;
	}
}


// Accepts:
// Filename
// File pointer
// ** to ll of games
// Returns:
// int (For error reporting)
int read_file(FPTR fp, ll_ptr llist, const char * fn) {
	if(open_file(fn, &fp, "r") == 1) {return 1;}
	char * line = NULL;
	size_t len = 0;
	/*
	while((getline(&line, &len, fp)) != -1) {
		// Spawn a new node.
		// Give it details.
		// Push it to the list that will be returned.
	}
	*/
	// Temp variables.
	char tmpname[20];
	int tmpage;
	int tmpdeptId;
	char tmpcmpName[20];
	float tmpsalary;
	// Ignore first line.
	getline(&line, &len, fp);
	free(line);
	// Read lines into temp variables.
	while(
		(fscanf(fp, "%s %d %d %s %f",
				tmpname,
				&tmpage,
				&tmpdeptId,
				tmpcmpName,
				&tmpsalary) != -1)
		) {
		// Debug code.
		/*
		printf("%s %d %d %s %.2f\n",
				&tmpname,
				tmpage,
				tmpdeptId,
				&tmpcmpName,
				tmpsalary);
		*/
		// Make new employee.
		ll_ptr ll_new = new_emp(tmpname,
								tmpage,
								tmpdeptId,
								tmpcmpName,
								tmpsalary);
		// Put at head of linked list.
		ll_push(&ll_new);
	}
	/*
	// Line will be malloc'd by getline, free the memory.
	free(line);
	*/
	fclose(fp);
	return 0;
}


void ll_print(ll_ptr *readme) {
	ll_ptr ll_tmp = *readme;
	printf(	"%s\t\t%d\t\t%d\t\t%s\t\t%.2f\n",
			ll_tmp->personalInfo.name,
			ll_tmp->personalInfo.age,
			ll_tmp->officialInfo.deptId,
			ll_tmp->officialInfo.cmpName,
			ll_tmp->officialInfo.salary);
}


void ll_free(ll_ptr *freethis) {
	if(freethis != NULL) {
		while(*freethis != NULL) {
			// Because the list is NULL terminated,
			// *freethis ends up getting set to null once we reach
			//+the end.
			ll_ptr temp = ll_pop();
			// Free the actual link in the list.
			free(temp);
		}
	}
}
