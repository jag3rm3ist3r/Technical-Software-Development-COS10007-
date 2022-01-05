#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


struct CharChain {
	char stored_character;
	struct CharChain * next;
};
typedef struct CharChain cc;
typedef cc * cc_ptr;
cc_ptr head0 = NULL;
cc_ptr head1 = NULL;


cc_ptr push(cc_ptr * h, char c);
cc_ptr pop(cc_ptr * h);
void nukelist(cc_ptr * h);


int main(void) {
	// Take user input.
	printf(	"Palindrome tester\n"
			"Type a string to be tested.\n");
	char input[100];
	fgets(input, 99, stdin);
	printf("\n");

	// Push string to stack removing non alnum.
	for(int i = 0; i < strlen(input); i++) {
		if(isalnum(input[i]) != 0) {
			push(&head0, tolower(input[i]));
			// Printing the original string here so that I don't have to create
			// a loop just to print it from.
			printf("%c", tolower(input[i]));
		}
	}
	printf("\n");

	// Copy contents of stack to new stack in reverse order.
	cc_ptr temp = head0;
	while(temp != NULL) {
		push(&head1, temp->stored_character);
		temp = temp->next;
	}

	// Compare contents of stacks.
	bool same = true;
	while(head0 != NULL) {
		// This is where the reversed loop is printed.
		printf("%c", head0->stored_character);
		if(head0->stored_character != head1->stored_character) {
			same = false;
		}
		free(pop(&head0));
		free(pop(&head1));
	}
	printf("\n\n");

	// Tell the user if the input was a palindrome.
	if(same == true) {
		printf("This is a palindrome.\n");
	} else {
		printf("This is not a palindrome.\n");
	}

	// Cleanup. (Just in case there's something left of these lists somehow.)
	nukelist(&head0);
	nukelist(&head1);

	return 0;
}


cc_ptr push(cc_ptr * h, char c) {
	cc_ptr newcc = (cc*) malloc(sizeof(cc));
	newcc->stored_character = c;
	newcc->next = *h;
	*h = newcc;
	return newcc;
}

cc_ptr pop(cc_ptr * h) {
	cc_ptr p = *h;
	*h = (*h)->next;
	return p;
}

void nukelist(cc_ptr * h) {
	while(*h != NULL) {
		cc_ptr temp = *h;
		*h = (*h)->next;
		free(temp);
	}
}
