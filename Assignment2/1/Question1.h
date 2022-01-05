// Question1.h


// typedef laziness.
typedef FILE * FPTR;


// Game data.
typedef struct Game_Data {
	char name[50];
}game_data;


// Order data.
typedef struct Order_Data {
	int id;
	game_data contents;
}order_data;


// Union for storing different pointers inside the data section of the ll.
typedef union StructVariant {
	game_data game;
	order_data order;
}structVariant;


// Customer orders linked list.
typedef struct LL {
	structVariant * data;
	struct LL * next;
}ll;




// Print a bunch of endlines to screen to clear it the lazy way.
void clear_screen(void) {
	const size_t line_count = 100;
	for(int i = 0; i < line_count; i++) {
		printf("\n");
	}
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


// Take user input, return int.
int user_input_int(void) {
	char input[128];
	fflush(stdin);
	fgets(input, 127, stdin);
	return atoi(input);
}


void user_input_char(char (*input)[50]) {
	fflush(stdin);
	fgets(*input, 49, stdin);
	// Make sure there's a carriage return before the '\0'.
	for(int i = 0; 50 > i && '\0' != (*input)[i]; i++) {
		if('\0' == (*input)[i + 1]) {
			(*input)[i] = '\n';
		}
	}
}




// LL PUSH
// Both accept:
// ll ** to the node to be pushed and
// ll ** to the head of the list.
// HEAD
// Push a node into the head of a singly linked list.
void ll_push(ll ** pushme, ll ** goeshere) {
	(*pushme)->next = *goeshere;
	*goeshere = *pushme;
}

// TAIL
// Push a node into the tail of a singly linked list using the head as a
// reference point.
void ll_tail_push(ll ** pushme, ll ** goeshere) {
	ll * temp = *goeshere;
	if(temp != NULL) {
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = *pushme;
	} else {
		*goeshere = *pushme;
	}
}


// LL POP
// Both accept:
// ll ** to the head of the list.
// Both return:
// ll * to the popped node.
// HEAD
// Pop a node off of the head of a singly linked list.
ll * ll_pop(ll ** popme) {
	// Save the pointer to the head.
	ll * temp = *popme;
	// Shift the head down one.
	*popme = (*popme)->next;
	// Make sure it's ->next is NULL so that it no longer points back to this list.
	temp->next = NULL;
	// Return the severed head.
	return temp;
}

// TAIL
// Pop a node of the tail of a singly linked list using the head as a reference
// point.
ll * ll_tail_pop(ll ** popme) {
	ll * tail = *popme;
	// Stop stepping through when next == NULL.
	while(	tail != NULL &&
			tail->next != NULL) {
		tail = tail->next;
	}

	ll * tail_prev = *popme;
	if(tail_prev->next != NULL) {
		// The list is more than one item long.
		// Stop stepping through when next == tail.
		while(	tail_prev != NULL &&
				tail_prev->next != NULL &&
				tail_prev->next != tail) {
			tail_prev = tail_prev->next;
		}
		tail_prev->next = NULL;
	} else {
		// The list is only one item long.
		*popme = NULL;
	}

	// Make sure it's ->next is NULL so that it no longer points back to this list.
	tail->next = NULL;

	return tail;
}


// Create a node to be pushed onto a linked list.
ll * ll_new_node(void) {
	// Create a new node with a null pointer.
	ll * new_node_p = NULL;
	new_node_p = (ll*) malloc(sizeof(ll));
	new_node_p->next = NULL;
	//new_node_p->data.game = NULL;

	// Give the node it's data.
	new_node_p->data = (structVariant*) malloc(sizeof(structVariant));

	return new_node_p;
}


// Free up an ll and it's data.
void ll_free(ll ** freethis) {
	if(freethis != NULL) {
		while(*freethis != NULL) {
			// Because the list is NULL terminated,
			// *freethis ends up getting set to null once we reach the end.
			ll * temp = ll_pop(freethis);
	
			// Check if this is the correct way to do this.
			free(temp->data);
	
			// Free the actual link in the list.
			free(temp);
		}
	}
}


// Remove a specific element from the list n jumps from the head.
// head == 0
ll * ll_remove_by_index(ll ** head, const size_t node_index) {
	ll * pointernode = ll_new_node();
	ll * temp = pointernode;
	temp->next = *head;

	// Find the node before the one to be removed.
	for(	int i = 0;
			node_index - 1 > i &&
			head != NULL;
			i++) {
		temp = temp->next;
	}
	// Check it isn't a NULL pointer.
	if(temp == NULL) {
		// The index pointed past the end of the list.
		fprintf(stderr, "Invalid index.\n");
		return NULL;
	}

	// Make a join around it then return it by way of pointer.
	ll * removed = temp->next;
	temp->next = removed->next;
	// Make sure it's ->next is NULL
	// so that it no longer points back to this list.
	removed->next = NULL;
	// Make sure if the head was the node that was removed then the head is set
	// to the next node down.
	*head = pointernode->next;
	// This MUST be NULL so that ll_free doesn't free the whole list.
	pointernode->next = NULL;
	ll_free(&pointernode);

	return removed;
}


