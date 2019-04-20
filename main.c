#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int main(int argc, char * argv[]){
	int n = 0;

	if (argc <= 1){
		printf ("Usage: %s <number> \n", argv[0]);
		return 2;
	}

	n = atoi(argv[1]);
	assert( n >= 0);
	fact(n);

	return 1;
}