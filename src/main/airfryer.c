#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "airf.h"

int main(int argc, char *argv[]) {

	if (argc > 2) {
		return EXIT_FAILURE;
	}
	if (argc == 1) 
		iterate_dir("-e", NULL);
	else
		iterate_dir(argv[1], NULL);

	return 0;

}
