// Question1.c


// Correct ammount of arguments for program to expect.
#define ARG_COUNT 1


// atoi
#include <stdlib.h>
// Basic io
#include <stdio.h>
// Boolean type.
#include <stdbool.h>
// strcpy
#include <string.h>
// usleep
#include <unistd.h>
// Header file.
#include "Question1.h"


// Argument priority is as follows: (higher == leftmost)
// FPTR fp
// ll ** o
// ll ** g
// ll ** s
// char * _
ll * add_game(ll ** g, char * name);
ll * add_order(ll ** o, const size_t on);
int read_file(FPTR fp, ll ** g, const char * fn);
int write_file(FPTR fp, ll ** g, const char * fn);
void print_games_details(ll ** g);
void display_order(ll ** o);
void process_next_order(ll ** o, ll ** g, ll ** s);
void display_all_orders(ll ** o);
void cancel_last_order(ll ** o);
void display_next_order(ll ** o);
void display_completed_orders(ll ** s);


// argc == 2
// argv[2] == [this_file, games.txt]
int main(int argc, char *argv[]) {
	// Order numbers are sequential and start from 1337 because memes.
	size_t ordnum = 1337;
	// Pointer for storing the input file.
	FPTR fp = NULL;


	if(argc != ARG_COUNT + 1) {
		fprintf(stderr, "Invalid number of arguments, must be %d.\n", ARG_COUNT);
		return 1;
	}


	// Attempt to open last argument, parse to fill linked list.
	// Kill program if this fails.
	ll * games_ll = NULL;
	if(1 == read_file(fp, &games_ll, argv[ARG_COUNT])) {
		fprintf(stderr,
				"Failed to open file, check permissions.\n"
				"Filename: %s\n",
				argv[ARG_COUNT]);
		return 1;
	}

	if(games_ll == NULL) {
		printf("No games to sell.\nExiting...\n");
		return 1;
	}

	// Storage for orders.
	ll * orders_ll = NULL;

	// Storage for games that have been sold.
	ll * sold_ll = NULL;




	// Use this to pass to user_input_char.
	// like this: user_input_char(&input);
	char input[50] = "\0";
	bool menu(void) {
		clear_screen();
		printf("GENERIC GAMES STORE NAME HERE\n"
				"\n"
				"1 : Display current stock\n"
				"2 : Add a game to stock\n"
				"3 : Add an order\n"
				"4 : Cancel last order\n"
				"5 : Process next order\n"
				"6 : Display all orders\n"
				"7 : Display next order\n"
				"8 : Display completed orders\n"
				"9 : Update games file\n"
				"10 : Exit\n"
				"\n"
				"\n");
		switch(user_input_int()) {
			case 1:
				clear_screen();
				printf("Print available stock.\n\n");
				print_games_details(&games_ll);
				break;
			case 2:
				clear_screen();
				printf("Add a game to stock.\n\n");
				printf("Adding a new game:\n"
						"\n"
						"Name: ");
				user_input_char(&input);
				if(1 < strlen(input)) {
					add_game(&games_ll, input);
				} else {
					printf("Error: Input too short.\n");
				}
				break;
			case 3:
				clear_screen();
				printf("Add an order.\n\n");
				printf(	"Order #%d added to queue.\n",
						(add_order(&orders_ll, ordnum++))->data->order.id);
				break;
			case 4:
				clear_screen();
				printf("Cancel last order.\n\n");
				cancel_last_order(&orders_ll);
				break;
			case 5:
				clear_screen();
				printf("Process next order.\n\n");
				process_next_order(&orders_ll, &games_ll, &sold_ll);
				break;
			case 6:
				clear_screen();
				printf("Display all orders.\n\n");
				display_all_orders(&orders_ll);
				break;
			case 7:
				clear_screen();
				printf("Display next order.\n\n");
				display_next_order(&orders_ll);
				break;
			case 8:
				clear_screen();
				printf("Display completed orders.\n\n");
				display_completed_orders(&sold_ll);
				break;
			case 9:
				clear_screen();
				printf("Update games stock file.\n\n");
				if(0 == write_file(fp, &games_ll, argv[ARG_COUNT])) {
					printf("Write success.\n");
				} else {
					fprintf(stderr, "Failed to open file for writing.\n");
				}
				break;
			case 10:
				clear_screen();
				printf("Quit.\n\n");
				printf("Exiting...\n");
				return false;
			default:
				// No option selected, just reprint menu.
				return true;
		}
		printf("\n\nPress enter to continue.\n");
		user_input_int();
		return true;
	}
	// Loop menu till it returns false.
	while(menu()) {}


	// Cleanup.
	ll_free(&games_ll);
	ll_free(&orders_ll);
	ll_free(&sold_ll);


	return 0;
}


// Print the names of the games.
void print_games_details(ll ** g) {
	if(g != NULL) {
		for(	ll * temp = *g;
				temp != NULL;
				temp = temp->next) {
			printf("%s", temp->data->game.name);
		}
	} else {
		printf("No games to sell.\n");
	}
}


// Add a new game to the game stock ll.
ll * add_game(ll ** g, char * name) {
	// Sanity check.
	if(g != NULL) {
		ll * newgame = ll_new_node();
		strcpy(newgame->data->game.name, name);
		ll_push(&newgame, g);
		return newgame;
	}
}


// Scan file for games into a ll, return a pointer to the start of the ll.
// Accepts:
// Filename
// File pointer
// ** to ll of games
// Returns:
// int (For error reporting)
int read_file(FPTR fp, ll ** g, const char * fn) {
	if(open_file(fn, &fp, "r") == 1) {return 1;}
	char * line = NULL;
	size_t len = 0;
	while((getline(&line, &len, fp)) != -1) {
		// Spawn a new node.
		ll * temp_new_game = ll_new_node();
		// Give it game details.
		strcpy(temp_new_game->data->game.name, line);
		// Push it to the games list that will be returned.
		ll_push(&temp_new_game, g);
	}
	// Line will be malloc'd by getline, free the memory.
	free(line);
	fclose(fp);
	return 0;
}


// Write games to file.
// Accepts:
// Filename
// File pointer
// ** to ll of games
// Returns:
// int (For error reporting)
int write_file(FPTR fp, ll ** g, const char * fn) {
	if(open_file(fn, &fp, "w") == 1) {return 1;}
	for(	ll * temp_games_p = *g;
			temp_games_p != NULL;
			temp_games_p = temp_games_p->next) {
		// Write each game to the file.
		fprintf(fp, "%s", temp_games_p->data->game.name);
	}
	fclose(fp);
	return 0;
}


// Add a new order to the customer order ll.
ll * add_order(ll ** o, const size_t on) {
	ll * neworder = ll_new_node();
	neworder->data->order.id = on;
	printf("Input name of game to be ordered (order ID: %d): ", on);
	user_input_char(&neworder->data->order.contents.name);
	ll_tail_push(&neworder, o);
	return neworder;
}


// Display details of a single order.
// For use in other functions to keep output consistent.
void display_order(ll ** o) {
	// Sanity check.
	if(o != NULL && *o != NULL) {
		printf("Order ID: %d\n", (*o)->data->order.id);
		printf("Order contents: %s\n", (*o)->data->order.contents.name);
		printf("\n");
	}
}


// !!! ISSUE !!!
// (refer to comment in func)
// Search for a game in the linked list, then return it's location.
// Returns -1 if not found or if the list is NULL.
int search_for_game(ll ** g, char * name) {
	if(g != NULL && *g != NULL) {
		// For storing location in list by index from head.
		size_t i = 0;
		for(ll * temp = *g; temp != NULL; temp = temp->next) {
			i++;
			// Dumb search with strcmp, may need to be changed to strstr.
			if(0 == strcmp(temp->data->game.name, name)) {
				return i;
			}
		}
	} else {
		printf("Nothing to display.");
	}
	return -1;
}


// Process the order at the head of the ll, place the sold game in the sold ll.
void process_next_order(ll ** o, ll ** g, ll ** s) {
	// Sanity check.
	if(o != NULL && *o != NULL) {
		// Grab the next order.
		ll * ordertemp = ll_pop(o);
		// This is for storing the game that is found and removed from the list.
		ll * gametemp = NULL;


		// search_for_game will return -1 when not found.
		int gameindex = search_for_game(g, ordertemp->data->order.contents.name);
		if(0 > gameindex) {
			// Game was not found.
			// There is a small issue where the game has a \n in the name,
			// which makes this printf split to two lines unintentionally.
			// I can't be bothered fixing this because it's unimportant.
			printf(	"The game: %s"
					"is currently not available, "
					"order sent to end of queue.",
					ordertemp->data->order.contents.name);

			// Push the order back to the tail as it is unavailable right now
			// and there are other orders to be filled..
			ll_tail_push(&ordertemp, o);
		} else {
			// Game was found gameindex is a positive value.
			gametemp = ll_remove_by_index(g, (size_t) gameindex);
			// This will fill the order's details out with any extra information
			// that the game knows about itself.
			ordertemp->data->order.contents = gametemp->data->game;
			// We don't need the game any more because it has been bought.
			ll_free(&gametemp);
			// Push the order into the completed orders ll.
			printf("Order processed: \n");
			display_order(&ordertemp);
			// Dump the order in the completed orders list.
			ll_push(&ordertemp, s);
		}
	} else {
		printf("There are no orders in the queue.");
	}
}


// Display all orders in the customer orders ll.
void display_all_orders(ll ** o) {
	// Sanity check.
	if(o != NULL && *o != NULL) {
		// List is ! NULL, step through orders and display them.
		for(ll * temp = *o; temp != NULL; temp = temp->next) {
			display_order(&temp);
		}
	} else {
		printf("No orders in the queue.\n");
	}
}


// Remove the last order that was created from the tail of the ll.
void cancel_last_order(ll ** o) {
	// Sanity check.
	if(o != NULL && *o != NULL) {
		ll * temp = ll_tail_pop(o);
		printf("Order removed.\n");
		display_order(&temp);
		ll_free(&temp);
	} else {
		printf("No orders in the queue.\n");
	}
}


// Display the next order in the queue.
void display_next_order(ll ** o) {
	// Sanity check.
	if(o != NULL && *o != NULL) {
		display_order(o);
	} else {
		printf("No orders in the queue.\n");
	}
}


// Display the order at the end of the ll.
void display_completed_orders(ll ** s) {
	// Sanity check.
	if(s != NULL && *s != NULL) {
		for(ll * temp = *s;
			temp != NULL;
			temp = temp->next) {
			display_order(&temp);
		}
	} else {
		printf("No completed orders.\n");
	}
}


