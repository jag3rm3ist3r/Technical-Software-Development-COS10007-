#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/*
 *
 * Assignment 1 Section A Question 3
 *
 */


// I'm using line comments instead of block comments deal with it.


// !!! FIXED PART OF ASSIGNMENT DO NOT CHANGE !!!
struct Bus {
	// Unique value. Example: 1
	int BusID;
	// Unique value. Example: 1001
	int RouteID;
	// Scheduled departure time
	time_t schedule;
};
// !!! END FIXED PART OF ASSIGNMENT !!!


// Typedef laziness.
typedef struct Bus bus;
typedef bus * bus_ptr;


// !!! FIXED PART OF ASSIGNMENT DO NOT CHANGE !!!
bus Depot[10];
// !!! END FIXED PART OF ASSIGNMENT !!!


// FUNCTION PROTOTYPES

// This is to keep the menu happy so I don't have it resetting it
// to a null pointer every time the menu loops.
bus_ptr Depot_pointer = NULL;

bool menu(void);

void clear(void);

int userinputint(void);

void printBuses(void);

bus_ptr createBuses(void);

void scheduleBuses(void);

void alignupBuses(void);

struct Bus_ll {
	int BusID;
	int RouteID;
	time_t schedule;
	struct Bus_ll * next;
};

// Typedef laziness.
typedef struct Bus_ll bus_ll;
typedef bus_ll * bus_ll_ptr;

// Lazy pile of global variables so I don't have to pass the variable
// into functions as often.
bus_ll_ptr Depot_ll_head = NULL;
bus_ll_ptr Depot_ll_pos = NULL;
bus_ll_ptr Depot_ll_tail = NULL;

bus_ll_ptr releaseBus(bus_ll_ptr prev_head);

bus_ll_ptr emergency(bus_ll_ptr prev_tail);

void cleanup(void);

void debug_menu(void);


int main(void) {
	srandom(time(NULL));


	// Loop the main menu till it returns false.
	while(menu()){}


	// Free the memory that was allocated to the linked list.
	cleanup();


	return 0;
}


// Menu : Looped from main function until it returns false.
bool menu(void) {
	clear();


	printf(	"Bus depot scheduling program\n\n"
			"1 : Initialize depot\n"
			"2 : Print depot contents\n"
			"3 : Schedule buses\n"
			"4 : Align buses\n"
			"5 : Release bus\n"
			"6 : Emergency release bus\n"
			"7 : Exit program\n\n");


	// Generic error message for the menu to display when the depot
	// hasn't been initialized yet.
	void depoterror(void) {
		printf("The Depot hasn't been initialized yet.\n");
	}

	// Generic error message for when the alignupBuses function
	// hasn't been run yet.
	void alignerror(void) {
		printf(	"The depot hasn't been aligned yet or there are no "
				"buses in the list.\n"
				"You may realign the buses to repopulate the list if "
				"you have initialized the depot already.\n");
	}


	switch(userinputint()) {
		case 1:
			// init depot
			// Depot_pointer is for determining if the bus creation
			// function has run. It is NULL by default.
			if(Depot_pointer == NULL) {
				Depot_pointer = createBuses();
				printf("Depot initialized.\n");
			} else {
				printf("Depot already initialized.\n");
			}
			break;
		case 2:
			// print depot
			if(Depot_pointer != NULL) {
				printBuses();
			} else {
				depoterror();
			}
			break;
		case 3:
			// schedule depot
			if(Depot_pointer != NULL) {
				scheduleBuses();
				printf("Buses scheduled.\n");
			} else {
				depoterror();
			}
			break;
		case 4:
			// alignup buses
			alignupBuses();
			printf("Buses aligned.\n");
			break;
		case 5:
			// release buses
			if(Depot_ll_head != NULL) {
				free(releaseBus(Depot_ll_head));
			} else {
				alignerror();
			}
			break;
		case 6:
			// emergency release bus
			if(Depot_ll_head != NULL) {
				free(emergency(Depot_ll_tail));
			} else {
				alignerror();
			}
			break;
		case 0:
			// debug menu
			printf("Secret debug menu.\n");
			debug_menu();
			break;
		default:
			return false;
	}
	

	// Make sure to stop after running the function as we may want to
	// read what is on the screen.
	printf("Press any key to continue...");
	userinputint();
	return true;
}


// Clear the screen of any text the lazy way.
void clear(void) {
	// Ammount of newlines to print.
	const size_t newlinecount = 100;
	for(int i = 0; i < newlinecount; i++) {printf("\n");}
}


// Take user input and return int.
int userinputint(void) {
	char temp[32];
	fflush(stdin);
	fgets(temp, 31, stdin);
	return atoi(temp);
}


// Print the details of all the buses in the Depot array.
void printBuses(void) {
	for(int i = 0; i < 10; i++) {
		printf(	"Depot[%d]\n"
				"BusID : %d\n"
				"RouteID : %d\n"
				"schedule : %s\n\n",
				i,
				Depot[i].BusID,
				Depot[i].RouteID,
				ctime(&Depot[i].schedule));
	}
}


// Create 10 buses and store them in the Depot array.
// BusID and RouteID to be filled with random integer values.
// Schedule to be left blank.
bus_ptr createBuses(void) {
	for(int i = 0; i < 10; i++) {
		Depot[i].BusID = random() % 10000;
		Depot[i].RouteID = random() % 100;
	}
	return Depot;
}


// The departure time for each bus to be filled, refer to sample code.
void scheduleBuses(void) {
	for(int i = 0; i < 10; i++) {
		Depot[i].schedule = time(NULL)+random()%10000;
	}
}


// Buses to be rearranged in the Depot array based on each buses
// scedule.
// The earliest scheduled bus to be placed at the bottom of the Depot
// array.
void alignupBuses(void) {
	// Place for storing a bus that we will move.
	bus temp;

	// Rearrange array such that earliest is at the "bottom"
	// of the array, which I'm assuming is the end of the array.
	for(int i = 0; i < 10; i++) {
		for(int a = i + 1; a < 10; a++) {
			if(Depot_pointer[i].schedule < Depot_pointer[a].schedule) {
				// Switch positiions.
				temp = Depot_pointer[i];
				Depot_pointer[i] = Depot_pointer[a];
				Depot_pointer[a] = temp;
			}
		}
	}

	// Export the data to the linked list which is where the data
	// should have been in the first place.
	for(int i = 0; i < 10; i++) {
		bus_ll_ptr newBus = (bus_ll*) malloc(sizeof(bus_ll));
		newBus->BusID = Depot_pointer[i].BusID;
		newBus->RouteID = Depot_pointer[i].RouteID;
		newBus->schedule = Depot_pointer[i].schedule;
		if(Depot_ll_head == NULL) {
			Depot_ll_tail = newBus;
		}
		newBus->next = Depot_ll_head;
		Depot_ll_head = newBus;
	}
}


// Release one bus at a time from the Depot based on the schedule.
// Bus with the earliest schedule should leave the Depot first.
// Queue concept. (FIFO)
// Remove the head of the linked list, which will also be the bus
// with the earliest departure time.
bus_ll_ptr releaseBus(bus_ll_ptr prev_head) {
	Depot_ll_head = Depot_ll_head->next;

	// Return the pointer to the old head of the list in case it
	// needs to be used elsewhere. (It is freed in the menu function.)
	return prev_head;
}


// Release one bus at a time from the Depot,
// with the last scheduled bus to leave the Depot array first.
// Stack concept. (FILO)
// Remove the tail of the linked list, which will also be the bus
// with the latest departure time.
bus_ll_ptr emergency(bus_ll_ptr prev_tail) {
	// Find new tail. (2nd from end)
	// I don't actually need the pointer to the tail to do this,
	// I'm just using it to demonstrate that it's the tail of the list.
	// This while loop could just be:
	// while(Depot_ll_pos->next->next != NULL) {
	//     Depot_ll_pos = Depot_ll_pos->next;
	// }
	Depot_ll_pos = Depot_ll_head;
	if(Depot_ll_head != Depot_ll_tail) {
		while(Depot_ll_pos->next != Depot_ll_tail) {
			Depot_ll_pos = Depot_ll_pos->next;
		}
		// Set new tail.
		Depot_ll_tail = Depot_ll_pos;
		Depot_ll_tail->next = NULL;
	} else {
		Depot_ll_head = NULL;
		Depot_ll_tail = NULL;
	}

	// Return the pointer to the old tail of the list in case it
	// needs to be use elsewhere. (It is freed in the menu function.)
	return prev_tail;
}


// Print the linked list that isn't printed by the print function
// because the assignment has a stipulation that the printBuses 
// function uses an array instead of the linked list.
// The fact that I need this is absurd, whoever designed this
// assignment definitely didn't think it through propperly.
void debug_menu(void) {
	Depot_ll_pos = Depot_ll_head;
	while(Depot_ll_pos != NULL) {
		// Print whether this is considered to be the head of the list.
		if(Depot_ll_pos == Depot_ll_head) {printf("Head\n");}
		// Print whether this is considered to be the tail of the list.
		if(Depot_ll_pos == Depot_ll_tail) {printf("Tail\n");}

		// Print data stored in struct.
		printf("BusID : %d\n", Depot_ll_pos->BusID);
		printf("RouteID : %d\n", Depot_ll_pos->RouteID);
		printf("schedule : %s\n", ctime(&Depot_ll_pos->schedule));

		// Move to next position.
		Depot_ll_pos = Depot_ll_pos->next;
	}
}


// Cleanup function to free the data in the linked list.
// This doesn't free any items stripped from the linked list using:
// releaseBus()
// emergency()
// Those are freed elsewhere.
void cleanup(void) {
	while(Depot_ll_head != NULL) {
		Depot_ll_pos = Depot_ll_head;
		Depot_ll_head = Depot_ll_pos->next;
		free(Depot_ll_pos);
	}
}
