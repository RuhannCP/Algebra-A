#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int fact(int n){

	int i;
	int p = 1;

	for (i=1; i <= n ; ++i){
		p = p * i;
	}
	return p;

}

int main(int argc, char * argv[]){
	int n;

	if (argc <= 1){
		/* Check if user has a command line argument */
		printf ("Usage: %s <number>\n", argv[0]);
		return 2;
	}

	n = atoi(argv[1]); /* Extract the command line argument */

	assert( n >= 0);

	/* Print the factorial */
	printf ("%d ! = %d \n", n, fact(n));

	return 1;
}
