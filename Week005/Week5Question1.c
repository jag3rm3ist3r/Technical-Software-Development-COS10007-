#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct LL {
	char character;
	struct LL * next;
};

typedef struct LL ll_struct;
typedef ll_struct * ll;


void cleanup(ll * freethis);
void print_list(ll * printthis);


int main(void) {
	// Setup random number generation.
	srandom(time(NULL));


	// Create the linked list to work on.
	ll list0 = NULL;


	// Dump random values into the list.
	for(int i = 0; i < 10; i++) {
		ll newll = (ll_struct*) malloc(sizeof(ll_struct));
		newll->character = random() % 26 + 97;
		newll->next = list0;
		list0 = newll;
	}


	print_list(&list0);


	// Reverse the order of the list.
	ll prev = NULL;
	ll next = list0;
	while(next != NULL) {
		next = list0->next;
		list0->next = prev;
		prev = list0;
		if(next != NULL) {list0 = next;}
	}


	print_list(&list0);


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
		printf("%c", ll_pos->character);
		printf(" -> ");
	}
	printf("NULL\n");
}
