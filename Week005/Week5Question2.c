#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct LL {
	int integer;
	struct LL * next;
};

typedef struct LL ll_struct;
typedef ll_struct * ll;


void cleanup(ll * freethis);
void print_list(ll * printthis);
void print_list_in_reverse(ll * printthis);


int main(void) {
	// Create the linked list to work on.
	ll list0 = NULL;


	// Dump random values into the list.
	for(int i = 0; i < 10; i++) {
		ll newll = (ll_struct*) malloc(sizeof(ll_struct));
		newll->integer = i;
		newll->next = list0;
		list0 = newll;
	}


	print_list(&list0);


	print_list_in_reverse(&list0);


	// Clean up memory.
	cleanup(&list0);


	return 0;
}


// Collapse and free ll *arg1.
void cleanup(ll * freethis) {
	while(*freethis != NULL) {
		ll temp = *freethis;
		*freethis = (*freethis)->next;
		free(temp);
	}
}


// Print contents of ll *arg1.
void print_list(ll * printthis) {
	// Print linked list contents onto screen.
	for(ll ll_pos = *printthis; ll_pos != NULL; ll_pos = ll_pos->next) {
		printf("%d", ll_pos->integer);
	}
	printf("\n");
}


void print_list_in_reverse(ll * printthis) {
	bool printfunc(ll ptr) {
		if(ptr->next != NULL) {
			printfunc(ptr->next);
		}
		printf("%d", ptr->integer);
	}
	printfunc(*printthis);
	printf("\n");
}
