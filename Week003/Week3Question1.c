#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int main(void) {
	/* Wait 1 second to make sure that the time isn't the same when we run this
	 * program again. */
	sleep(1);
	/* Setup random number generation. */
	srandom(time(NULL));

	/* Singly linked list. */
	struct llstruct {
		int integer;
		struct llstruct *next;
	};
	typedef struct llstruct ll;
	typedef ll *ll_ptr;

	/* Pointers to locations in the list. */
	ll_ptr index = NULL;
	ll_ptr curr = NULL;


	/* Fill out contents of list with random values. */
	for(int i = 0; i < 10; i++) {
		curr = (ll*) malloc(sizeof(ll));
		curr->integer = random() % 51;
		curr->next = index;
		index = curr;
	}

	/* Print the list. */
	while(curr != NULL) {
		printf("%d ", curr->integer);
		curr = curr->next;
	}

	/* Put a newline between and reset the value of curr. */
	printf("\n");
	curr = index;

	/* Calculate the average. */
	float average = 0.00;
	while(curr != NULL) {
		average += (float) curr->integer;
		curr = curr->next;
	}
	average /= 10.00;
	printf("Average: %.2f\n", average);

	/* Free memory. */
	while(index != NULL) {
		curr = index->next;
		free(index);
		index = curr;
	}


	return 0;
}
