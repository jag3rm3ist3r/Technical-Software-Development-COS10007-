// Week9Question3.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Week9Question3.h"


int main(void) {
	// Take user input.
	printf("Please enter a sentence no longer than 100 characters.\n");
	char input[100];
	fgets(input, 99, stdin);
	//printf(input);
	printf("\n");


	// There is a bug where the program will consider leading whitespace to be a
	// word instead of ignoring it and starting at the first valid character but
	// I can't be bothered fixing it.

	// Cut the words up into individual strings and place them into the stack.
	size_t cache_pos = 0;
	char cache[100] = "";
	for(int i = 0; i < strlen(input); i++) {
		if(input[i] != ' ' && input[i] != '\0' && input[i] != '\n') {
			// Valid character that is part of the word.
			cache[cache_pos] = input[i];
			cache_pos++;
		} else {
			// End of the word.
			printf("%s\n", cache);
			// Push the word to the top of the stack.
			strcpy((pushWord())->word, cache);
			// Reset the cache.
			cache_pos = 0;
			for(int a = 0; a < 100; a++) {
				cache[a] = '\0';
			}
			// Skip the rest of the whitespace if it's not a single character.
			while(input[i + 1] == ' ') {i++;}
		}
	}


	// Separate the two stacks.
	printf("\n");


	// Print and free the stack.
	sent_ptr temp;
	while(head != NULL) {
		temp = popWord(head);
		printf("%s\n", temp->word);
		free(temp);
	}

	printf("\n");


	return 0;
}

