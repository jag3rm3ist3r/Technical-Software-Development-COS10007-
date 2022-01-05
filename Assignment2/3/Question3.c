// Question3.c




// basic io
#include <stdio.h>
// atoi
#include <stdlib.h>
// Boolean return from menu
#include <stdbool.h>
// strcpy
#include <string.h>

// Header file
#include "Question3.h"




int main(int argc, char *argv[]) {
	const char namelist[4][50] = {
		{"Jerry Seinfeld"},
		{"George Costanza"},
		{"Cosmo Kramer"},
		{"Elaine Benes"},
	};
	// Newman
	// The Soup Nazi
	// Lloyd Braun
	// Mickey Abbott
	// Uncle Leo
	// George Steinbrenner


	// Make a list of employees.
	// Give random ids and salaries to the employees and assign them a name from
	// the list of valid names.
	employee Employees[10];
	// Create 4 fixed employees that never change names, but with random ids and
	// salary.
	for(int i = 0; i < 4; i++) {
		Employees[i].id = random() % 10000 + 1;
		strcpy(Employees[i].name, namelist[i]);
		Employees[i].salary = random() % 50000 + 40001;
	}
	// Let the user decide the rest.
	for(int i = 4; i < 10; i++) {
		Employees[i].id = random() % 10000 + 1;
		printf("Input a name for employee #%d: ", Employees[i].id);
		char tempname[50];
		user_input_char(tempname);
		strcpy(Employees[i].name, tempname);
		Employees[i].salary = random() % 50000 + 40001;
	}


	// Print an employee's details.
	void print_employee(employee e) {
		printf(	"ID\t:\t%d\n"
				"Name\t:\t%s\n"
				"Salary\t:\t$%d\n\n",
				e.id,
				e.name,
				e.salary);
	}


	// Print all employees' details.
	void print_employees(void) {
		for(int i = 0; i < 10; i++) {
			print_employee(Employees[i]);
		}
	}


	// Main menu.
	bool menu(void) {
		printf(	"EMPLOYEE RECORD SEARCH\n"
				"\n"
				"\n"
				"1  :  Print all employee details\n"
				"2  :  Linear search by id\n"
				"3  :  Binary search by id\n"
				"10 :  Exit\n"
				"\n");
		char input[100];
		// The function call was too long so I stored the bulk of it in this.
		int temp;
		switch(user_input_int()) {
			case 1:
				print_employees();
				break;
			case 2:
				printf(	"Which employee id are you linear searching for? ");
				temp = linear_search(
					Employees,
					sizeof(Employees) / sizeof(*Employees),
					user_input_int()
				);
				if(temp >= 0) {
					print_employee(Employees[temp]);
				} else {
					printf("Employee not found.\n");
				}
				break;
			case 3:
				printf(	"Which employee id are you binary searching for? ");
				temp = binary_search(
					Employees,
					sizeof(Employees) / sizeof(*Employees),
					user_input_int()
				);
				if(temp >= 0) {
					print_employee(Employees[temp]);
				} else {
					printf("Employee not found.\n");
				}
				break;
			case 10:
				return false;
			default:
				return true;
		}
		printf("Press enter to continue...\n");
		user_input_int();
		return true;
	}


	// Sort the array so that the binary search works on it.
	for(int i = 1; i < 10; i++) {
		for(int j = i; j > 0 && Employees[j - 1].id > Employees[j].id; j--) {
			employee temp = Employees[j - 1];
			Employees[j - 1] = Employees[j];
			Employees[j] = temp;
		}
	}
	// Loop the menu.
	while(menu()) {}


	printf("Exiting...\n");


	return 0;
}


