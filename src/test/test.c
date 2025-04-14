#include <stdio.h>

int main(void) {

	FILE* f;
	char c;
	
	c = 164;
	c *= 2;
	if ((f = fopen("file", "wb")) == NULL)
		perror("fopen err");
	fwrite(&c, sizeof(char), 1, f);
	printf("%c\n", c);
	fclose(f);
	return 0;

}
