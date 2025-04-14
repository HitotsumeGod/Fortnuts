#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ASCII_LIM 255
#define DEGREE 2

void fencrypt(char *fname, int degree);
void fdecrypt(char *fname, int degree);

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA wd;
	HANDLE winhandle;

	if (argc != 2) {
		printf("%s\n", "Please provide an argument for the program.");
		return EXIT_FAILURE;
	}
	if (strcmp("-e", argv[1]) == 0) {
		if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
			perror("findfirstfile err");
			return EXIT_FAILURE;
		}
		while (FindNextFile(winhandle, &wd) > 0) {
			printf("%s\n", wd.cFileName);
			if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				;
			else {
				fencrypt(wd.cFileName, DEGREE);
				printf("File %s encrypted!\n", wd.cFileName);
			}
		}
		if (GetLastError() != ERROR_NO_MORE_FILES) {
			perror("FindNextFile error.");
			return EXIT_FAILURE;
		}
		printf("%s\n", "Encrypting process complete.");
	} else if (strcmp("-d", argv[1]) == 0) {
		if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
			perror("findfirstfile err");
			return EXIT_FAILURE;
		}
		while (FindNextFile(winhandle, &wd) > 0) {
			if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				;
			else {
				fdecrypt(wd.cFileName, DEGREE);
				printf("File %s decrypted!\n", wd.cFileName);
			}
		}
		if (GetLastError() != ERROR_NO_MORE_FILES) {
			perror("FindNextFile error.");
			return EXIT_FAILURE;
		}
		printf("%s\n", "Decrypting process complete.");
	} else 
		printf("%s\n", "Invalid program argument.");
	return 0;

}

void fencrypt(char *fname, int degree) {

	FILE *f;
	char *bitbuf;
	long fsize;

	if ((f = fopen(fname, "rb")) == NULL) {
		perror("fopen err");
		exit(EXIT_FAILURE);
	}
	if (fseek(f, 0, SEEK_END) == -1) {
		perror("fseek err");
		exit(EXIT_FAILURE);
	}
	fsize = ftell(f);
	rewind(f);
	if ((bitbuf = malloc(sizeof(char) * fsize)) == NULL) {
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	if (fread(bitbuf, sizeof(char), fsize, f) < 0) 
		if (ferror(f)) {
			perror("fread err");
			exit(EXIT_FAILURE);
		}
	for (int i = 0; i < fsize; i++) {
		if (*(bitbuf + i) < ASCII_LIM - degree)
			*(bitbuf + i) += degree;
		else 
			*(bitbuf + i) -= degree;
	}
	if (freopen(fname, "wb", f) == NULL) {
		perror("freopen err");
		exit(EXIT_FAILURE);
	}
	if (fwrite(bitbuf, sizeof(char), fsize, f) < 0) {
		perror("fwrite err");
		exit(EXIT_FAILURE);
	}
	if (fclose(f) == -1) {
		perror("fclose err");
		exit(EXIT_FAILURE);
	}
	free(bitbuf);

}

void fdecrypt(char *fname, int degree) {

	FILE *f;
	char *bitbuf;
	long fsize;

	if ((f = fopen(fname, "rb")) == NULL) {
		perror("fopen err");
		exit(EXIT_FAILURE);
	}
	if (fseek(f, 0, SEEK_END) == -1) {
		perror("fseek err");
		exit(EXIT_FAILURE);
	}
	fsize = ftell(f);
	rewind(f);
	if ((bitbuf = malloc(sizeof(char) * fsize)) == NULL) {
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	if (fread(bitbuf, sizeof(char), fsize, f) < 0) 
		if (ferror(f)) {
			perror("fread err");
			exit(EXIT_FAILURE);
		}
	for (int i = 0; i < fsize; i++) {
		if (*(bitbuf + i) == 252 || *(bitbuf + i) == 253)
			*(bitbuf + i) += degree;
		else
			*(bitbuf + i) -= degree;
	}
	if (freopen(fname, "wb", f) == NULL) {
		perror("freopen err");
		exit(EXIT_FAILURE);
	}
	if (fwrite(bitbuf, sizeof(char), fsize, f) < 0) {
		perror("fwrite err");
		exit(EXIT_FAILURE);
	}
	if (fclose(f) == -1) {
		perror("fclose err");
		exit(EXIT_FAILURE);
	}
	free(bitbuf);

}
