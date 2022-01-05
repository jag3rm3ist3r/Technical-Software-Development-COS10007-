//Sample Code for Assignment-1 TP1 2020 - COS10007
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Sample Structure 
typedef struct {
	char id[2];
	// Type time_t allows us to store date & time.
	time_t t;
} Bus;

int main() {
	// Initialize the srandom with the current time.
	srandom(time(NULL));
	Bus array[3];
	for(int i = 0; i < 3; i++) {
		printf("Enter bus id ...\n");
		gets(array[i].id);
		// To take the current time and add a random value to it.
		array[i].t = time(NULL)+random()%9999;
	}
	
	/* Following code is to display the structure arrays contents */
	for(int i = 0; i < 3; i++) {
		// ctime: Convert and the time_t to a string.
		printf(	"Bus id = %s -> Time --> %s \n",
				array[i].id,
				ctime(&array[i].t));
	}
     
    return 0;
}
